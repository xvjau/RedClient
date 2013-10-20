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

#ifndef RMREQTIMEENTRY_H
#define RMREQTIMEENTRY_H

#include "rmrequest.h"
#include "rmtimeentry.h"

#include <QUrlQuery>

class RMReqTimeEntry : public RMRequest
{
    Q_OBJECT

public:
    struct Filters
    {
        int offset = 0;
    };
    
    explicit RMReqTimeEntry(RedMineManager* manager, Filters filters): 
        RMRequest(manager),
        m_filers(filters)
    {
    }
    
protected:
    Filters m_filers;
    
    virtual QUrl buildUrl()
    {
        QUrl result(m_manager->baseUrl());
        result.setPath("/time_entries.json");
        
        QUrlQuery query;
        
        if (m_filers.offset)
            query.addQueryItem("offset", QString::number(m_filers.offset));
        
        result.setQuery(query);
        
        return result;
    }
    
    virtual void replyFinished(QNetworkReply* reply) override
    {
        processReply<RMTimeEntry>(reply, "time_entries", 
                                  [this] (int limit, int offset, int totalCount, const TimeEntryVectorPtr &data)
                                  { emit recievedTimeEntryList(limit, offset, totalCount, data); });
    }

signals:
    void recievedTimeEntryList(int limit, int offset, int totalCount, TimeEntryVectorPtr);

};

#endif // RMREQTIMEENTRY_H
