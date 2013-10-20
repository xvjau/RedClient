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

#ifndef RMTIMEENTRY_H
#define RMTIMEENTRY_H

#include "rmobjectsummary.h"

#include <QDateTime>
#include <QString>
#include <QJsonValueRef>

#include <memory>
#include <vector>

class RMTimeEntry;
class RedMineManager;

typedef std::shared_ptr<std::vector<RMTimeEntry>> TimeEntryVectorPtr;

class RMTimeEntry: public QObject
{
    Q_OBJECT
    
public:
    RMTimeEntry();
    RMTimeEntry(RMTimeEntry &&other);
    RMTimeEntry(const QJsonValueRef &json, RedMineManager *manager, QObject *parent = nullptr);
    explicit RMTimeEntry(RedMineManager *manager, QObject *parent = nullptr);
    
protected:
    RedMineManager *m_manager = nullptr;
    
    int m_id = 0;
    RMObjectSummary m_project;
    QString m_comments;
    RMObjectSummary m_activity;
    QDateTime m_createdOn;
    QDateTime m_updatedOn;
    QDateTime m_spentOn;
    RMObjectSummary m_user;
    int m_issue = 0;
    
public:
    int id() const { return m_id; };
    const RMObjectSummary& project() const { return m_project; };
    const QString& comments() const { return m_comments; };
    const RMObjectSummary& activity() const { return m_activity; };
    const QDateTime& createdOn() const { return m_createdOn; };
    const QDateTime& updatedOn() const { return m_updatedOn; };
    const QDateTime& spentOn() const { return m_spentOn; };
    const RMObjectSummary& user() const { return m_user; };
    int issue() const { return m_issue; };
};

#endif // RMTIMEENTRY_H
