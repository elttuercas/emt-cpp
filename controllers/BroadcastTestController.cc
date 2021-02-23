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

#include "BroadcastTestController.h"

void BroadcastTestController::asyncHandleHttpRequest(
        const drogon::HttpRequestPtr &req,
        std::function<void(const drogon::HttpResponsePtr &)> &&callback
)
{
    std::string                                strEventID     = req->getParameter("event_id");
    std::deque<drogon::WebSocketConnectionPtr> *rgOpenSockets = &Log::ViewSocket::s_rgOpenSockets.at(strEventID);
    Json::Value                                jsonTestData;
    jsonTestData["is_error"] = false;
    jsonTestData["message"]  = "Broadcast test";

    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";

    std::string strJsonTestData = Json::writeString(builder, jsonTestData);

    // Iterate open sockets for the requested event and send the same message in each.
    for (const drogon::WebSocketConnectionPtr &openSocket : *rgOpenSockets)
    {
        openSocket->send(strJsonTestData);
    }

    drogon::HttpResponsePtr resp = drogon::HttpResponse::newHttpResponse();
    resp->setContentTypeCode(drogon::ContentType::CT_NONE);
    resp->setStatusCode(drogon::HttpStatusCode::k204NoContent);
    callback(resp);
}