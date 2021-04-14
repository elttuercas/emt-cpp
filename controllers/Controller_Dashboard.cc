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

#include "Controller_Dashboard.h"

using namespace Controller;

void Dashboard::get(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    auto                 *pTmplBootstrap = drogon::app().getPlugin<GlobalTmplBootstrap>();
    drogon::HttpViewData data;
    data.insert("loggedIn", req->session()->get<bool>("loggedIn"));

    drogon::orm::DbClientPtr                              pDbClient = drogon::app().getDbClient("emt");
    drogon::orm::Mapper<drogon_model::sqlite3::EventLogs> mapperEventLogs(pDbClient);

    try
    {
        std::vector<drogon_model::sqlite3::EventLogs> eventLogs = mapperEventLogs
                .orderBy(drogon_model::sqlite3::EventLogs::Cols::_id, drogon::orm::SortOrder::DESC)
                .limit(25)
                .offset(0)
                .findAll();
        data.insert("eventLogs", std::move(eventLogs));
        callback(pTmplBootstrap->newHttpViewResponse("./views/dashboard.csp", "EMT - Dashboard", data));
    }
    catch (const drogon::orm::SqlError &sqlError)
    {
        req->session()->insert("errorFile", std::move(std::string(__FILE__)));
        req->session()->insert("errorLine", 31);
        req->session()->insert("httpErrorCode", drogon::HttpStatusCode::k500InternalServerError);
        req->session()->insert(
                "errorGithubUrl",
                std::move(
                        std::string(
                                "https://github.com/elttuercas/emt-cpp/tree/master/controllers/Controller_Dashboard.cc#L31"
                        )
                )
        );
        req->session()->insert(
                "errorDetails",
                std::move(
                        std::map<std::string, std::string> {
                                {"SQL Query", sqlError.query()},
                                {"SQL Error", std::move(std::string(sqlError.what()))}
                        }
                )
        );
        callback(drogon::HttpResponse::newRedirectionResponse("/error/"));
    }
}

void Dashboard::getPaginated(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback,
        int page
)
{
}
