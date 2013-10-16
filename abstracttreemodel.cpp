#include "abstracttreemodel.h"
#include <iostream>

AbstractTreeModel::AbstractTreeModel(QObject* parent): QAbstractItemModel(parent),
    m_rootItem(std::make_shared<AbstractModelItem>())
{
}

AbstractTreeModel::AbstractTreeModel(const AbstractTreeModel& _other): QAbstractItemModel()
{
    m_rootItem = const_cast<AbstractTreeModel*>(&_other)->m_rootItem;
}

AbstractTreeModel& AbstractTreeModel::operator=(const AbstractTreeModel& _other)
{
    m_rootItem = const_cast<AbstractTreeModel*>(&_other)->m_rootItem;
    return *this;
}

int AbstractTreeModel::columnCount(const QModelIndex& parent) const
{
    if(parent.isValid())
    {
        auto item = static_cast<AbstractModelItem*>(parent.internalPointer());
        if(item)
            return item->columnCount();
    }
    
    if (m_rootItem->m_children.size())
        return m_rootItem->m_children.at(0)->columnCount();
    else
        return m_rootItem->columnCount();
}

QVariant AbstractTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
         return QVariant();

    int col = index.column();
    if(role > Qt::UserRole)
        col = role;
    else if (role != Qt::DisplayRole)
        return QVariant();

    auto item = static_cast<AbstractModelItem*>(index.internalPointer());

    return item->data(col);
}

bool AbstractTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
         return false;

    int col = index.column();
    if(role > Qt::UserRole)
        col = role;

    auto item = static_cast<AbstractModelItem*>(index.internalPointer());

    
    return item->setData(col, value);
}

QModelIndex AbstractTreeModel::index(int _row, int _col, const QModelIndex& _parent) const
{
    if (!hasIndex(_row, _col, _parent))
         return QModelIndex();

     AbstractModelItem *parentItem;

     if (!_parent.isValid())
         parentItem = m_rootItem.get();
     else
         parentItem = static_cast<AbstractModelItem*>(_parent.internalPointer());

     auto childItem = parentItem->m_children.at(_row);
     if (childItem)
         return createIndex(_row, _col, childItem.get());
     else
         return QModelIndex();
}

QModelIndex AbstractTreeModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
         return QModelIndex();

     auto *childItem = static_cast<AbstractModelItem*>(child.internalPointer());
     auto *parentItem = childItem->m_parent;

     if (parentItem == m_rootItem.get())
         return QModelIndex();

     return createIndex(parentItem->m_row, 0, parentItem);
}

int AbstractTreeModel::rowCount(const QModelIndex& parent) const
{
    if(parent.isValid())
    {
        auto item = static_cast<AbstractModelItem*>(parent.internalPointer());
        if(item)
            return item->rowCount();
    }
    return m_rootItem->m_children.size();
}

void AbstractTreeModel::sort(int column, Qt::SortOrder order)
{
    auto compare = [=](const AbstractModelItemPtr lhs, const AbstractModelItemPtr rhs) -> bool 
    { 
        return lhs->data(column).toString().compare(rhs->data(column).toString()) < 0;
    };
    
    sort(m_rootItem.get(), order, compare);
}

void AbstractTreeModel::sort(AbstractModelItem* _item, Qt::SortOrder order, const AbstractTreeModel::SortComparer &comparer)
{
    auto &children = _item->m_children;
    
    int colCount = _item->columnCount();
    int rowCount = children.size();
    
    if (rowCount > 0)
    {
        if (order == Qt::AscendingOrder)
            std::sort(children.begin(), children.end(), comparer);
        else
            std::sort(children.rbegin(), children.rend(), comparer);
        
        emit dataChanged(index(0, 0), index(rowCount, colCount));
        
        for(auto it = children.begin(), end = children.end(); it != end; it++)
            sort(it->get(), order, comparer);
    }
}
