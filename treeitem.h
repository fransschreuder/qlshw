#ifndef TREEITEM_H
#define TREEITEM_H
#include <QList>
#include <QVariant>
#include <QIcon>

class TreeItem
{
public:
    TreeItem(const QList<QVariant> &data, QIcon i, TreeItem *parent = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parent();
    QIcon getIcon() const{return icon;}
    void setIcon(QIcon i){icon = i;}

private:
    QList<TreeItem*> childItems;
    QList<QVariant> itemData;
    QIcon icon;
    TreeItem *parentItem;
};

#endif // TREEITEM_H
