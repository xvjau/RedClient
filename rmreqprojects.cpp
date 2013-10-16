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

#include "rmreqprojects.h"
#include "redminemanager.h"

#include <memory>

#include <QJsonArray>
#include <QJsonObject>

#include <cassert>

RMReqProjects::RMReqProjects(RedMineManager* manager): 
    RMRequest(manager)
{

}

QUrl RMReqProjects::buildUrl()
{
    QUrl result(m_manager->baseUrl());
    result.setPath("/projects.json");
    return result;
}

void RMReqProjects::replyFinished(QNetworkReply* reply)
{
    RMRequest::replyFinished(reply);
    
    auto projects = std::make_shared<std::vector<RMProject>>();
    
    QJsonObject obj = m_jsonDocument.object();
    
    auto it = obj.find("projects");
    
    if(it != obj.end())
    {
        auto list = it.value().toArray();
        
        for(auto project : list)
        {
            RMProject p(project, m_manager);
            projects->push_back(std::move(p));
        }
    }
    
    emit recievedProjectList(projects);
    deleteLater();
}
