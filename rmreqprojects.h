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

#ifndef RMREQPROJECTS_H
#define RMREQPROJECTS_H

#include "rmrequest.h"
#include "rmproject.h"

#include <QMap>

class RMReqProjects : public RMRequest
{
    Q_OBJECT
public:
    explicit RMReqProjects(RedMineManager *manager);
    
protected:
    virtual QUrl buildUrl();
    
    virtual void replyFinished(QNetworkReply* reply);
    
    QMap<int, RMProject> m_projects;
};

#endif // RMREQPROJECTS_H
