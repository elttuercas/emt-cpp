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

#include "Log_CreateController.h"
using namespace Log;

void CreateController::get(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    drogon::HttpViewData data;
    data.insert("loggedIn", true);

    drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newHttpViewResponse("./views/log/create.csp", data);
    callback(pResponse);
}
