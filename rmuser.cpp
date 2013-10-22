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

#include "rmuser.h"

#include <QJsonObject>

#include <cassert>

static void __registerClass() __attribute__((constructor));

static void __registerClass() 
{
    qRegisterMetaType<RMUser*>("RMUser");
    qRegisterMetaType<UserVectorPtr*>("UserVectorPtr");
}

RMUser::RMUser(RMUser&& other): 
    QObject(other.parent()),
    m_manager(other.m_manager),
    m_id(other.m_id),
    m_login(std::move(other.m_login)),
    m_firstName(std::move(other.m_firstName)),
    m_lastName(std::move(other.m_lastName)),
    m_email(std::move(other.m_email)),
    m_authSourceId(other.m_authSourceId)
{

}

RMUser::RMUser(const QJsonValueRef& json, RedMineManager* manager, QObject* parent): 
    QObject(parent),
    m_manager(manager)
{
    assert(json.isObject());
    
    QJsonObject obj = json.toObject();
    
    m_id = obj.value("id").toDouble();
    m_login = obj.value("login").toString();
    m_firstName = obj.value("firstname").toString();
    m_lastName = obj.value("lastname").toString();
    m_email = obj.value("email").toString();
    m_authSourceId = obj.value("auth_source_id").toDouble();
}

RMUser::RMUser(RedMineManager* manager, QObject* parent): 
    QObject(parent),
    m_manager(manager)
{

}
