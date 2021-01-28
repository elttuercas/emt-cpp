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

#include <drogon/HttpController.h>

using namespace drogon;
namespace Log
{
    /**
     * Class to test the log create view.
     *
     * @author Carlos Amores
     */
    class CreateController : public drogon::HttpController<CreateController>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(CreateController::get, "/log/create/", Get);
            ADD_METHOD_TO(CreateController::post, "/log/create/", Post);
        METHOD_LIST_END

        /**
         * Displays the form to create an event log.
         * @param req
         * @param callback
         */
        void get(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        /**
         * Handle the user form submission and create the event log as requested.
         * @param req
         * @param callback
         */
        void post(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    };
}
