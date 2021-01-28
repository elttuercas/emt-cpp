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

#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

/**
 * Class LoginController. This class will handle
 */
class LoginController : public drogon::HttpController<LoginController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(LoginController::loginTrue, "/login/", Get, "LoggedOutFilter");
    METHOD_LIST_END

    /**
     * Test method which always sets the user's session logged in value to true.
     * @param req
     * @param callback
     */
    void loginTrue(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
