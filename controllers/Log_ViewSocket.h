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

#include <drogon/WebSocketController.h>

using namespace drogon;
namespace Log
{
    /**
     * Class Log::ViewSocket. This class handles websocket connections from the event log view page to update
     * the attendance table periodically whenever an user joins or leaves the event channel in Discord.
     *
     * @author Carlos Amores
     */
    class ViewSocket : public drogon::WebSocketController<ViewSocket>
    {
    public:
        /**
         * Stores pointers to the currently open web sockets separated based on event IDs.
         */
        static std::map<std::string, std::vector<WebSocketConnectionPtr>> s_rgOpenSockets;
        /**
         * Stores a map of websocket connection pointers associated with the event ID for which
         * they were opened.
         */
        static std::map<WebSocketConnectionPtr, std::string> s_rgSocketEvent;

        /**
         * Function called when a new message is received from a client currently connected to the websocket.
         * This function is unused.
         */
        void handleNewMessage(const WebSocketConnectionPtr &,
                                      std::string &&,
                                      const WebSocketMessageType &) override;
        /**
         * Function called when a new connection is made from a client to the websocket path specified in this
         * controller.
         */
        void handleNewConnection(const HttpRequestPtr &, const WebSocketConnectionPtr &) override;
        /**
         * Function called when a connection made to the path specified in this controller is closed.
         */
        void handleConnectionClosed(const WebSocketConnectionPtr &) override;

        WS_PATH_LIST_BEGIN
            WS_PATH_ADD("/log/view/");
        WS_PATH_LIST_END
    };
}
