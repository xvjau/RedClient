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

#ifndef ISSUESMODEL_H
#define ISSUESMODEL_H

#include <QAbstractTableModel>

#include "rmissue.h"

class IssuesModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    explicit IssuesModel(RedMineManager  *manager, QObject* parent = 0);
    
    virtual int columnCount(const QModelIndex&) const override;
    virtual int rowCount(const QModelIndex&) const override;
    
    virtual QVariant data(const QModelIndex& index, int role) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    
    virtual bool insertRows(int row, int count, const QModelIndex&) override;
    virtual bool removeRows(int row, int count, const QModelIndex&) override;
    
protected:
    RedMineManager  *m_manager = nullptr;
    IssueVectorPtr  m_issuesData;

    QModelIndex m_selected;
    
public slots:
    void setIssuesData(uint limit, uint offset, uint totalCount, IssueVectorPtr issues);
    Q_INVOKABLE void setSelected(QModelIndex _index);
};

#endif // ISSUESMODEL_H
