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

#ifndef RMREQUEST_H
#define RMREQUEST_H

#include <QObject>
#include <QNetworkReply>
#include <QList>
#include <QSslError>
#include <QJsonDocument>

class RedMineManager;
class QJsonDocument;

class RMRequest : public QObject
{
    Q_OBJECT
public:
    explicit RMRequest(RedMineManager *manager);
    
protected:
    RedMineManager  *m_manager;
    QNetworkReply   *m_reply = nullptr;
    
    QJsonDocument   m_jsonDocument;
    
    virtual QUrl buildUrl() = 0;
    
protected slots:
    virtual void replyFinished(QNetworkReply* reply);
    virtual void requestReadyRead();
    virtual void requestError(QNetworkReply::NetworkError error);
    virtual void requestSslErrors(QList<QSslError> errorList);
    
    bool checkIfReplyIsForMe(QNetworkReply *reply)
    {
        return reply->request().originatingObject() == this;
    }
public:
    virtual void start();
    
signals:
    void done();
};

#endif // RMREQUEST_H
