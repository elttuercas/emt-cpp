/*
 * __/\\\\\\\\\\\\\\\__/\\\\____________/\\\\__/\\\\\\\\\\\\\\\_
 *  _\/\\\///////////__\/\\\\\\________/\\\\\\_\///////\\\/////__
 *   _\/\\\_____________\/\\\//\\\____/\\\//\\\_______\/\\\_______
 *    _\/\\\\\\\\\\\_____\/\\\\///\\\/\\\/_\/\\\_______\/\\\_______
 *     _\/\\\///////______\/\\\__\///\\\/___\/\\\_______\/\\\_______
 *      _\/\\\_____________\/\\\____\///_____\/\\\_______\/\\\_______
 *       _\/\\\_____________\/\\\_____________\/\\\_______\/\\\_______
 *        _\/\\\\\\\\\\\\\\\_\/\\\_____________\/\\\_______\/\\\_______
 *         _\///////////////__\///______________\///________\///________
 */

#include "Controller_Login.h"

using namespace Controller;

void Login::handleOAuthCallback(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    std::string strCode, strState;

    // Get the callback params from the URI.
    try
    {
        const std::unordered_map<std::string, std::string> rgRequestParameters = req->getParameters();
        strCode  = rgRequestParameters.at("code");
        strState = rgRequestParameters.at("state");
    }
    catch (const std::out_of_range &)
    {
        // Either the code or state are not set so redirect to login page.
        req->session()->insert("errors", true);
        callback(drogon::HttpResponse::newRedirectionResponse("/login/"));
        return;
    }

    // Compare the received code with the code stored in the user's session.
    if (strState != req->session()->get<std::string>("oauthState"))
    {
        req->session()->insert("errors", true);
        callback(drogon::HttpResponse::newRedirectionResponse("/login/"));
        return;
    }
    req->session()->erase("oauthState");

    const Json::Value jsonCustomConfig = drogon::app().getCustomConfig();

    // Create a POST request to get the OAuth access token from the server.
    drogon::HttpClientPtr reqClient = drogon::HttpClient::newHttpClient(jsonCustomConfig["ips_site_url"].asString());

    drogon::HttpRequestPtr pTokenReq = drogon::HttpRequest::newHttpFormPostRequest();
    pTokenReq->setParameter("grant_type", "authorization_code");
    pTokenReq->setParameter("code", strCode);
    pTokenReq->setParameter("redirect_uri", jsonCustomConfig["site_url"].asString() + "/login/callback/");
    pTokenReq->setParameter("client_id", jsonCustomConfig["oauth_client_id"].asString());
    pTokenReq->setParameter("client_secret", jsonCustomConfig["oauth_client_secret"].asString());
    pTokenReq->setParameter("code_verifier", req->session()->get<std::string>("oauthCodeVerifier"));
    req->session()->erase("oauthCodeVerifier");

    pTokenReq->setPath("/oauth/token/");
    reqClient->sendRequest(
            pTokenReq,
            [callback, &req, &reqClient](drogon::ReqResult result, const drogon::HttpResponsePtr &resp)
            {
                if (result == drogon::ReqResult::Ok)
                {
                    const std::shared_ptr<Json::Value> pJsonRespData     = resp->getJsonObject();
                    const std::string                  strApiAccessToken = (*pJsonRespData)["access_token"].asString();

                    // With the access token in tow, make another call to the IPS API to obtain member information.
                    drogon::HttpRequestPtr pMemberReq = drogon::HttpRequest::newHttpRequest();
                    pMemberReq->addHeader(
                            "Authorization",
                            "Bearer " + strApiAccessToken
                    );
                    pMemberReq->setPath("/core/me");

                    reqClient->sendRequest(
                            pMemberReq,
                            [callback, &req, &strApiAccessToken](
                                    drogon::ReqResult result,
                                    const drogon::HttpResponsePtr &resp
                            )
                            {
                                if (result == drogon::ReqResult::Ok)
                                {
                                    const std::shared_ptr<Json::Value> pJsonRespData = resp->getJsonObject();
                                    req->session()->insert("loggedIn", true);
                                    req->session()->insert("apiAccessToken", strApiAccessToken);
                                    req->session()->insert("memberId", (*pJsonRespData)["id"].asInt());

                                    callback(drogon::HttpResponse::newRedirectionResponse("/dashboard/"));
                                }
                                else
                                {
                                    req->session()->insert("errors", true);
                                    callback(drogon::HttpResponse::newRedirectionResponse("/login/"));
                                }
                            }
                    );
                }
                else
                {
                    req->session()->insert("errors", true);
                    callback(drogon::HttpResponse::newRedirectionResponse("/login/"));
                }
            }
    );
}

void Login::get(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    std::string strOAuthState = drogon::utils::genRandomString(128);
    // A new state is generated and used to create the link every time the user visits the page.
    req->session()->modify<std::string>(
            "oauthState",
            [&strOAuthState](std::string &sessionState)
            {
                sessionState = strOAuthState;
            }
    );

    // Since we implement PKCE with OAuth, generate a code verifier and challenge.
    char strRandomBytes[32];
    randombytes_buf(strRandomBytes, 32);
    std::string strVerifier = drogon::utils::base64Encode(
            reinterpret_cast<const unsigned char *>(strRandomBytes),
            32,
            true
    );

    // Calculate SHA256 of verifier to obtain the challenge.
    std::string   strChallenge;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX    sha256Ctx;
    SHA256_Init(&sha256Ctx);
    SHA256_Update(&sha256Ctx, strVerifier.c_str(), strVerifier.length());
    SHA256_Final(hash, &sha256Ctx);
    for (const unsigned char &i : hash)
    {
        std::stringstream ss;
        ss << std::hex << static_cast<int>(i);
        strChallenge += ss.str();
    }

    // Base 64 encode the challenge as well.
    strChallenge = drogon::utils::base64Encode(
            reinterpret_cast<const unsigned char *>(strChallenge.c_str()),
            strChallenge.length(),
            true
    );
    // And make the challenge URL safe as well since base64 encoding is not URL safe.
    strChallenge = drogon::utils::urlEncodeComponent(strChallenge);

    const Json::Value jsonCustomConfig = drogon::app().getCustomConfig();

    // Start generating the link the user will be taken to when they click on the login button.
    std::string strOAuthLoginUrl = jsonCustomConfig["ips_site_url"].asString() + "/oauth/authorize/";
    strOAuthLoginUrl +=
            "?response_type=code&client_id=" + jsonCustomConfig["oauth_client_id"].asString() + "&redirect_uri=";
    strOAuthLoginUrl += drogon::utils::urlEncodeComponent(jsonCustomConfig["site_url"].asString() + "/login/callback/");
    strOAuthLoginUrl += "&scope=emt&state=" + strOAuthState + "&code_challenge=" + strChallenge;
    strOAuthLoginUrl += "&code_challenge_method=S256";

    // Store the verifier in the session as it will be used later and like the state it is changed every time...
    req->session()->modify<std::string>(
            "oauthCodeVerifier",
            [&strVerifier](std::string &sessionVerifier)
            {
                sessionVerifier = strVerifier;
            }
    );

    drogon::HttpViewData data;
    data.insert("loggedIn", req->session()->get<bool>("loggedIn"));
    data.insert("oauthLoginUrl", std::move(strOAuthLoginUrl));
    data.insert("errors", req->session()->get<bool>("errors"));
    req->session()->erase("errors");

    callback(drogon::HttpResponse::newHttpViewResponse("./views/login.csp", data));
}
