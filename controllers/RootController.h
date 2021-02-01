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

#include <drogon/HttpSimpleController.h>

using namespace drogon;

/**
 * Class RootController. This class redirects traffic from the default web route / to the default dashboard
 * view. The reason the dashboard view is not located at the web root is because the URL looks like absolute shit
 * when using pagination with the events table.
 *
 * https://emt.eltu.engineer/dashboard/1/ <-- Looks good
 * https://emt.eltu.engineer/1/           <-- What the fuck is this?
 *
 * @author Carlos Amores
 */
class RootController : public drogon::HttpSimpleController<RootController>
{
public:
    void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        PATH_ADD("/", HttpMethod::Get);
    PATH_LIST_END
};
