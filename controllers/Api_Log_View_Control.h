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
     * This class handles AJAX operations to control a specific event
     */
    class Control : public drogon::HttpController<Control>
    {
    public:
        // TODO: Logged in filter
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(Control::post, "/api/log/{1:logId}/view/control/", HttpMethod::Post);
        METHOD_LIST_END

        enum Actions
        {
            STARTED        = 1 << 0,
            CANCELLED      = 1 << 1,
            ENDED          = 1 << 2,
            AWARDS_ISSUED  = 1 << 3,
            AWARDS_REVOKED = 1 << 4,
            EVENT_LOCKED   = 1 << 5
        };

        void post(const drogon::HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                  const std::string &logId);
    };
}
