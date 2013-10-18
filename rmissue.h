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

#ifndef RMISSUE_H
#define RMISSUE_H

#include <QObject>
#include <QJsonValueRef>
#include <QJsonObject>
#include <QDateTime>

#include <vector>
#include <memory>

class RedMineManager;
class RMIssue;

typedef std::shared_ptr<std::vector<RMIssue>> IssueVectorPtr;

class RMIssue: public QObject
{
    Q_OBJECT
    
public:
    enum Status
    {
        isAll = 0,
        isOpen,
        isClosed
    };
    
    RMIssue(RMIssue &&other);
    RMIssue(const QJsonValueRef &json, RedMineManager *manager, QObject *parent = nullptr);
    explicit RMIssue(RedMineManager *manager, QObject *parent = nullptr);

protected:
    RedMineManager *m_manager = nullptr;
    
    int m_id = 0;
    QString m_subject;
    RMObjectSummary m_status;
    QDateTime m_createdOn;
    RMObjectSummary m_author;
    RMObjectSummary m_project;
    RMObjectSummary m_tracker;
    RMObjectSummary m_assignedTo;
    QDateTime m_updatedOn;
    QDateTime m_startDate;
    double m_doneRatio = 0;
    QString m_description;
    RMObjectSummary m_priority;

public:
    int id() const { return m_id; }
    const QString& subject() const { return m_subject; }
    const RMObjectSummary& status() const { return m_status; }
    const QDateTime& createdOn() const { return m_createdOn; }
    const RMObjectSummary& author() const { return m_author; }
    const RMObjectSummary& project() const { return m_project; }
    const RMObjectSummary& tracker() const { return m_tracker; }
    const RMObjectSummary& assignedTo() const { return m_assignedTo; }
    const QDateTime&  updatedOn() const { return m_updatedOn; }
    const QDateTime&  startDate() const { return m_startDate; }
    double doneRatio() const { return m_doneRatio; }
    const QString& description() const { return m_description; }
    const RMObjectSummary& priority() const { return m_priority; }
};

#endif // RMISSUE_H
