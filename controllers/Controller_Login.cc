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

const std::string Login::s_strOAuthClientID        = "0312716581837523fb7a3db7d9c324ce";
const std::string Login::s_strOAuthClientSecret    = "";
const std::string Login::s_strRedirectUrl          = "https://emt.eltu.engineer/login/callback/";
const std::string Login::s_strInvisionCommunityUrl = "https://ips.eltu.engineer";

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

    // Create a POST request to get the OAuth access token from the server.
    drogon::HttpRequestPtr pTokenReq = drogon::HttpRequest::newHttpFormPostRequest();
    pTokenReq->setParameter("grant_type", "authorization_code");
    pTokenReq->setParameter("code", strCode);
    pTokenReq->setParameter("redirect_uri", s_strRedirectUrl);
    pTokenReq->setParameter("client_id", s_strOAuthClientID);
    pTokenReq->setParameter("client_secret", s_strOAuthClientSecret);
    pTokenReq->setParameter("code_verifier", req->session()->get<std::string>("oauthCodeVerifier"));
    req->session()->erase("oauthCodeVerifier");

    drogon::HttpClientPtr reqClient = drogon::HttpClient::newHttpClient(s_strInvisionCommunityUrl);
    pTokenReq->setPath("/oauth/token/");
    reqClient->sendRequest(
            pTokenReq,
            [callback, &req](drogon::ReqResult result, const drogon::HttpResponsePtr &resp)
            {
                if (result == drogon::ReqResult::Ok)
                {
                    req->session()->insert("loggedIn", true);
                    const std::shared_ptr<Json::Value> jsonRespData = resp->getJsonObject();
                    // Access token to make API calls.
                    req->session()->insert("apiAccessToken", (*jsonRespData)["access_token"].asString());
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

    // Start generating the link the user will be taken to when they click on the login button.
    std::string strOAuthLoginUrl = s_strInvisionCommunityUrl + "/oauth/authorize/";
    strOAuthLoginUrl += "?response_type=code&client_id=" + s_strOAuthClientID + "&redirect_uri=";
    strOAuthLoginUrl += drogon::utils::urlEncodeComponent(s_strRedirectUrl);
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
    data.insert("oauthLoginUrl", strOAuthLoginUrl);
    data.insert("errors", req->session()->get<bool>("errors"));
    req->session()->erase("errors");

    callback(drogon::HttpResponse::newHttpViewResponse("./views/login.csp", data));
}
