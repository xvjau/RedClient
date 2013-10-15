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

#include "redminemanager.h"

#include "rmreqprojects.h"

#include <QAuthenticator>

static void __registerClass() __attribute__((constructor));

static void __registerClass() 
{
    qRegisterMetaType<RedMineManager*>("RedMineManager");
}

RedMineManager::RedMineManager(QUrl url):
    m_baseUrl(std::move(url))
{
    connect(&m_accessManager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));
}

RedMineManager::~RedMineManager()
{
}

void RedMineManager::authenticationRequired(QNetworkReply* reply, QAuthenticator* authenticator)
{
    authenticator->setUser(m_login);
    authenticator->setPassword(m_password);
}

void RedMineManager::login(QString login, QString password)
{
    m_login = std::move(login);
    m_password = std::move(password);
}

void RedMineManager::listProjects()
{  
    RMReqProjects *req = new RMReqProjects(this);
    req->start();
}


#include "redminemanager.moc"
