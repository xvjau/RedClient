/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2013  Gianni Rossi <gianni.rossi@bitforge.com.br>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "rmtimeentry.h"
#include "globals.h"
#include "redminemanager.h"

#include <cassert>

static void __registerClass() __attribute__((constructor));

static void __registerClass() 
{
    qRegisterMetaType<RMTimeEntry*>("RMTimeEntry");
}

RMTimeEntry::RMTimeEntry(): QObject()
{
}

RMTimeEntry::RMTimeEntry(RMTimeEntry&& other): 
    QObject(other.parent()),
    m_id(other.m_id),
    m_project(std::move(other.m_project)),
    m_comments(std::move(other.m_comments)),
    m_activity(std::move(other.m_activity)),
    m_createdOn(std::move(other.m_createdOn)),
    m_updatedOn(std::move(other.m_updatedOn)),
    m_spentOn(std::move(other.m_spentOn)),
    m_user(std::move(other.m_user)),
    m_issue(other.m_issue)
{
}

/*
 * "limit":25,
 * "total_count":111,
 * "time_entries": [{  
 *      "created_on":"2013/10/15 15:06:15 -0300",
 *      "project":{"name":"IPTV Orange","id":2},
 *      "comments":"",
 *      "activity":{"name":"Development","id":9},
 *      "updated_on":"2013/10/15 15:06:15 -0300",
 *      "spent_on":"2013/10/15","hours":40.0,
 *      "user":{"name":"Caio Casimiro","id":8},
 *      "id":113,
 *      "issue":{"id":214}
 * },
 */

RMTimeEntry::RMTimeEntry(const QJsonValueRef& json, RedMineManager* manager, QObject* parent): 
    QObject(parent),
    m_manager(manager)
{
    assert(json.isObject());
    
    QJsonObject obj = json.toObject();
    
    m_id = obj.value("id").toDouble();
    m_project = RMObjectSummary(obj.value("project").toObject());
    m_comments = obj.value("comments").toString();
    m_activity = RMObjectSummary(obj.value("activity").toObject());
    m_createdOn = jsonDate(obj.value("created_on").toString());
    m_updatedOn = jsonDate(obj.value("updated_on").toString());
    m_spentOn = jsonDate(obj.value("spent_on").toString());
    m_user = RMObjectSummary(obj.value("user").toObject());
    m_issue = obj.value("issue").toObject().value("id").toDouble();
}

RMTimeEntry::RMTimeEntry(RedMineManager* manager, QObject* parent): 
    QObject(parent),
    m_manager(manager)
{

}
