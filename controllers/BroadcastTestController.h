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

#include <drogon/HttpSimpleController.h>
#include "Log_ViewSocket.h"

using namespace drogon;
/**
 * Class BroadcastTestController
 *
 * This is a test class to send messages to open websockets associated with events. It does not implement input
 * validation.
 *
 * @author Carlos Amores
 */
class BroadcastTestController : public drogon::HttpSimpleController<BroadcastTestController>
{
public:
    void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
        PATH_ADD("/log/broadcast/", HttpMethod::Get);
    PATH_LIST_END
};
