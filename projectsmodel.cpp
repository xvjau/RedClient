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

#include "projectsmodel.h"

#include <unordered_map>

#include <cassert>

class ProjectsModelItem: public AbstractModelItem 
{
private:
    RMProject m_project;
public:
    ProjectsModelItem(RMProject &&_project, AbstractModelItem *_parent = nullptr):
        AbstractModelItem(_parent),
        m_project(std::move(_project))
    {
    }
        
    virtual int columnCount() const { return 7; }
    
    virtual QVariant data(int _col, int _role = Qt::DisplayRole) const 
    {
        Q_UNUSED(_role);
        
        switch(_col)
        {
            case 0: return m_project.id(); 
            case 1: return m_project.createdOn();
            case 2: return m_project.updatedOn();
            case 3: return m_project.identifier();
            case 4: return m_project.name();
            case 5: return m_project.description();
            case 6: return m_project.parentProjectId();
        }
        return QVariant();
    }
    
    virtual bool setData(int _col, const QVariant &_value) 
    {
#warning TODO Update project
        return false;
    }
};

ProjectsModel::ProjectsModel(QObject* parent): 
    AbstractTreeModel(parent)
{
}

void ProjectsModel::setProjectData(uint limit, uint offset, uint totalCount, ProjectVectorPtr projectList)
{
#warning TODO Allow for multiple HTTP requests
    // clear data
    m_rootItem = std::make_shared<AbstractModelItem>();
    
    auto &data = *projectList.get();
    
    std::unordered_map<int, std::shared_ptr<AbstractModelItem>> cache;
    
    while(!data.empty())
    {
        std::shared_ptr<AbstractModelItem> parent;
        
        auto it = data.begin();
        
        DO_NEXT:
        
        if (it->parentProjectId())
        {
            auto itParent = cache.find(it->parentProjectId());
            if (itParent != cache.end())
                parent = itParent->second;
            else
            {
                // Skip this project, since its parent hasn't been loaded yet
                it++;
                goto DO_NEXT;
            }
        }
        else
            parent = m_rootItem;
        
        auto child = std::make_shared<ProjectsModelItem>(std::move(*it), parent.get());
        child->m_row = parent->m_children.size();
        
        parent->m_children.push_back(child);
        
        cache.insert(std::make_pair(it->id(), child));
        
        data.erase(it);
    }
}

QVariant ProjectsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        assert(section < 7);
        
        switch(section)
        {
            case 0: return tr("id"); 
            case 1: return tr("createdOn");
            case 2: return tr("updatedOn");
            case 3: return tr("identifier");
            case 4: return tr("name");
            case 5: return tr("description");
            case 6: return tr("parentProjectId");
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}


