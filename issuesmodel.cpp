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

#include "issuesmodel.h"

#include <unordered_map>

#include <cassert>

class IssuesModelItem: public AbstractModelItem 
{
private:
    RMIssue m_issue;
public:
    IssuesModelItem(RMIssue &&_issue, AbstractModelItem *_parent = nullptr):
    AbstractModelItem(_parent),
        m_issue(std::move(_issue))
    {
    }
       
    virtual int columnCount() const { return 13; }
    
    virtual QVariant data(int _col, int _role = Qt::DisplayRole) const 
    {
        Q_UNUSED(_role);
        
        switch(_col)
        {
            case 0: return m_issue.id();
            case 1: return m_issue.subject();
            case 2: return m_issue.status().name();
            case 3: return m_issue.createdOn();
            case 4: return m_issue.author().name();
            case 5: return m_issue.project().name();
            case 6: return m_issue.tracker().name();
            case 7: return m_issue.assignedTo().name();
            case 8: return m_issue.updatedOn();
            case 9: return m_issue.startDate();
            case 10: return m_issue.doneRatio();
            case 11: return m_issue.description();
            case 12: return m_issue.priority().name();
            
        }
        return QVariant();
    }
    
    virtual bool setData(int _col, const QVariant &_value) 
    {
        return false;
    }
};

IssuesModel::IssuesModel(QObject* parent): 
    AbstractTreeModel(parent)
{
}

void IssuesModel::setIssuesData(int limit, int offset, int totalCount, IssueVectorPtr issues)
{
#warning TODO Allow for multiple HTTP requests
    // clear data
    m_rootItem = std::make_shared<AbstractModelItem>();
    
    auto &data = *issues.get();
    
    int row = 0;
    
    for(auto &issue : data)
    {
        auto item = std::make_shared<IssuesModelItem>(std::move(issue), m_rootItem.get());
        item->m_row = row++;
        m_rootItem->m_children.push_back(std::move(item));
    }
}

QVariant IssuesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        assert(section < 13);
        
        switch(section)
        {
             case 0: return tr("id");
             case 1: return tr("subject");
             case 2: return tr("status");
             case 3: return tr("createdOn");
             case 4: return tr("author");
             case 5: return tr("project");
             case 6: return tr("tracker");
             case 7: return tr("assignedTo");
             case 8: return tr("updatedOn");
             case 9: return tr("startDate");
             case 10: return tr("doneRatio");
             case 11: return tr("description");
             case 12: return tr("priority");
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}
