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

#include "GlobalTmplBootstrap.h"

using namespace drogon;

void GlobalTmplBootstrap::initAndStart(const Json::Value &config)
{
}

void GlobalTmplBootstrap::shutdown()
{
}

drogon::HttpResponsePtr GlobalTmplBootstrap::newHttpViewResponse(
        const std::string &viewName,
        const std::string &viewTitle,
        drogon::HttpViewData data
)
{
    // Convert the JSONCPP types to standard library types.
    const Json::Value                                         jsonConfig = drogon::app().getCustomConfig();
    std::map<std::string, std::map<std::string, std::string>> rgFooterLinks;

    for (const std::string &strColumnTitle : jsonConfig["footer_links"].getMemberNames())
    {
        for (const std::string &strLinkName : jsonConfig["footer_links"][strColumnTitle].getMemberNames())
        {
            rgFooterLinks[strColumnTitle][strLinkName] = std::move(
                    jsonConfig["footer_links"][strColumnTitle][strLinkName].asString()
            );
        }
    }

    data.insert("pageTitle", viewTitle);
    data.insert("logoUrl", std::move(jsonConfig["logo_url"].asString()));
    data.insert("footerLinks", std::move(rgFooterLinks));

    return drogon::HttpResponse::newHttpViewResponse(viewName, data);
}

drogon::HttpResponsePtr GlobalTmplBootstrap::newHttpViewResponse(
        const std::string &viewName,
        const std::string &viewTitle
)
{
    drogon::HttpViewData data;
    return newHttpViewResponse(viewName, viewTitle, data);
}
