/**
 *
 *  EventAwards.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "EventAwards.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::sqlite3;

const std::string EventAwards::Cols::_id         = "id";
const std::string EventAwards::Cols::_log_id     = "log_id";
const std::string EventAwards::Cols::_member_id  = "member_id";
const std::string EventAwards::Cols::_rep_issued = "rep_issued";
const std::string EventAwards::primaryKeyName    = "id";
const bool EventAwards::hasPrimaryKey = true;
const std::string EventAwards::tableName = "event_awards";

const std::vector<typename EventAwards::MetaData> EventAwards::metaData_ = {
        {"id",         "uint64_t", "integer", 8, 1, 1, 1},
        {"log_id",     "uint64_t", "integer", 8, 0, 0, 1},
        {"member_id",  "uint64_t", "integer", 8, 0, 0, 1},
        {"rep_issued", "uint64_t", "integer", 8, 0, 0, 1}
};

const std::string &EventAwards::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}

EventAwards::EventAwards(const Row &r, const ssize_t indexOffset) noexcept
{
    if (indexOffset < 0)
    {
        if (!r["id"].isNull())
        {
            id_ = std::make_shared<uint64_t>(r["id"].as<uint64_t>());
        }
        if (!r["log_id"].isNull())
        {
            logId_ = std::make_shared<uint64_t>(r["log_id"].as<uint64_t>());
        }
        if (!r["member_id"].isNull())
        {
            memberId_ = std::make_shared<uint64_t>(r["member_id"].as<uint64_t>());
        }
        if (!r["rep_issued"].isNull())
        {
            repIssued_ = std::make_shared<uint64_t>(r["rep_issued"].as<uint64_t>());
        }
    }
    else
    {
        size_t offset = (size_t) indexOffset;
        if (offset + 4 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if (!r[index].isNull())
        {
            id_ = std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
        index = offset + 1;
        if (!r[index].isNull())
        {
            logId_ = std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
        index = offset + 2;
        if (!r[index].isNull())
        {
            memberId_ = std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
        index = offset + 3;
        if (!r[index].isNull())
        {
            repIssued_ = std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
    }

}

EventAwards::EventAwards(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if (pMasqueradingVector.size() != 4)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if (!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if (!pJson[pMasqueradingVector[0]].isNull())
        {
            id_ = std::make_shared<uint64_t>((uint64_t) pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if (!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if (!pJson[pMasqueradingVector[1]].isNull())
        {
            logId_ = std::make_shared<uint64_t>((uint64_t) pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
    if (!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if (!pJson[pMasqueradingVector[2]].isNull())
        {
            memberId_ = std::make_shared<uint64_t>((uint64_t) pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
    if (!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if (!pJson[pMasqueradingVector[3]].isNull())
        {
            repIssued_ = std::make_shared<uint64_t>((uint64_t) pJson[pMasqueradingVector[3]].asUInt64());
        }
    }
}

EventAwards::EventAwards(const Json::Value &pJson) noexcept(false)
{
    if (pJson.isMember("id"))
    {
        dirtyFlag_[0] = true;
        if (!pJson["id"].isNull())
        {
            id_ = std::make_shared<uint64_t>((uint64_t) pJson["id"].asUInt64());
        }
    }
    if (pJson.isMember("log_id"))
    {
        dirtyFlag_[1] = true;
        if (!pJson["log_id"].isNull())
        {
            logId_ = std::make_shared<uint64_t>((uint64_t) pJson["log_id"].asUInt64());
        }
    }
    if (pJson.isMember("member_id"))
    {
        dirtyFlag_[2] = true;
        if (!pJson["member_id"].isNull())
        {
            memberId_ = std::make_shared<uint64_t>((uint64_t) pJson["member_id"].asUInt64());
        }
    }
    if (pJson.isMember("rep_issued"))
    {
        dirtyFlag_[3] = true;
        if (!pJson["rep_issued"].isNull())
        {
            repIssued_ = std::make_shared<uint64_t>((uint64_t) pJson["rep_issued"].asUInt64());
        }
    }
}

void EventAwards::updateByMasqueradedJson(const Json::Value &pJson,
                                          const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if (pMasqueradingVector.size() != 4)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if (!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if (!pJson[pMasqueradingVector[0]].isNull())
        {
            id_ = std::make_shared<uint64_t>((uint64_t) pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if (!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if (!pJson[pMasqueradingVector[1]].isNull())
        {
            logId_ = std::make_shared<uint64_t>((uint64_t) pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
    if (!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if (!pJson[pMasqueradingVector[2]].isNull())
        {
            memberId_ = std::make_shared<uint64_t>((uint64_t) pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
    if (!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if (!pJson[pMasqueradingVector[3]].isNull())
        {
            repIssued_ = std::make_shared<uint64_t>((uint64_t) pJson[pMasqueradingVector[3]].asUInt64());
        }
    }
}

void EventAwards::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if (pJson.isMember("id"))
    {
        if (!pJson["id"].isNull())
        {
            id_ = std::make_shared<uint64_t>((uint64_t) pJson["id"].asUInt64());
        }
    }
    if (pJson.isMember("log_id"))
    {
        dirtyFlag_[1] = true;
        if (!pJson["log_id"].isNull())
        {
            logId_ = std::make_shared<uint64_t>((uint64_t) pJson["log_id"].asUInt64());
        }
    }
    if (pJson.isMember("member_id"))
    {
        dirtyFlag_[2] = true;
        if (!pJson["member_id"].isNull())
        {
            memberId_ = std::make_shared<uint64_t>((uint64_t) pJson["member_id"].asUInt64());
        }
    }
    if (pJson.isMember("rep_issued"))
    {
        dirtyFlag_[3] = true;
        if (!pJson["rep_issued"].isNull())
        {
            repIssued_ = std::make_shared<uint64_t>((uint64_t) pJson["rep_issued"].asUInt64());
        }
    }
}

const uint64_t &EventAwards::getValueOfId() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if (id_)
        return *id_;
    return defaultValue;
}

const std::shared_ptr<uint64_t> &EventAwards::getId() const noexcept
{
    return id_;
}

void EventAwards::setId(const uint64_t &pId) noexcept
{
    id_ = std::make_shared<uint64_t>(pId);
    dirtyFlag_[0] = true;
}


const typename EventAwards::PrimaryKeyType &EventAwards::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const uint64_t &EventAwards::getValueOfLogId() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if (logId_)
        return *logId_;
    return defaultValue;
}

const std::shared_ptr<uint64_t> &EventAwards::getLogId() const noexcept
{
    return logId_;
}

void EventAwards::setLogId(const uint64_t &pLogId) noexcept
{
    logId_ = std::make_shared<uint64_t>(pLogId);
    dirtyFlag_[1] = true;
}


const uint64_t &EventAwards::getValueOfMemberId() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if (memberId_)
        return *memberId_;
    return defaultValue;
}

const std::shared_ptr<uint64_t> &EventAwards::getMemberId() const noexcept
{
    return memberId_;
}

void EventAwards::setMemberId(const uint64_t &pMemberId) noexcept
{
    memberId_ = std::make_shared<uint64_t>(pMemberId);
    dirtyFlag_[2] = true;
}


const uint64_t &EventAwards::getValueOfRepIssued() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if (repIssued_)
        return *repIssued_;
    return defaultValue;
}

const std::shared_ptr<uint64_t> &EventAwards::getRepIssued() const noexcept
{
    return repIssued_;
}

void EventAwards::setRepIssued(const uint64_t &pRepIssued) noexcept
{
    repIssued_ = std::make_shared<uint64_t>(pRepIssued);
    dirtyFlag_[3] = true;
}


void EventAwards::updateId(const uint64_t id)
{
    id_ = std::make_shared<uint64_t>(id);
}

const std::vector<std::string> &EventAwards::insertColumns() noexcept
{
    static const std::vector<std::string> inCols = {
            "log_id",
            "member_id",
            "rep_issued"
    };
    return inCols;
}

void EventAwards::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if (dirtyFlag_[1])
    {
        if (getLogId())
        {
            binder << getValueOfLogId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[2])
    {
        if (getMemberId())
        {
            binder << getValueOfMemberId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[3])
    {
        if (getRepIssued())
        {
            binder << getValueOfRepIssued();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> EventAwards::updateColumns() const
{
    std::vector<std::string> ret;
    if (dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if (dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if (dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    return ret;
}

void EventAwards::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if (dirtyFlag_[1])
    {
        if (getLogId())
        {
            binder << getValueOfLogId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[2])
    {
        if (getMemberId())
        {
            binder << getValueOfMemberId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if (dirtyFlag_[3])
    {
        if (getRepIssued())
        {
            binder << getValueOfRepIssued();
        }
        else
        {
            binder << nullptr;
        }
    }
}

Json::Value EventAwards::toJson() const
{
    Json::Value ret;
    if (getId())
    {
        ret["id"] = (Json::UInt64) getValueOfId();
    }
    else
    {
        ret["id"] = Json::Value();
    }
    if (getLogId())
    {
        ret["log_id"] = (Json::UInt64) getValueOfLogId();
    }
    else
    {
        ret["log_id"] = Json::Value();
    }
    if (getMemberId())
    {
        ret["member_id"] = (Json::UInt64) getValueOfMemberId();
    }
    else
    {
        ret["member_id"] = Json::Value();
    }
    if (getRepIssued())
    {
        ret["rep_issued"] = (Json::UInt64) getValueOfRepIssued();
    }
    else
    {
        ret["rep_issued"] = Json::Value();
    }
    return ret;
}

Json::Value EventAwards::toMasqueradedJson(
        const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if (pMasqueradingVector.size() == 4)
    {
        if (!pMasqueradingVector[0].empty())
        {
            if (getId())
            {
                ret[pMasqueradingVector[0]] = (Json::UInt64) getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[1].empty())
        {
            if (getLogId())
            {
                ret[pMasqueradingVector[1]] = (Json::UInt64) getValueOfLogId();
            }
            else
            {
                ret[pMasqueradingVector[1]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[2].empty())
        {
            if (getMemberId())
            {
                ret[pMasqueradingVector[2]] = (Json::UInt64) getValueOfMemberId();
            }
            else
            {
                ret[pMasqueradingVector[2]] = Json::Value();
            }
        }
        if (!pMasqueradingVector[3].empty())
        {
            if (getRepIssued())
            {
                ret[pMasqueradingVector[3]] = (Json::UInt64) getValueOfRepIssued();
            }
            else
            {
                ret[pMasqueradingVector[3]] = Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if (getId())
    {
        ret["id"] = (Json::UInt64) getValueOfId();
    }
    else
    {
        ret["id"] = Json::Value();
    }
    if (getLogId())
    {
        ret["log_id"] = (Json::UInt64) getValueOfLogId();
    }
    else
    {
        ret["log_id"] = Json::Value();
    }
    if (getMemberId())
    {
        ret["member_id"] = (Json::UInt64) getValueOfMemberId();
    }
    else
    {
        ret["member_id"] = Json::Value();
    }
    if (getRepIssued())
    {
        ret["rep_issued"] = (Json::UInt64) getValueOfRepIssued();
    }
    else
    {
        ret["rep_issued"] = Json::Value();
    }
    return ret;
}

bool EventAwards::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if (pJson.isMember("id"))
    {
        if (!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if (pJson.isMember("log_id"))
    {
        if (!validJsonOfField(1, "log_id", pJson["log_id"], err, true))
            return false;
    }
    else
    {
        err = "The log_id column cannot be null";
        return false;
    }
    if (pJson.isMember("member_id"))
    {
        if (!validJsonOfField(2, "member_id", pJson["member_id"], err, true))
            return false;
    }
    else
    {
        err = "The member_id column cannot be null";
        return false;
    }
    if (pJson.isMember("rep_issued"))
    {
        if (!validJsonOfField(3, "rep_issued", pJson["rep_issued"], err, true))
            return false;
    }
    else
    {
        err = "The rep_issued column cannot be null";
        return false;
    }
    return true;
}

bool EventAwards::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                     const std::vector<std::string> &pMasqueradingVector,
                                                     std::string &err)
{
    if (pMasqueradingVector.size() != 4)
    {
        err = "Bad masquerading vector";
        return false;
    }
    if (!pMasqueradingVector[0].empty())
    {
        if (pJson.isMember(pMasqueradingVector[0]))
        {
            if (!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                return false;
        }
    }
    if (!pMasqueradingVector[1].empty())
    {
        if (pJson.isMember(pMasqueradingVector[1]))
        {
            if (!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                return false;
        }
        else
        {
            err = "The " + pMasqueradingVector[1] + " column cannot be null";
            return false;
        }
    }
    if (!pMasqueradingVector[2].empty())
    {
        if (pJson.isMember(pMasqueradingVector[2]))
        {
            if (!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                return false;
        }
        else
        {
            err = "The " + pMasqueradingVector[2] + " column cannot be null";
            return false;
        }
    }
    if (!pMasqueradingVector[3].empty())
    {
        if (pJson.isMember(pMasqueradingVector[3]))
        {
            if (!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                return false;
        }
        else
        {
            err = "The " + pMasqueradingVector[3] + " column cannot be null";
            return false;
        }
    }
    return true;
}

bool EventAwards::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if (pJson.isMember("id"))
    {
        if (!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if (pJson.isMember("log_id"))
    {
        if (!validJsonOfField(1, "log_id", pJson["log_id"], err, false))
            return false;
    }
    if (pJson.isMember("member_id"))
    {
        if (!validJsonOfField(2, "member_id", pJson["member_id"], err, false))
            return false;
    }
    if (pJson.isMember("rep_issued"))
    {
        if (!validJsonOfField(3, "rep_issued", pJson["rep_issued"], err, false))
            return false;
    }
    return true;
}

bool EventAwards::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                   const std::vector<std::string> &pMasqueradingVector,
                                                   std::string &err)
{
    if (pMasqueradingVector.size() != 4)
    {
        err = "Bad masquerading vector";
        return false;
    }
    if (!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if (!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if (!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        if (!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
            return false;
    }
    if (!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        if (!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
            return false;
    }
    if (!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        if (!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
            return false;
    }
    return true;
}

bool EventAwards::validJsonOfField(size_t index,
                                   const std::string &fieldName,
                                   const Json::Value &pJson,
                                   std::string &err,
                                   bool isForCreation)
{
    switch (index)
    {
        case 0:
            if (pJson.isNull())
            {
                err = "The " + fieldName + " column cannot be null";
                return false;
            }
            if (isForCreation)
            {
                err = "The automatic primary key cannot be set";
                return false;
            }
            if (!pJson.isUInt64())
            {
                err = "Type error in the " + fieldName + " field";
                return false;
            }
            break;
        case 1:
            if (pJson.isNull())
            {
                err = "The " + fieldName + " column cannot be null";
                return false;
            }
            if (!pJson.isUInt64())
            {
                err = "Type error in the " + fieldName + " field";
                return false;
            }
            break;
        case 2:
            if (pJson.isNull())
            {
                err = "The " + fieldName + " column cannot be null";
                return false;
            }
            if (!pJson.isUInt64())
            {
                err = "Type error in the " + fieldName + " field";
                return false;
            }
            break;
        case 3:
            if (pJson.isNull())
            {
                err = "The " + fieldName + " column cannot be null";
                return false;
            }
            if (!pJson.isUInt64())
            {
                err = "Type error in the " + fieldName + " field";
                return false;
            }
            break;

        default:
            err = "Internal error in the server";
            return false;
            break;
    }
    return true;
}