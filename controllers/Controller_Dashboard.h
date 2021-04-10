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
#include <cmath>
#include "plugins/GlobalTmplBootstrap.h"

using namespace drogon;
namespace Controller
{
    /**
     * Class Controller::Dashboard
     *
     * Displays recently hosted events by default. Handles pagination of the recently hosted events table when necessary.
     *
     * @author Carlos Amores
     */
    class Dashboard : public drogon::HttpController<Dashboard>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(Dashboard::get, "/dashboard/", HttpMethod::Get);
            ADD_METHOD_TO(Dashboard::getPaginated, "/dashboard/{1:page}/", HttpMethod::Get);
        METHOD_LIST_END

        /**
         * Handle a default get request without pagination parameters. Displays a table with the last 25 events
         * at most by default.
         *
         * @param req
         * @param callback
         */
        void get(const drogon::HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        /**
         * Handle a get request with pagination data. Display the events corresponding to the requested page
         * to a maximum of 25 events.
         *
         * @param req
         * @param callback
         * @param page
         */
        void getPaginated(const drogon::HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                          int page);
    };
}
