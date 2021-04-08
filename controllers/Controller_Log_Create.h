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
            ADD_METHOD_TO(Create::get, "/log/create/", HttpMethod::Get, "LoggedInFilter");
            ADD_METHOD_TO(Create::post, "/log/create/", HttpMethod::Post, "LoggedInFilter");
        METHOD_LIST_END

        enum Platform
        {
            DISCORD = 1,
            TWITCH  = 2
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
