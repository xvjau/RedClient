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

#ifndef REDMINEMANAGER_H
#define REDMINEMANAGER_H

#include <QObject>
#include <QUrl>
#include <QMap>
#include <QNetworkAccessManager>

#include "rmtimeentry.h"
#include "rmproject.h"
#include "rmissue.h"
#include "rmuser.h"

class QNetworkAccessManager;

class RedMineManager : public QObject
{
    Q_OBJECT

public:
    RedMineManager(QUrl url);
    virtual ~RedMineManager();
    
private:
    QMap<QString, QString>  m_extraHeaders;
    
    QUrl                    m_baseUrl;
    QNetworkAccessManager   m_accessManager;
    
protected slots:
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    
signals:
    void recievedProjectList(uint limit, uint offset, uint totalCount, ProjectVectorPtr projects);
    void recievedIssuesList(uint limit, uint offset, uint totalCount, IssueVectorPtr issues);
    void recievedTimeEntriesList(uint limit, uint offset, uint totalCount, TimeEntryVectorPtr timeEntries);
    void recievedUsersList(uint limit, uint offset, uint totalCount, UserVectorPtr users);
    
public:
    const QMap<QString, QString>& extraHeaders() const { return m_extraHeaders; }
    const QUrl& baseUrl() const { return m_baseUrl; }
    QNetworkAccessManager   *accessManager() { return &m_accessManager; }
    
public slots:
    Q_INVOKABLE void listProjects(uint offset = 0);
    Q_INVOKABLE void listIssues(uint offset = 0);
    Q_INVOKABLE void listTimeEntries(uint offset = 0);
    Q_INVOKABLE void listUsers(uint offset = 0);
};

#endif // REDMINEMANAGER_H
