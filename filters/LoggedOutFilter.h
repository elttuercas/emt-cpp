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

#include <drogon/HttpFilter.h>

using namespace drogon;

/**
 * Class LoggedOutFilter. This filter is alike LoggedInFilter except that it checks that the user is logged out. We do
 * not want users accessing the login page while they are already logged in.
 *
 * @author Carlos Amores
 */
class LoggedOutFilter : public HttpFilter<LoggedOutFilter>
{
public:
    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) override;
};

