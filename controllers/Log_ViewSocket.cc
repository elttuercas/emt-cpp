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
    // TODO: Validate the event ID received in the request is a currently running valid event.
    std::string strEventID = req->getParameter("event_id");
    if (strEventID.empty())
    {
        /*
         * There is no event ID in the URL so close the socket immediately.
         * TODO: Send error message prior to force closing the connection.
         */
        wsConnPtr->forceClose();
        return;
    }

    // Insert the websocket pointer into the container.
    //s_rgOpenSockets[strEventID].push_back(wsConnPtr);
    // Map the socket to the event it was created for.
    //s_rgSocketEvent[wsConnPtr] = strEventID;
}

void ViewSocket::handleConnectionClosed(const drogon::WebSocketConnectionPtr &wsConnPtr)
{
    // Get the event for which the websocket was created.
    //std::string strEventID = s_rgSocketEvent[wsConnPtr];
    // Locate the pointer to be deleted in the pointer container.
    /*auto        it         = std::find(
            s_rgOpenSockets[strEventID].begin(),
            s_rgOpenSockets[strEventID].end(),
            wsConnPtr
    );*/
    // Delete the pointer from the container.
    //s_rgOpenSockets[strEventID].erase(it);
    // Delete the map entry for the specified pointer.
    //s_rgSocketEvent.erase(wsConnPtr);
}
