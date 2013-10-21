#ifndef ABSTRACTTREEMODEL_H
#define ABSTRACTTREEMODEL_H

#include <QAbstractItemModel>
#include <memory>
#include <functional>

class AbstractModelItem;
typedef std::shared_ptr<AbstractModelItem> AbstractModelItemPtr;
typedef std::vector<AbstractModelItemPtr> AbstractModelItemVector;

class AbstractModelItem 
{
public:
    AbstractModelItem(AbstractModelItem *_parent = nullptr):m_parent(_parent), m_row(0) {}
    
    AbstractModelItem *m_parent;
    AbstractModelItemVector m_children; 
    int m_row;
    
    int rowCount() const { return m_children.size(); }
    virtual int columnCount() const { return 1; }
    virtual QVariant data(int _col, int _role = Qt::DisplayRole) const { Q_UNUSED(_col); Q_UNUSED(_role); return QVariant(); }
    virtual bool setData(int _col, const QVariant &_value) { Q_UNUSED(_col); Q_UNUSED(_value); return false; }
};

class AbstractTreeModel : public QAbstractItemModel
{
    Q_OBJECT

protected:
    explicit AbstractTreeModel(QObject* parent = 0);
    
public:
    explicit AbstractTreeModel(const AbstractTreeModel &_other);
    
    virtual AbstractTreeModel &operator=(const AbstractTreeModel &_other);
    
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;

    virtual QVariant data(const QModelIndex &index, int role) const override;   
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual QModelIndex index(int _row, int _col, const QModelIndex &_parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    
    virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    
protected:
    AbstractModelItemPtr m_rootItem;
    
    typedef std::function<bool(const AbstractModelItemPtr&, const AbstractModelItemPtr&)> SortComparer;
    virtual void sort(AbstractModelItem *_item, Qt::SortOrder order, const AbstractTreeModel::SortComparer &comparer);
};

#endif // ABSTRACTTREEMODEL_H
