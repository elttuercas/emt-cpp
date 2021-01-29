/*
 * __/\\\\\\\\\\\\\\\__/\\\\____________/\\\\__/\\\\\\\\\\\\\\\_
 *  _\/\\\///////////__\/\\\\\\________/\\\\\\_\///////\\\/////__
 *   _\/\\\_____________\/\\\//\\\____/\\\//\\\_______\/\\\_______
 *    _\/\\\\\\\\\\\_____\/\\\\///\\\/\\\/_\/\\\_______\/\\\_______
 *     _\/\\\///////______\/\\\__\///\\\/___\/\\\_______\/\\\_______
 *	    _\/\\\_____________\/\\\____\///_____\/\\\_______\/\\\_______
 *	     _\/\\\_____________\/\\\_____________\/\\\_______\/\\\_______
 *        _\/\\\\\\\\\\\\\\\_\/\\\_____________\/\\\_______\/\\\_______
 *         _\///////////////__\///______________\///________\///________
 */

#include "LoginController.h"

void LoginController::loginTrue(const drogon::HttpRequestPtr &req,
                                std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    req->session()->insert("loggedIn", true);
    drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newRedirectionResponse("/dashboard/");
    callback(pResponse);
}

void LoginController::handleOAuthCallback(const drogon::HttpRequestPtr &req,
                                          std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    std::string strCode, strState;

    // Get the callback params from the URI.
    try
    {
        std::unordered_map<std::string, std::string> rgRequestParameters = req->getParameters();
        strCode  = rgRequestParameters.at("code");
        strState = rgRequestParameters.at("state");
    }
    catch (const std::out_of_range &e)
    {
        // Either the code or state are not set so redirect to login page.
        callback(drogon::HttpResponse::newRedirectionResponse("/login/"));
        return;
    }

    // Compare the received code with the code stored in the user's session.
    if (strState != req->session()->get<std::string>("oauthState"))
    {
        // Nope.
        callback(drogon::HttpResponse::newRedirectionResponse("/login/"));
        return;
    }
    req->session()->erase("oauthState");

    // Create a POST request to get the OAuth access token from the server.
    drogon::HttpRequestPtr pTokenReq = drogon::HttpRequest::newHttpFormPostRequest();
    pTokenReq->setParameter("grant_type", "authorization_code");
    pTokenReq->setParameter("code", strCode);
    // TODO
    pTokenReq->setParameter("redirect_uri", "");
    pTokenReq->setParameter("client_id", "");
    pTokenReq->setParameter("client_secret", "");

    // TODO
    drogon::HttpClientPtr reqClient = drogon::HttpClient::newHttpClient("");
    reqClient->sendRequest(
            pTokenReq,
            [](drogon::ReqResult result, const drogon::HttpResponsePtr &resp)
            {
                if (result == drogon::ReqResult::Ok)
                {
                    
                }
            }
    );
}
