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

#include "Controller_Log_Create.h"

using namespace Controller::Log;

void Create::get(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    // Create a CSRF Token for the member each time they visit the page to make it properly secure.
    std::string strCsrfToken, strCsrfTokenID;
    strCsrfTokenID = drogon::utils::genRandomString(10);
    strCsrfToken   = drogon::utils::getMd5(drogon::utils::genRandomString(50));

    // Insert into session for evaluation with form submission.
    req->session()->modify<std::string>(
            "csrfTokenID",
            [&strCsrfTokenID](std::string &sessionCsrfTokenID)
            {
                sessionCsrfTokenID = strCsrfTokenID;
            }
    );
    req->session()->modify<std::string>(
            "csrfToken",
            [&strCsrfToken](std::string &sessionCsrfToken)
            {
                sessionCsrfToken = strCsrfToken;
            }
    );

    drogon::HttpViewData data;
    data.insert("loggedIn", req->session()->get<bool>("loggedIn"));
    data.insert("csrfTokenID", std::move(strCsrfTokenID));
    data.insert("csrfToken", std::move(strCsrfToken));

    callback(drogon::HttpResponse::newHttpViewResponse("./views/log/create.csp", data));
}

void Create::post(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    // Retrieve the form data from the request.
    const std::unordered_map<std::string, std::string> rgPostData = req->getParameters();
    const auto                                         strTokenID = req->session()->get<std::string>("csrfTokenID");

    // Create a vector with the expected parameters.
    std::vector<std::string>                             rgExpectedParams = {
            "event",
            "platform",
            "rep_rate",
            strTokenID
    };
    // Create a vector with the name of the input parameters.
    std::vector<std::string>                             rgInputParams;
    try
    {
        rgInputParams.reserve(rgPostData.size());
    }
    catch (const std::length_error &)
    {
        /*
         * A malicious user could cause a length_error by submitting a form with more elements than
         * std::vector<std::string>::max_size so this catch block should redirect the user back to the
         * log creation form with an error message.
         */
        req->session()->insert("errorFile", std::move(std::string(__FILE__)));
        req->session()->insert("errorLine", 71);
        req->session()->insert("httpErrorCode", drogon::HttpStatusCode::k400BadRequest);
        req->session()->insert(
                "errorGithubUrl",
                std::move(
                        std::string(
                                "https://github.com/elttuercas/emt-cpp/tree/master/controllers/Controller_Log_Create.cc#L71"
                        )
                )
        );
        req->session()->insert(
                "errorDetails",
                std::move(
                        std::map<std::string, std::string> {
                                {"POST Data Size",     std::to_string(rgPostData.size())},
                                {"POST Data Max Size", std::to_string(rgInputParams.max_size())}
                        }
                )
        );
        callback(drogon::HttpResponse::newRedirectionResponse("/error/"));
        return;
    }
    for (const std::pair<const std::string, std::string> &postDatum : rgPostData)
    {
        rgInputParams.push_back(postDatum.first);
    }

    // Sort both vectors and ensure the expected keys match exactly with the received keys.
    std::sort(rgInputParams.begin(), rgInputParams.end());
    std::sort(rgExpectedParams.begin(), rgExpectedParams.end());
    if (rgInputParams != rgExpectedParams)
    {
        req->session()->insert("errorFile", std::move(std::string(__FILE__)));
        req->session()->insert("errorLine", 111);
        req->session()->insert("httpErrorCode", drogon::HttpStatusCode::k400BadRequest);
        req->session()->insert(
                "errorGithubUrl",
                std::move(
                        std::string(
                                "https://github.com/elttuercas/emt-cpp/tree/master/controllers/Controller_Log_Create.cc#L111"
                        )
                )
        );
        req->session()->insert(
                "errorDetails",
                std::move(
                        std::map<std::string, std::string> {
                                {"Received POST arguments", std::to_string(rgInputParams.size())},
                                {"Expected POST arguments", std::to_string(rgExpectedParams.size())}
                        }
                )
        );
        callback(drogon::HttpResponse::newRedirectionResponse("/error/"));
        return;
    }

    // Ensure that the CSRF token in the form matches the token in the user's session.
    if (rgPostData.at(strTokenID) != req->session()->get<std::string>("csrfToken"))
    {
        req->session()->insert("errorFile", std::move(std::string(__FILE__)));
        req->session()->insert("errorLine", 138);
        req->session()->insert("httpErrorCode", drogon::HttpStatusCode::k400BadRequest);
        req->session()->insert(
                "errorGithubUrl",
                std::move(
                        std::string(
                                "https://github.com/elttuercas/emt-cpp/tree/master/controllers/Controller_Log_Create.cc#L138"
                        )
                )
        );
        req->session()->insert(
                "errorDetails",
                std::move(
                        std::map<std::string, std::string> {
                                {"Expected CSRF token value", req->session()->get<std::string>("crsfToken")},
                                {"Received CSRF token value", rgPostData.at(strTokenID)}
                        }
                )
        );
        callback(drogon::HttpResponse::newRedirectionResponse("/error/"));
        return;
    }

    drogon::orm::DbClientPtr                                 pDbClient = drogon::app().getDbClient("emt");
    drogon::orm::Mapper<drogon_model::sqlite3::EventLogs>    mapperEventLogs(pDbClient);
    drogon::orm::Mapper<drogon_model::sqlite3::EventActions> mapperEventActions(pDbClient);

    // Get the current unix timestamp.
    std::chrono::time_point<std::chrono::system_clock> tpNow = std::chrono::system_clock::now();

    long iEpochTimestamp = std::chrono::duration_cast<std::chrono::seconds>(tpNow.time_since_epoch()).count();

    // Convert the input data strings to the right types.
    int iAward, iCalendarEventId, iPlatform;
    try
    {
        iAward           = std::stoi(rgPostData.at("rep_rate"));
        iCalendarEventId = std::stoi(rgPostData.at("event"));
        iPlatform        = std::stoi(rgPostData.at("platform"));
    }
    catch (const std::invalid_argument &)
    {
        req->session()->insert("errorFile", std::move(std::string(__FILE__)));
        req->session()->insert("errorLine", 175);
        req->session()->insert("httpErrorCode", drogon::HttpStatusCode::k400BadRequest);
        req->session()->insert(
                "errorGithubUrl",
                std::move(
                        std::string(
                                "https://github.com/elttuercas/emt-cpp/tree/master/controllers/Controller_Log_Create.cc#L175"
                        )
                )
        );
        req->session()->insert(
                "errorDetails",
                std::move(
                        std::map<std::string, std::string> {
                                {"REP Rate", rgPostData.at("rep_rate")},
                                {"Event ID", rgPostData.at("event")},
                                {"Platform", rgPostData.at("platform")}
                        }
                )
        );
        callback(drogon::HttpResponse::newRedirectionResponse("/error/"));
        return;
    }

    if (!(iPlatform == Platform::TWITCH || iPlatform == Platform::DISCORD))
    {
        drogon::HttpResponsePtr pResp = drogon::HttpResponse::newHttpResponse();
        pResp->setStatusCode(drogon::k400BadRequest);
        pResp->setContentTypeCode(drogon::CT_NONE);
        callback(pResp);
        return;
    }

    drogon_model::sqlite3::EventLogs log;
    log.setAward(iAward);
    log.setCalendarEventId(iCalendarEventId);
    log.setPlatform(iPlatform);
    log.setStatus(0);
    log.setHost(req->session()->get<int>("memberId"));
    log.setHash(
            drogon::utils::getMd5(std::to_string(iCalendarEventId) + std::to_string(iEpochTimestamp))
    );
    // TODO: Non-fixed rate.
    log.setRepRate(0.0028);
    mapperEventLogs.insert(log);

    drogon_model::sqlite3::EventActions action;
    action.setLogId(*log.getId());
    action.setMemberId(req->session()->get<int>("memberId"));
    action.setTimestamp(iEpochTimestamp);
    action.setAction(Actions::CREATED);
    mapperEventActions.insert(action);

    if (iPlatform == Platform::DISCORD)
    {
        drogon::orm::Mapper<drogon_model::sqlite3::EventDiscordMap> mapperEventDiscordMap(pDbClient);

        drogon_model::sqlite3::EventDiscordMap eventDiscordMap;
        eventDiscordMap.setLogId(*log.getId());
        // TODO: Get Discord channel from Discord bot.
        eventDiscordMap.setDiscordChannel("");

        mapperEventDiscordMap.insert(eventDiscordMap);
    }

    callback(drogon::HttpResponse::newRedirectionResponse("/log/view/" + *log.getHash() + '/'));
}
