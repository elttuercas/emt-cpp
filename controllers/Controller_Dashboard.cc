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

#include "Controller_Dashboard.h"

using namespace Controller;

void Dashboard::get(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    auto                 *pTmplBootstrap = drogon::app().getPlugin<GlobalTmplBootstrap>();
    drogon::HttpViewData data;

    data.insert("loggedIn", req->session()->get<bool>("loggedIn"));
    callback(pTmplBootstrap->newHttpViewResponse("./views/dashboard.csp", "EMT - Dashboard", data));
}

void Dashboard::getPaginated(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback,
        int page
)
{
}
