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

using namespace drogon;
namespace Log
{
    /**
     * Class Log::CreateController. This class handles displaying the form to create an event log
     * when accessed with the HTTP GET method and handles the form submission in the same path when the result is
     * submitted with the HTTP POST method.
     *
     * @author Carlos Amores
     */
    class CreateController : public drogon::HttpController<CreateController>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(CreateController::get, "/log/create/", HttpMethod::Get, "LoggedInFilter");
            ADD_METHOD_TO(CreateController::post, "/log/create/", HttpMethod::Post, "LoggedInFilter");
        METHOD_LIST_END

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
