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
namespace Api::Log::View
{
    /**
     * Class Api::Log::View
     *
     * This class handles AJAX operations to control a specific event log in the EMT.
     *
     * @author Carlos Amores
     */
    class Control : public drogon::HttpController<Control>
    {
    public:
        // TODO: Logged in filter
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(Control::post, "/api/log/view/{1:logId}/control/", HttpMethod::Post);
        METHOD_LIST_END

        /**
         * Enum Actions
         *
         * In this controller the CREATED action is not used given that this controller handles
         * the event controls once it has been created.
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
         * Handles AJAX POST requests sent to the endpoint to control an Event log.
         *
         * @param req
         * @param callback
         * @param logId
         */
        void post(const drogon::HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                  const std::string &logId);
    };
}
