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

#ifndef RMREQUSERS_H
#define RMREQUSERS_H

#include "rmrequest.h"
#include "rmuser.h"

class RMReqUsers : public RMRequest
{
    Q_OBJECT
    
public:
    struct Filters
    {
        RMUser::Status status = RMUser::usActive;
        QString name;
        int groupId = 0;
    };
    
    explicit RMReqUsers(RedMineManager* manager, Filters filters): 
        RMRequest(manager),
        m_filters(filters)
    {}
    
protected:
    Filters m_filters;
    
    virtual QUrl buildUrl() override
    {
        QUrl result(m_manager->baseUrl());
        result.setPath("/users.json");
        return result;
    }
    
    virtual void replyFinished(QNetworkReply* reply) override
    {
        processReply<RMUser>(reply, "users", 
                                [this] (uint limit, uint offset, uint totalCount, const UserVectorPtr &data)
                                { emit recievedUserList(limit, offset, totalCount, data); });
    }
    
signals:
    void recievedUserList(uint limit, uint offset, uint totalCount, UserVectorPtr users);
};

#endif // RMREQUSERS_H
