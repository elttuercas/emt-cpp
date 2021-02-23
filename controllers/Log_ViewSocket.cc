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

#include "Log_ViewSocket.h"

using namespace Log;

std::map<std::string, std::deque<WebSocketConnectionPtr>>  ViewSocket::s_rgOpenSockets;
std::map<WebSocketConnectionPtr, std::string>              ViewSocket::s_rgSocketEvent;

void ViewSocket::handleNewMessage(
        const drogon::WebSocketConnectionPtr &wsConnPtr,
        std::string &&message,
        const drogon::WebSocketMessageType &type
)
{
}

void ViewSocket::handleNewConnection(
        const drogon::HttpRequestPtr &req,
        const drogon::WebSocketConnectionPtr &wsConnPtr
)
{
    /*
     * TODO: Validate the event ID received in the request is a currently running valid event.
     * It must be a running event because otherwise there is no point in opening a websocket for
     * an event which is not going to receive updates.
     */
    std::string strEventID = req->getParameter("event_id");
    if (strEventID.empty())
    {
        // There is no event ID in the URL so close the socket immediately.
        Json::Value jsonErrMessage;
        jsonErrMessage["is_error"] = true;
        jsonErrMessage["error"]    = "Invalid event ID";
        jsonErrMessage["errno"]    = 1;

        Json::StreamWriterBuilder builder;
        builder["indentation"] = "";

        wsConnPtr->send(Json::writeString(builder, jsonErrMessage));
        wsConnPtr->forceClose();
        return;
    }

    // Insert the websocket pointer into the container.
    s_rgOpenSockets[strEventID].push_back(wsConnPtr);
    // Map the socket to the event it was created for.
    s_rgSocketEvent[wsConnPtr] = strEventID;
}

void ViewSocket::handleConnectionClosed(const drogon::WebSocketConnectionPtr &wsConnPtr)
{
    // Get the event for which the websocket was created.
    std::string strEventID;
    try
    {
        strEventID = s_rgSocketEvent.at(wsConnPtr);
    }
    catch (const std::out_of_range &)
    {
        /*
         * This can happen when calling forceClose on a websocket that has just been created
         * prior to being closed due to malformed request. Meaning that if it cannot be found
         * it does not exist in either the map or the deque so there is nothing further to do.
         */
        return;
    }
    // Locate the pointer to be deleted in the pointer container.
    auto        it = std::find(
            s_rgOpenSockets[strEventID].begin(),
            s_rgOpenSockets[strEventID].end(),
            wsConnPtr
    );
    // Delete the pointer from the container.
    s_rgOpenSockets[strEventID].erase(it);
    // Delete the map entry for the specified pointer.
    s_rgSocketEvent.erase(wsConnPtr);
}
