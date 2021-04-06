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
namespace Api::Log
{
    /**
     * Class Api::Log::View
     *
     * This class handles AJAX operations to control a specific event
     */
    class View : public drogon::HttpController<View>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(View::eventControls, "/api/log/{1:logId}/view/");
        METHOD_LIST_END

        /**
         * Handle the requests sent when an user interacts with an event log's controls.
         *
         * @param req
         * @param callback
         * @param eventId
         */
        void eventControls(const drogon::HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &logId);
    };
}
