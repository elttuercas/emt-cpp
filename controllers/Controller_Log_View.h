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
#include "models/EventLogs.h"
#include "models/EventDiscordMap.h"

using namespace drogon;
namespace Controller::Log
{
    /**
     * Class Controller::Log::View
     *
     * This controller handles displaying an event log based on the hash passed in the URL.
     *
     * @author Carlos Amores
     */
    class View : public drogon::HttpController<View>
    {
    public:
        // TODO: Attendance pagination view
        METHOD_LIST_BEGIN
        METHOD_LIST_END

        /**
         * Enum Platform
         *
         * The different platforms which can be selected in the EMT to host Events. Should be
         * hardcoded in accordance with the IPS application as well.
         */
        enum Platform
        {
            DISCORD = 1 << 0,
            TWITCH  = 1 << 1
        };

        /**
         * Handles GET requests and displays the requested event log.
         *
         * @param req
         * @param callback
         * @param logId
         */
        void get(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                 const std::string &logId);
    };
}
