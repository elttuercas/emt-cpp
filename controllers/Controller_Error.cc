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

#include "Controller_Error.h"

using namespace Controller;

void Error::asyncHandleHttpRequest(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    const auto strErrorFile   = req->session()->get<std::string>("errorFile");
    const auto iErrorLine     = req->session()->get<int>("errorLine");
    const auto httpStatusCode = req->session()->get<drogon::HttpStatusCode>("httpErrorCode");
    req->session()->erase("errorFile");
    req->session()->erase("errorLine");
    req->session()->erase("httpErrorCode");

    if (strErrorFile.empty() || iErrorLine == 0)
    {
        // Check that the user should actually be seeing this page.
        callback(drogon::HttpResponse::newRedirectionResponse("/dashboard/"));
        return;
    }

    auto                     *pTmplBootstrap    = drogon::app().getPlugin<GlobalTmplBootstrap>();
    std::ifstream            is(strErrorFile);
    std::string              strLine;
    std::vector<std::string> rgstrLines;
    int                      iMinLine, iMaxLine = iErrorLine + 9, iLine = 1;
    drogon::HttpViewData     data;

    if (iErrorLine - 9 < 1)
    {
        iMinLine = 1;
    }
    else
    {
        iMinLine = iErrorLine - 9;
    }

    rgstrLines.reserve(iMaxLine - iMinLine + 1);
    while (std::getline(is, strLine))
    {
        if (iLine >= iMinLine && iLine <= iMaxLine)
        {
            rgstrLines.push_back(std::move(strLine));
        }
        ++iLine;
    }

    is.close();
    data.insert("loggedIn", req->session()->get<bool>("loggedIn"));
    data.insert("lines", std::move(rgstrLines));
    data.insert("lineStart", iMinLine);

    drogon::HttpResponsePtr pResp = pTmplBootstrap->newHttpViewResponse(
            "./views/global/error.csp",
            "EMT - Error",
            data
    );
    pResp->setStatusCode(httpStatusCode);
    callback(pResp);
}
