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

#include "rmissue.h"
#include "globals.h"

#include <cassert>

static void __registerClass() __attribute__((constructor));

static void __registerClass() 
{
    qRegisterMetaType<RMIssue*>("RMIssue");
    qRegisterMetaType<IssueVectorPtr*>("IssueVectorPtr");
}

RMIssue::RMIssue(RMIssue&& other): 
    QObject(other.parent()),
    m_manager(other.m_manager),
    m_id(other.m_id),
    m_subject(std::move(other.m_subject)),
    m_status(std::move(other.m_status)),
    m_createdOn(std::move(other.m_createdOn)),
    m_author(std::move(other.m_author)),
    m_project(std::move(other.m_project)),
    m_tracker(std::move(other.m_tracker)),
    m_assignedTo(std::move(other.m_assignedTo)),
    m_updatedOn(std::move(other.m_updatedOn)),
    m_startDate(std::move(other.m_startDate)),
    m_doneRatio(other.m_doneRatio),
    m_description(std::move(other.m_description)),
    m_priority(std::move(other.m_priority))
{
}

/*{
    "subject":"STB",
    "status":{"name":"In Progress","id":2},
    "created_on":"2013/09/16 16:20:43 -0300",
    "author":{"name":"Alberto Margarido","id":9},
    "project":{"name":"IPTV Orange","id":2},
    "tracker":{"name":"Documentation","id":7},
    "assigned_to":{"name":"Alberto Margarido","id":9},
    "updated_on":"2013/09/16 16:20:43 -0300",
    "start_date":"2013/09/16",
    "id":222,
    "done_ratio":0,
    "description":"*S*et *T*op *B*OX - manual de configura\u00e7\u00e3o\r\n\r\nM\u00f3dulo: configura\u00e7\u00e3o que \u00e9 realizada pela Operadora",
    "priority":{"name":"Normal","id":4}
}*/

RMIssue::RMIssue(const QJsonValueRef& json, RedMineManager* manager, QObject* parent): 
    QObject(parent),
    m_manager(manager)
{
    assert(json.isObject());
    
    QJsonObject obj = json.toObject();
    
    m_id = obj.value("id").toDouble();
    m_subject = obj.value("subject").toString();
    m_status = RMObjectSummary(obj.value("status").toObject());
    m_createdOn = jsonDate(obj.value("created_on").toString());
    m_author = RMObjectSummary(obj.value("author").toObject());
    m_project = RMObjectSummary(obj.value("project").toObject());
    m_tracker = RMObjectSummary(obj.value("tracker").toObject());
    m_assignedTo = RMObjectSummary(obj.value("assigned_to").toObject());
    m_updatedOn = jsonDate(obj.value("updated_on").toString());
    m_startDate = jsonDate(obj.value("start_date").toString());
    m_doneRatio = obj.value("done_ratio").toDouble();
    m_description = obj.value("description").toString();
    m_priority = RMObjectSummary(obj.value("priority").toObject());
}

RMIssue::RMIssue(RedMineManager* manager, QObject* parent): 
    QObject(parent),
    m_manager(manager)
{

}

