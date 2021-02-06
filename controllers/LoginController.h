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

#pragma once

#include <drogon/HttpController.h>
#include <drogon/HttpClient.h>
#include "sodium/randombytes.h"
#include "openssl/sha.h"

using namespace drogon;

/**
 * Class LoginController. This class will handle
 */
class LoginController : public drogon::HttpController<LoginController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(LoginController::get, "/login/", HttpMethod::Get, "LoggedOutFilter");
        ADD_METHOD_TO(LoginController::handleOAuthCallback, "/login/callback/", HttpMethod::Get, "LoggedOutFilter");
    METHOD_LIST_END

    /**
     * Handle OAuth callback validation and login.
     * @param req
     * @param callback
     */
    void handleOAuthCallback(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    /**
     * Display the login page, set an OAuth state in user's session and create a login link with the dynamic state data.
     * @param req
     * @param callback
     */
    void get(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

private:
    /**
     * The client ID assigned to the EMT application by the application we are going to use to log in using OAuth.
     */
    static const std::string s_strOAuthClientID;
    /**
     * The client secret assigned to the EMT application by the application we are going to use to log in using OAuth.
     */
    static const std::string s_strOAuthClientSecret;
    /**
     * The URI to which the user will be redirected in our application after accepting to log in.
     */
    static const std::string s_strRedirectUrl;
};
