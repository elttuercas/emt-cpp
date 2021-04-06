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
#include <sodium/randombytes.h>
#include <openssl/sha.h>

using namespace drogon;
namespace Controller
{
    /**
     * Class Controller::Login
     *
     * This class handles user OAuth login with an IPS community.
     *
     * @author Carlos Amores
     */
    class Login : public drogon::HttpController<Login>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(Login::get, "/login/", HttpMethod::Get, "LoggedOutFilter");
            ADD_METHOD_TO(Login::handleOAuthCallback, "/login/callback/", HttpMethod::Get, "LoggedOutFilter");
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
         * The URL to which the user will be redirected in our application after accepting to log in.
         */
        static const std::string s_strRedirectUrl;
        /**
         * The URL where the POST request will be sent to obtain the authorisation token.
         */
        static const std::string s_strInvisionCommunityUrl;
    };
}
