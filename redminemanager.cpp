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
#include "rmreqissues.h"
#include "rmreqtimeentry.h"

#include "login.h"
#include "rmrequsers.h"

#include <QAuthenticator>
#include <QApplication>
#include <QSettings>
#include <QNetworkConfigurationManager>

static void __registerClass() __attribute__((constructor));

static void __registerClass() 
{
    qRegisterMetaType<RedMineManager*>("RedMineManager");
}

RedMineManager::RedMineManager(QUrl url):
    m_baseUrl(std::move(url))
{
    connect(&m_accessManager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));
    
    QSettings settings;
    settings.beginGroup("RedMine");
    
    if (settings.contains("AccessKey"))
        m_extraHeaders.insert("X-Redmine-API-Key", settings.value("AccessKey").toString());
}

RedMineManager::~RedMineManager()
{
}

void RedMineManager::authenticationRequired(QNetworkReply* reply, QAuthenticator* authenticator)
{
    Q_UNUSED(reply);
    
    Login dlg;
    if (dlg.exec() == QDialog::Rejected)
        QApplication::quit();
    
    authenticator->setUser(dlg.login());
    authenticator->setPassword(dlg.password());
}

void RedMineManager::listProjects(uint offset)
{  
    RMReqProjects *req = new RMReqProjects(this);
    
    connect(req, SIGNAL(recievedProjectList(uint, uint, uint, ProjectVectorPtr)), this, SIGNAL(recievedProjectList(uint, uint, uint, ProjectVectorPtr)));
    
    req->start();
}

void RedMineManager::listIssues(uint offset)
{
    RMReqIssues::Filters filters;
    filters.status = RMIssue::isAll;
    filters.offset = offset;
    RMReqIssues *req = new RMReqIssues(this, std::move(filters));
    
    connect(req, SIGNAL(recievedIssueList(uint, uint, uint, IssueVectorPtr)), this, SIGNAL(recievedIssuesList(uint, uint, uint, IssueVectorPtr)));
    
    req->start();
}

void RedMineManager::listTimeEntries(uint offset)
{
    RMReqTimeEntry::Filters filters;
    filters.offset = offset;
    
    RMReqTimeEntry *req = new RMReqTimeEntry(this, std::move(filters));
    
    connect(req, SIGNAL(recievedTimeEntryList(uint, uint, uint, TimeEntryVectorPtr)), this, SIGNAL(recievedTimeEntriesList(uint, uint, uint, TimeEntryVectorPtr)));
    
    req->start();
}

void RedMineManager::listUsers(uint offset)
{
    RMReqUsers::Filters filters;
    
    RMReqUsers *req = new RMReqUsers(this, std::move(filters));
    
    connect(req, SIGNAL(recievedUserList(uint,uint,uint,UserVectorPtr)), this, SIGNAL(recievedUsersList(uint,uint,uint,UserVectorPtr)));
    
    req->start();
}
