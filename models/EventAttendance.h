/**
 *
 *  EventAttendance.h
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

        class EventAttendance
        {
        public:
            struct Cols
            {
                static const std::string _id;
                static const std::string _log_id;
                static const std::string _member_id;
                static const std::string _time_in_event;
                static const std::string _member_group_id;
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
            explicit EventAttendance(const Row &r, const ssize_t indexOffset = 0) noexcept;

            /**
             * @brief constructor
             * @param pJson The json object to construct a new instance.
             */
            explicit EventAttendance(const Json::Value &pJson) noexcept(false);

            /**
             * @brief constructor
             * @param pJson The json object to construct a new instance.
             * @param pMasqueradingVector The aliases of table columns.
             */
            EventAttendance(const Json::Value &pJson,
                            const std::vector<std::string> &pMasqueradingVector) noexcept(false);

            EventAttendance() = default;

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


            /**  For column log_id  */
            ///Get the value of the column log_id, returns the default value if the column is null
            const uint64_t &getValueOfLogId() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getLogId() const noexcept;

            ///Set the value of the column log_id
            void setLogId(const uint64_t &pLogId) noexcept;


            /**  For column member_id  */
            ///Get the value of the column member_id, returns the default value if the column is null
            const uint64_t &getValueOfMemberId() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getMemberId() const noexcept;

            ///Set the value of the column member_id
            void setMemberId(const uint64_t &pMemberId) noexcept;


            /**  For column time_in_event  */
            ///Get the value of the column time_in_event, returns the default value if the column is null
            const uint64_t &getValueOfTimeInEvent() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getTimeInEvent() const noexcept;

            ///Set the value of the column time_in_event
            void setTimeInEvent(const uint64_t &pTimeInEvent) noexcept;


            /**  For column member_group_id  */
            ///Get the value of the column member_group_id, returns the default value if the column is null
            const uint64_t &getValueOfMemberGroupId() const noexcept;
            ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
            const std::shared_ptr<uint64_t> &getMemberGroupId() const noexcept;

            ///Set the value of the column member_group_id
            void setMemberGroupId(const uint64_t &pMemberGroupId) noexcept;


            static size_t getColumnNumber() noexcept
            { return 5; }

            static const std::string &getColumnName(size_t index) noexcept(false);

            Json::Value toJson() const;
            Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
            /// Relationship interfaces
        private:
            friend Mapper<EventAttendance>;
            static const std::vector<std::string> &insertColumns() noexcept;
            void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
            const std::vector<std::string> updateColumns() const;
            void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
            ///For mysql or sqlite3
            void updateId(const uint64_t id);
            std::shared_ptr<uint64_t>          id_;
            std::shared_ptr<uint64_t>          logId_;
            std::shared_ptr<uint64_t>          memberId_;
            std::shared_ptr<uint64_t>          timeInEvent_;
            std::shared_ptr<uint64_t>          memberGroupId_;
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
            bool                               dirtyFlag_[5] = {false};
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
                    sql += "log_id,";
                    ++parametersCount;
                }
                if (dirtyFlag_[2])
                {
                    sql += "member_id,";
                    ++parametersCount;
                }
                if (dirtyFlag_[3])
                {
                    sql += "time_in_event,";
                    ++parametersCount;
                }
                if (!dirtyFlag_[3])
                {
                    needSelection = true;
                }
                if (dirtyFlag_[4])
                {
                    sql += "member_group_id,";
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
