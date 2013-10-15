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
#include <QNetworkAccessManager>

#include "rmproject.h"

class QNetworkAccessManager;

class RedMineManager : public QObject
{
    Q_OBJECT

public:
    RedMineManager(QUrl url);
    virtual ~RedMineManager();
    
private:
    QUrl                    m_baseUrl;
    QNetworkAccessManager   m_accessManager;
    
    bool                    m_loggedIn = false;
    QString                 m_login;
    QString                 m_password;
    
protected slots:
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    
signals:
    void responseListProjects(QList<RMProject> *projects);
    
public:
    bool loggedIn() { return m_loggedIn; }
    const QUrl& baseUrl() const { return m_baseUrl; }
    QNetworkAccessManager   *accessManager() { return &m_accessManager; }
    
public slots:
    void login(QString login, QString password);
    void listProjects();
};

#endif // REDMINEMANAGER_H
