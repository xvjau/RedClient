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

#ifndef RMUSER_H
#define RMUSER_H

#include <QObject>
#include <QJsonValueRef>

#include <vector>
#include <memory>

class RedMineManager;
class RMUser;

typedef std::shared_ptr<std::vector<RMUser>> UserVectorPtr;

class RMUser : public QObject
{
    Q_OBJECT
public:
    enum Status
    {
        usAnonymous  = 0,
        usActive     = 1,
        usRegistered = 2,
        usLocked     = 3
    };
    
    RMUser(RMUser &&other);
    RMUser(const QJsonValueRef &json, RedMineManager *manager, QObject *parent = nullptr);
    explicit RMUser(RedMineManager *manager, QObject *parent = nullptr);

protected:
    RedMineManager *m_manager = nullptr;
    
    int m_id = 0;
    QString m_login;
    QString m_firstName;
    QString m_lastName;
    QString m_email;
    int m_authSourceId = 0;

public:
    int id() const { return m_id; }
    const QString& login() const { return m_login; }
    const QString& firstName() const { return m_firstName; }
    const QString& lastName() const { return m_lastName; }
    const QString& email() const { return m_email; }
    int authSourceId() const { return m_authSourceId; }
};

#endif // RMUSER_H
