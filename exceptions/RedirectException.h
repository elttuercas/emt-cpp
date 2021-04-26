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

#include <exception>
#include <drogon/HttpTypes.h>
#include <string>
#include <map>

/**
 * Class RedirectException
 *
 * This is a custom exception class which allows code which may cause an error to be wrapped in a try-catch
 * block where this exception is thrown within the try part when the error occurs as to simplify the code
 * required to redirect an user to the error page within the application.
 *
 * @author Carlos Amores
 */
class RedirectException : public std::exception
{
public:
    explicit RedirectException(const int &errorLine,
                               const drogon::HttpStatusCode &httpStatusCode,
                               std::map<std::string, std::string> &&errorDetails) noexcept;
    explicit RedirectException(const int &errorLine, const drogon::HttpStatusCode &httpStatusCode) noexcept;
    [[nodiscard]] int getErrorLine() const;
    [[nodiscard]] drogon::HttpStatusCode getHttpStatusCode() const;
    [[nodiscard]] std::map<std::string, std::string> &&getErrorDetails();
protected:
    int                                m_iErrorLine;
    drogon::HttpStatusCode             m_httpStatusCode;
    std::map<std::string, std::string> m_rgErrorDetails;
};
