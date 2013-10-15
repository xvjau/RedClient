/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2013  Gianni Rossi <gianni.rossi@gmail.com>
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

#include "rmproject.h"

#include <QJsonValueRef>
#include <QJsonObject>

#include <cassert>

static void __registerClass() __attribute__((constructor));

static void __registerClass() 
{
    qRegisterMetaType<RMProject*>("RMProject");
}

RMProject::RMProject(RMProject&& other): 
    QObject(other.parent()),
    m_manager(other.m_manager)
{

}

RMProject::RMProject(const QJsonValueRef& json, RedMineManager* manager, QObject* parent): 
    QObject(parent),
    m_manager(manager)
{
    assert(json.isObject());
    
    QJsonObject obj = json.toObject();
    
    m_id = obj.value("id").toDouble();
    m_createdOn = QDateTime::fromString(obj.value("created_on").toString());
    m_updatedOn = QDateTime::fromString(obj.value("updated_on").toString());
    m_identifier = obj.value("identifier").toString();
    m_name = obj.value("name").toString();
    m_description = obj.value("description").toString();
}

RMProject::RMProject(RedMineManager *manager, QObject *parent):
    QObject(parent),
    m_manager(manager)
{
}

#include "rmproject.moc"
