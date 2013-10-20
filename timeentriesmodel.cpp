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

#include "timeentriesmodel.h"
#include "redminemanager.h"
#include <cassert>
#include <QDebug>

TimeEntriesModel::TimeEntriesModel(RedMineManager* manager, QObject* parent): 
    QAbstractTableModel(parent),
    m_manager(manager)
{
    connect(m_manager, SIGNAL(recievedTimeEntriesList(int,int,int,TimeEntryVectorPtr)), this, SLOT(setTimeEntriesData(int,int,int,TimeEntryVectorPtr)));
}

int TimeEntriesModel::columnCount(const QModelIndex& parent) const
{
    return 9;
}

int TimeEntriesModel::rowCount(const QModelIndex& parent) const
{
    return m_timeEntriesData ? m_timeEntriesData->size() : 0;
}

QVariant TimeEntriesModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        assert(index.row() <= m_timeEntriesData->size());
        const auto &row = (*m_timeEntriesData)[index.row()];
        
        switch(index.column())
        {
            case 0: return row.id();
            case 1: return row.project().name();
            case 2: return row.comments();
            case 3: return row.activity().name();
            case 4: return row.createdOn();
            case 5: return row.updatedOn();
            case 6: return row.spentOn();
            case 7: return row.user().name();
            case 8: return row.issue();
        }
    }
    return QVariant();
}

bool TimeEntriesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
#warning TODO
    return false;
}

QVariant TimeEntriesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(section)
        {
            case 0: return "id";
            case 1: return "project";
            case 2: return "comments";
            case 3: return "activity";
            case 4: return "createdOn";
            case 5: return "updatedOn";
            case 6: return "spentOn";
            case 7: return "user";
            case 8: return "issue";
        }
    }
    return QVariant();
}

bool TimeEntriesModel::insertRows(int row, int count, const QModelIndex& parent)
{
#warning TODO
    return false;
}

bool TimeEntriesModel::removeRows(int row, int count, const QModelIndex& parent)
{
#warning TODO
    return false;
}

void TimeEntriesModel::setTimeEntriesData(int limit, int offset, int totalCount, TimeEntryVectorPtr timeEntries)
{
    int last = offset + limit - 1;
    if (last > totalCount)
        last = totalCount - 1;
    
    beginInsertRows(QModelIndex(), offset, last);
    
    if (!m_timeEntriesData)
        m_timeEntriesData = timeEntries;
    else
    {
        auto data = m_timeEntriesData.get();
        
        if (totalCount > 0)
            data->reserve(totalCount);
        
        qDebug() << offset << "," << data->size();
        
        if (offset >= data->size())
        {
            for(auto &it : *timeEntries)
            {
                data->push_back(std::move(it));
            }
        }
    }
    
    if (m_timeEntriesData->size() < totalCount)
        m_manager->listTimeEntries(m_timeEntriesData->size());
    
    endInsertRows();
}

bool TimeEntriesModel::canFetchMore(const QModelIndex& parent) const
{
    return m_canFetchMore;
}

void TimeEntriesModel::fetchMore(const QModelIndex& parent)
{
    if (m_timeEntriesData && m_timeEntriesData->size())
    {
        m_manager->listTimeEntries(m_timeEntriesData->size());
    }
}

