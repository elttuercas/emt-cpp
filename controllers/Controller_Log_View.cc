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

#include "Controller_Log_View.h"

using namespace Controller::Log;

void View::get(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback,
        const std::string &logId
)
{
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

        if (*log.getPlatform() == Platform::DISCORD)
        {
            log.getDiscord(
                    pDbClient,
                    [callback](const drogon_model::sqlite3::EventDiscordMap &eventDiscordMap)
                    {
                        // TODO: Send request to Discord bot for attendance data based on the channel just obtained.
                    },
                    [callback](const drogon::orm::DrogonDbException &e)
                    {
                        // TODO: Error page.
                    }
            );
        }
        else
        {
            // TODO: Twitch events.
        }
    }
    catch (const drogon::orm::UnexpectedRows &)
    {
        // TODO: Log not found page.
    }
}
