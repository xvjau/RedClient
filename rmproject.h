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

#ifndef RMPROJECTS_H
#define RMPROJECTS_H

#include <QObject>
#include <QDateTime>
#include <unordered_map>
#include <QSharedPointer>

class RedMineManager;
class QJsonValueRef;
class RMProject;

typedef QSharedPointer<std::unordered_map<int, RMProject>> ProjectMapPtr;

class RMProject : public QObject
{
    Q_OBJECT

public:
    RMProject(RMProject &&other);
    RMProject(const QJsonValueRef &json, RedMineManager *manager, QObject *parent = nullptr);
    explicit RMProject(RedMineManager *manager, QObject *parent = nullptr);
    
protected:
    RedMineManager *m_manager;
    
    int         m_id;
    QDateTime   m_createdOn;
    QDateTime   m_updatedOn;
    QString     m_identifier;
    QString     m_name;
    QString     m_description;
    
    int         m_parentProjectId = 0;
    
public:
    int         id() const { return m_id; }
    QDateTime   createdOn() const { return m_createdOn; }
    QDateTime   updatedOn() const { return m_updatedOn; }
    QString     identifier() const { return m_identifier; }
    QString     name() const { return m_name; }
    QString     description() const { return m_description; }
    int         parentProjectId() const { return m_parentProjectId; }
};

#endif // RMPROJECTS_H
