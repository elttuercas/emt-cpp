/**
 *
 *  EventLogs.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

using namespace drogon::orm;
namespace drogon
{
    namespace orm
    {
        class DbClient;

        using DbClientPtr = std::shared_ptr<DbClient>;
    }
}
namespace drogon_model
{
    namespace sqlite3
    {
        class EventActions;

        class EventAttendance;

        class EventAwards;

        class EventDiscordMap;

        class EventLogs
        {
        public:
            struct Cols
            {
                static const std::string _id;
                static const std::string _award;
                static const std::string _calendar_event_id;
                static const std::string _platform;
                static const std::string _status;
                static const std::string _host;
                static const std::string _hash;
                static const std::string _rep_rate;
            };

            const static int                   primaryKeyNumber;
            const static std::string           tableName;
            const static bool                  hasPrimaryKey;
            const static std::string           primaryKeyName;
            using PrimaryKeyType = uint64_t;
            const PrimaryKeyType &getPrimaryKey() const;

            /**
             * @brief constructor
             * @param r One row of records in the SQL query result.
             * @param indexOffset Set the offset to -1 to access all columns by column names,
             * otherwise access all columns by offsets.
             * @note If the SQL is not a style of 'select * from table_name ...' (select all
             * columns by an asterisk), please set the offset to -1.
             */
            explicit EventLogs(const Row &r, const ssize_t indexOffset = 0) noexcept;

            /**
             * @brief constructor
             * @param pJson The json object to construct a new instance.
             */
            explicit EventLogs(const Json::Value &pJson) noexcept(false);

            /**
             * @brief constructor
             * @param pJson The json object to construct a new instance.
             * @param pMasqueradingVector The aliases of table columns.
             */
            EventLogs(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

            EventLogs() = default;

            void updateByJson(const Json::Value &pJson) noexcept(false);
            void updateByMasqueradedJson(const Json::Value &pJson,
                                         const std::vector<std::string> &pMasqueradingVector) noexcept(false);
            static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
            static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                           const std::vector<std::string> &pMasqueradingVector,
                                                           std::string &err);
            static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
            static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                                         const std::vector<std::string> &pMasqueradingVector,
                                                         std::string &err);
            static bool validJsonOfField(size_t index,
                                         const std::string &fieldName,
                                         const Json::Value &pJson,
                                         std::string &err,
                                         bool isForCreation);

            /**  For column id  */
            ///Get the value of the column id, returns the default value if the column is null
            const uint64_t &getValueOfId() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getId() const noexcept;

            ///Set the value of the column id
            void setId(const uint64_t &pId) noexcept;


            /**  For column award  */
            ///Get the value of the column award, returns the default value if the column is null
            const uint64_t &getValueOfAward() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getAward() const noexcept;

            ///Set the value of the column award
            void setAward(const uint64_t &pAward) noexcept;


            /**  For column calendar_event_id  */
            ///Get the value of the column calendar_event_id, returns the default value if the column is null
            const uint64_t &getValueOfCalendarEventId() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getCalendarEventId() const noexcept;

            ///Set the value of the column calendar_event_id
            void setCalendarEventId(const uint64_t &pCalendarEventId) noexcept;


            /**  For column platform  */
            ///Get the value of the column platform, returns the default value if the column is null
            const uint64_t &getValueOfPlatform() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getPlatform() const noexcept;

            ///Set the value of the column platform
            void setPlatform(const uint64_t &pPlatform) noexcept;


            /**  For column status  */
            ///Get the value of the column status, returns the default value if the column is null
            const uint64_t &getValueOfStatus() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getStatus() const noexcept;

            ///Set the value of the column status
            void setStatus(const uint64_t &pStatus) noexcept;


            /**  For column host  */
            ///Get the value of the column host, returns the default value if the column is null
            const uint64_t &getValueOfHost() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getHost() const noexcept;

            ///Set the value of the column host
            void setHost(const uint64_t &pHost) noexcept;


            /**  For column hash  */
            ///Get the value of the column hash, returns the default value if the column is null
            const std::string &getValueOfHash() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<std::string> &getHash() const noexcept;

            ///Set the value of the column hash
            void setHash(const std::string &pHash) noexcept;
            void setHash(std::string &&pHash) noexcept;


            /**  For column rep_rate  */
            ///Get the value of the column rep_rate, returns the default value if the column is null
            const double &getValueOfRepRate() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<double> &getRepRate() const noexcept;

            ///Set the value of the column rep_rate
            void setRepRate(const double &pRepRate) noexcept;


            static size_t getColumnNumber() noexcept
            { return 8; }

            static const std::string &getColumnName(size_t index) noexcept(false);

            Json::Value toJson() const;
            Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
            /// Relationship interfaces
            void getAction(const DbClientPtr &clientPtr,
                           const std::function<void(std::vector<EventActions>)> &rcb,
                           const ExceptionCallback &ecb) const;
            void getAttendance(const DbClientPtr &clientPtr,
                               const std::function<void(std::vector<EventAttendance>)> &rcb,
                               const ExceptionCallback &ecb) const;
            void getAward(const DbClientPtr &clientPtr,
                          const std::function<void(std::vector<EventAwards>)> &rcb,
                          const ExceptionCallback &ecb) const;
            void getDiscord(const DbClientPtr &clientPtr,
                            const std::function<void(EventDiscordMap)> &rcb,
                            const ExceptionCallback &ecb) const;
        private:
            friend Mapper<EventLogs>;
            static const std::vector<std::string> &insertColumns() noexcept;
            void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
            const std::vector<std::string> updateColumns() const;
            void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
            ///For mysql or sqlite3
            void updateId(const uint64_t id);
            std::shared_ptr<uint64_t>          id_;
            std::shared_ptr<uint64_t>          award_;
            std::shared_ptr<uint64_t>          calendarEventId_;
            std::shared_ptr<uint64_t>          platform_;
            std::shared_ptr<uint64_t>          status_;
            std::shared_ptr<uint64_t>          host_;
            std::shared_ptr<std::string>       hash_;
            std::shared_ptr<double>            repRate_;
            struct MetaData
            {
                const std::string colName_;
                const std::string colType_;
                const std::string colDatabaseType_;
                const ssize_t     colLength_;
                const bool        isAutoVal_;
                const bool        isPrimaryKey_;
                const bool        notNull_;
            };
            static const std::vector<MetaData> metaData_;
            bool                               dirtyFlag_[8] = {false};
        public:
            static const std::string &sqlForFindingByPrimaryKey()
            {
                static const std::string sql = "select * from " + tableName + " where id = ?";
                return sql;
            }

            static const std::string &sqlForDeletingByPrimaryKey()
            {
                static const std::string sql = "delete from " + tableName + " where id = ?";
                return sql;
            }

            std::string sqlForInserting(bool &needSelection) const
            {
                std::string sql             = "insert into " + tableName + " (";
                size_t      parametersCount = 0;
                needSelection = false;
                if (dirtyFlag_[1])
                {
                    sql += "award,";
                    ++parametersCount;
                }
                if (dirtyFlag_[2])
                {
                    sql += "calendar_event_id,";
                    ++parametersCount;
                }
                if (dirtyFlag_[3])
                {
                    sql += "platform,";
                    ++parametersCount;
                }
                if (dirtyFlag_[4])
                {
                    sql += "status,";
                    ++parametersCount;
                }
                if (dirtyFlag_[5])
                {
                    sql += "host,";
                    ++parametersCount;
                }
                if (dirtyFlag_[6])
                {
                    sql += "hash,";
                    ++parametersCount;
                }
                if (dirtyFlag_[7])
                {
                    sql += "rep_rate,";
                    ++parametersCount;
                }
                if (parametersCount > 0)
                {
                    sql[sql.length() - 1] = ')';
                    sql += " values (";
                }
                else
                    sql += ") values (";

                if (dirtyFlag_[1])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[2])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[3])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[4])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[5])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[6])
                {
                    sql.append("?,");

                }
                if (dirtyFlag_[7])
                {
                    sql.append("?,");

                }
                if (parametersCount > 0)
                {
                    sql.resize(sql.length() - 1);
                }
                sql.append(1, ')');
                LOG_TRACE << sql;
                return sql;
            }
        };
    } // namespace sqlite3
} // namespace drogon_model
