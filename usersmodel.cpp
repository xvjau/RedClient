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

#include "usersmodel.h"
#include "redminemanager.h"

#include <cassert>

UsersModel::UsersModel(RedMineManager* manager, QObject* parent): 
    QAbstractTableModel(parent),
    m_manager(manager)
{

}

int UsersModel::columnCount(const QModelIndex& parent) const
{
    return 6;
}

int UsersModel::rowCount(const QModelIndex& parent) const
{
    return m_usersData ? m_usersData->size() : 0;
}

QVariant UsersModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        assert(index.row() <= m_usersData->size());
        const auto &row = (*m_usersData)[index.row()];
        
        switch(index.column())
        {
            case 0: return row.id();
            case 1: return row.login();
            case 2: return row.firstName();
            case 3: return row.lastName();
            case 4: return row.email();
            case 5: return row.authSourceId();
        }
    }
    return QVariant();
}

bool UsersModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return false;
}

QVariant UsersModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch(section)
            {
                case 0: return "id";
                case 1: return "login";
                case 2: return "firstName";
                case 3: return "lastName";
                case 4: return "email";
                case 5: return "authSourceId";
            }
        }
        else
        {
            assert(section < m_usersData->size());
            const auto &row = (*m_usersData)[section];
            
            return row.id();
        }
    }
    return QVariant();
}

QHash< int, QByteArray > UsersModel::roleNames() const
{
    QHash<int, QByteArray> result;
    result.insert(crId, "id");
    result.insert(crLogin, "login");
    result.insert(crFirstName, "firstName");
    result.insert(crLastName, "lastName");
    result.insert(crEmail, "email");
    result.insert(crAuthSourceId, "authSourceId");
    
    return result;
}

void UsersModel::setUsersData(uint limit, uint offset, uint totalCount, UserVectorPtr users)
{
    uint last = offset + limit - 1;
    if (last > totalCount)
        last = totalCount - 1;
    
    beginInsertRows(QModelIndex(), offset, last);
    
    if (!m_usersData)
        m_usersData = users;
    else
    {
        auto data = m_usersData.get();
        
        if (totalCount > 0)
            data->reserve(totalCount);
        
        if (offset >= data->size())
        {
            for(auto &it : *users)
            {
                data->push_back(std::move(it));
            }
        }
    }
    
    if (m_usersData->size() < totalCount)
        m_manager->listUsers(m_usersData->size());
    
    endInsertRows();
}
