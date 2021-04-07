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

#include "Api_Log_View_Control.h"

using namespace Api::Log::View;

void Control::post(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback,
        const std::string &logId
)
{
    int iAction;
    try
    {
        // Validate POST input.
        iAction = std::stoi(req->getParameter("action"));
    }
    catch (const std::invalid_argument &)
    {
        drogon::HttpResponsePtr pResp;
        pResp->setStatusCode(drogon::k400BadRequest);
        pResp->setContentTypeCode(drogon::CT_NONE);
        callback(pResp);
        return;
    }

    // I'm retarded and right now I cannot think of a better way to validate input.
    if (!(iAction == Actions::STARTED
          || iAction == Actions::ENDED
          || iAction == Actions::CANCELLED
          || iAction == Actions::AWARDS_ISSUED
          || iAction == Actions::AWARDS_REVOKED
          || iAction == Actions::EVENT_LOCKED))
    {
        drogon::HttpResponsePtr pResp = drogon::HttpResponse::newHttpResponse();
        pResp->setStatusCode(drogon::k400BadRequest);
        pResp->setContentTypeCode(drogon::CT_NONE);
        callback(pResp);
        return;
    }

    drogon::orm::DbClientPtr                              pDbClient = drogon::app().getDbClient("emt");
    drogon::orm::Mapper<drogon_model::sqlite3::EventLogs> mapperEventLogs(pDbClient);

    try
    {
        drogon_model::sqlite3::EventLogs log = mapperEventLogs.findOne(
                drogon::orm::Criteria(
                        drogon_model::sqlite3::EventLogs::Cols::_hash,
                        drogon::orm::CompareOperator::EQ,
                        logId
                )
        );

        // Record that the action was performed.
        drogon::orm::Mapper<drogon_model::sqlite3::EventActions> mapperEventActions(pDbClient);
        drogon_model::sqlite3::EventActions                      action;

        action.setLogId(*log.getId());
        action.setMemberId(req->session()->get<int>("memberId"));
        action.setAction(iAction);

        // Get the current unix timestamp.
        std::chrono::time_point<std::chrono::system_clock> tpNow = std::chrono::system_clock::now();

        long iEpochTimestamp = std::chrono::duration_cast<std::chrono::seconds>(tpNow.time_since_epoch()).count();

        action.setTimestamp(iEpochTimestamp);

        mapperEventActions.insert(action);

        // Update the state of the event log accordingly.
        if (iAction == Actions::CANCELLED)
        {
            // If the event is cancelled, its state is set both to cancelled and ended.
            log.setStatus(*log.getStatus() | Actions::CANCELLED | Actions::ENDED);
        }
        else if (iAction == Actions::AWARDS_ISSUED)
        {
            // Also make a check to see if awards were previously revoked. If so, remove the revoked flag.
            if (*log.getStatus() & Actions::AWARDS_REVOKED)
            {
                log.setStatus(*log.getStatus() & ~Actions::AWARDS_REVOKED);
            }
            log.setStatus(*log.getStatus() | Actions::AWARDS_ISSUED);
        }
        else if (iAction == Actions::EVENT_LOCKED && *log.getStatus() & Actions::EVENT_LOCKED)
        {
            // Special case where the event locked action is sent again and results in the log being unlocked.
            log.setStatus(*log.getStatus() & ~Actions::EVENT_LOCKED);
        }
        else
        {
            // The rest of the cases, the flag simply is added or-ed with the existing value.
            log.setStatus(*log.getStatus() | iAction);
        }

        // And simply save the log.
        mapperEventLogs.update(log);

        drogon::HttpResponsePtr pResp = drogon::HttpResponse::newHttpResponse();
        pResp->setContentTypeCode(drogon::CT_NONE);
        pResp->setStatusCode(drogon::k204NoContent);
        callback(pResp);
    }
    catch (const drogon::orm::UnexpectedRows &)
    {
        // Exception thrown if no event is found. Return an error response.
        callback(drogon::HttpResponse::newNotFoundResponse());
    }
}
