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

#include "rmrequest.h"
#include "redminemanager.h"

#include <QApplication>
#include <QDebug>
#include <QJsonDocument>

RMRequest::RMRequest(RedMineManager *manager): 
    QObject(manager),
    m_manager(manager)
{
}

void RMRequest::requestError(QNetworkReply::NetworkError error)
{
    
#define STRCASE(CASE) \
    case QNetworkReply:: CASE : str = # CASE ; break;
    
    QString str;
    
    switch(error)
    {
        STRCASE(NoError);
        
        STRCASE(ConnectionRefusedError);
        STRCASE(RemoteHostClosedError);
        STRCASE(HostNotFoundError);
        STRCASE(TimeoutError);
        STRCASE(OperationCanceledError);
        STRCASE(SslHandshakeFailedError);
        STRCASE(TemporaryNetworkFailureError);
        STRCASE(UnknownNetworkError);

        // proxy errors (101-199):
        STRCASE(ProxyConnectionRefusedError);
        STRCASE(ProxyConnectionClosedError);
        STRCASE(ProxyNotFoundError);
        STRCASE(ProxyTimeoutError);
        STRCASE(ProxyAuthenticationRequiredError);
        STRCASE(UnknownProxyError);
        
        // content errors (201-299):
        STRCASE(ContentAccessDenied);
        STRCASE(ContentOperationNotPermittedError);
        STRCASE(ContentNotFoundError);
        STRCASE(AuthenticationRequiredError);
        STRCASE(ContentReSendError);
        STRCASE(UnknownContentError);
        
        // protocol errors
        STRCASE(ProtocolUnknownError);
        STRCASE(ProtocolInvalidOperationError);
        STRCASE(ProtocolFailure);
        
        STRCASE(NetworkSessionFailedError);
        STRCASE(BackgroundRequestNotAllowedError);
    }
    
    if (str.isEmpty())
        qDebug() << "Unknown Network Request error: " << error;
    else
        qDebug() << "Network Request error: (" << error << ") - " << str;
}

void RMRequest::requestSslErrors(QList< QSslError > errorList)
{
    m_reply->ignoreSslErrors(errorList);
    
    for(auto error: errorList)
        qDebug() << "SSL Network Request error:" << error.errorString();
}

void RMRequest::requestReadyRead()
{
    qDebug() << m_reply->readAll();
}

void RMRequest::replyFinished(QNetworkReply* reply)
{
    m_jsonDocument = QJsonDocument::fromBinaryData(reply->readAll());
    reply->deleteLater();
}

void RMRequest::start()
{
    connect(m_manager->accessManager(), SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    
    QNetworkRequest request;
    request.setUrl(buildUrl());
    request.setRawHeader("User-Agent", QApplication::applicationName().toUtf8());
    
    m_reply = m_manager->accessManager()->get(request);
    connect(m_reply, SIGNAL(readyRead()), this, SLOT(requestReadyRead()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(requestError(QNetworkReply::NetworkError)));
    connect(m_reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(requestSslErrors(QList<QSslError>)));
}


#include "rmrequest.moc"
