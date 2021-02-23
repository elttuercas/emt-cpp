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

/**
 * Interface WebSocketErrorResponse
 *
 * Represents an error response emitted by the serverside websocket controllers.
 *
 * @author Carlos Amores
 */
export interface WebSocketErrorResponse
{
    /**
     * Whether the response is an error response. Since this is an interface, it is a constant true value.
     */
    is_error : true;
    /**
     * A brief description of the error.
     */
    error : string;
    /**
     * Error code. Ideally unique in the whole application, most likely unique per endpoint. We will see.
     */
    errno : number;
}
