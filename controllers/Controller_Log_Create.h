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
#include "models/EventActions.h"
#include "models/EventDiscordMap.h"
#include "plugins/GlobalTmplBootstrap.h"

using namespace drogon;
namespace Controller::Log
{
    /**
     * Class Controller::Log::Create
     *
     * This class handles displaying the form to create an event log when accessed with the HTTP GET method and
     * handles the form submission in the same path when the result is submitted with the HTTP POST method.
     *
     * @author Carlos Amores
     */
    class Create : public drogon::HttpController<Create>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(Create::get, "/log/create/", HttpMethod::Get);
            ADD_METHOD_TO(Create::post, "/log/create/", HttpMethod::Post);
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
         * Enum Actions
         *
         * In this controller only the created action is used given this is the log creation controller.
         * The rest of the actions are used in the API controller Log_View_Control.
         */
        enum Actions
        {
            CREATED        = 1 << 0,
            STARTED        = 1 << 1,
            CANCELLED      = 1 << 2,
            ENDED          = 1 << 3,
            AWARDS_ISSUED  = 1 << 4,
            AWARDS_REVOKED = 1 << 5,
            EVENT_LOCKED   = 1 << 6
        };

        /**
         * Displays the form to create an event log.
         * @param req
         * @param callback
         */
        void get(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        /**
         * Handle the user form submission, validate input and create the event log.
         * @param req
         * @param callback
         */
        void post(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    };
}
