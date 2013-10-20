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

#ifndef RMREQISSUES_H
#define RMREQISSUES_H

#include <QUrlQuery>

#include "rmrequest.h"
#include "rmissue.h"

class RMReqIssues : public RMRequest
{
    Q_OBJECT
    
public:
    struct Filters
    {
        QVariant projectId;
        QVariant subProjectId;
        QVariant trackerId;
        RMIssue::Status status = RMIssue::isAll;
        QVariant assignedTo;
    };
    
    explicit RMReqIssues(RedMineManager* manager, Filters filters): 
        RMRequest(manager),
        m_filters(filters)
    {
    }
    
protected:
    Filters m_filters;
    
    virtual QUrl buildUrl() override
    {
        QUrl result(m_manager->baseUrl());
        result.setPath("/issues.json");
        
        QUrlQuery query;
        
        if (!m_filters.projectId.isNull())
        {
            query.addQueryItem("project_id", m_filters.projectId.toString());
            
            if (!m_filters.subProjectId.isNull())
                query.addQueryItem("subproject_id", m_filters.subProjectId.toString());
        }
        
        if (!m_filters.trackerId.isNull())
            query.addQueryItem("tracker_id", m_filters.trackerId.toString());
        
        if (m_filters.status != RMIssue::isAll)
            query.addQueryItem("status_id", (m_filters.status == RMIssue::isOpen ? "open" : "closed"));
        
        if (!m_filters.assignedTo.isNull())
            query.addQueryItem("assigned_to_id", m_filters.assignedTo.toString());
        
        result.setQuery(query);
        
        qDebug() << result.toString();
        
        return result;
    }
    
    virtual void replyFinished(QNetworkReply* reply) override
    {
        processReply<RMIssue>(reply, "issues", 
                              [this] (uint limit, uint offset, uint totalCount, const IssueVectorPtr &data)
                              { emit recievedIssueList(limit, offset, totalCount, data); });
    }

signals:
    void recievedIssueList(uint limit, uint offset, uint totalCount, IssueVectorPtr);
};

#endif // RMREQISSUES_H
