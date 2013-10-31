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

#include "redminemanager.h"

#include <unordered_map>
#include <QFont>
#include <cassert>

IssuesModel::IssuesModel(RedMineManager* manager, QObject* parent): 
    QAbstractTableModel(parent),
    m_manager(manager)
{
}

void IssuesModel::setIssuesData(uint limit, uint offset, uint totalCount, IssueVectorPtr issues)
{
    uint last = offset + limit - 1;
    if (last > totalCount)
        last = totalCount - 1;
    
    beginInsertRows(QModelIndex(), offset, last);
    
    if (!m_issuesData)
        m_issuesData = issues;
    else
    {
        auto data = m_issuesData.get();
        
        if (totalCount > 0)
            data->reserve(totalCount);
        
        if (offset >= data->size())
        {
            for(auto &it : *issues)
            {
                data->push_back(std::move(it));
            }
        }
    }
    
    if (m_issuesData->size() < totalCount)
        m_manager->listIssues(m_issuesData->size());
    
    endInsertRows();
}

int IssuesModel::columnCount(const QModelIndex& ) const
{
    return 13;
}

int IssuesModel::rowCount(const QModelIndex& ) const
{
    return m_issuesData ? m_issuesData->size() : 0;
}

QVariant IssuesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
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
        else
        {
            assert(section <= m_issuesData->size());
            const auto &row = (*m_issuesData)[section];
            
            return row.id();
        }
    }
    return QVariant();
}

QVariant IssuesModel::data(const QModelIndex& index, int role) const
{
    switch(role)
    {
        case Qt::FontRole:
            if (index.row() == m_selected.row() && index.parent() == m_selected.parent())
            {
                QFont result;
                result.setBold(true);
                return result;
            }
            break;
            
        case Qt::DisplayRole:
        {
            assert(index.row() <= m_issuesData->size());
            const auto &row = (*m_issuesData)[index.row()];
            
            switch(index.column())
            {
                case 0: return row.id();
                case 1: return row.subject();
                case 2: return row.status().name();
                case 3: return row.createdOn();
                case 4: return row.author().name();
                case 5: return row.project().name();
                case 6: return row.tracker().name();
                case 7: return row.assignedTo().name();
                case 8: return row.updatedOn();
                case 9: return row.startDate();
                case 10: return row.doneRatio();
                case 11: return row.description();
                case 12: return row.priority().name();   
            }
            break;
        }
    }
    return QVariant();
}

bool IssuesModel::insertRows(int row, int count, const QModelIndex& )
{
    return false;
}

bool IssuesModel::removeRows(int row, int count, const QModelIndex& )
{
    return false;
}

bool IssuesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return false;
}

void IssuesModel::setSelected(QModelIndex _index)
{
    QModelIndex oldTopLeft, oldBottomRight;
    
    if (m_selected.isValid())
    {
        oldTopLeft = index(m_selected.row(), 0, m_selected.parent());
        oldBottomRight = index(m_selected.row(), columnCount(m_selected.parent()) - 1, m_selected.parent());
    }
    
    m_selected = _index;
    
    QModelIndex topLeft = index(m_selected.row(), 0, m_selected.parent());
    QModelIndex bottomRight = index(m_selected.row(), columnCount(m_selected.parent()) - 1, m_selected.parent());
    
    if (oldTopLeft.isValid())
        emit dataChanged(oldTopLeft, oldBottomRight, {Qt::FontRole});
    
    emit dataChanged(topLeft, bottomRight, {Qt::FontRole});
}
