#include "treemodel.h"
#include <QStringList>
#include <QDebug>
#include <QIcon>

TreeModel::TreeModel(const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Hardware"<<"Value";
    rootItem = new TreeItem(rootData, QIcon());
    setupModelData(data.split(QString("\n")), rootItem);
}



TreeModel::~TreeModel()
{
    delete rootItem;
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        QString line = lines[number];
        QIcon icon;
        if(line.contains("  *-"))
        {
           line.replace(QString("  *-"), QString("    "));
           if(line.contains("core"))icon=QIcon(":/icons/motherboard.svg");
           if(line.contains("memory"))icon=QIcon::fromTheme("media-memory");
           if(line.contains("cache"))icon=QIcon::fromTheme("media-memory");
           if(line.contains("bank"))icon=QIcon::fromTheme("media-memory");
           if(line.contains("cpu"))icon=QIcon(":/icons/cpu.svg");
           if(line.contains("multimedia"))icon=QIcon::fromTheme("audio-card");
           if(line.contains("display"))icon=QIcon::fromTheme("video-display");
           if(line.contains("usb"))icon=QIcon(":/icons/stock_usb.svg");
           if(line.contains("network"))icon=QIcon(":/icons/network.svg");
           if(line.contains("pci"))icon=QIcon(":/icons/pcie.svg");
           if(line.contains("isa"))icon=QIcon(":/icons/pcie.svg");
           if(line.contains("storage"))icon=QIcon::fromTheme("drive-harddisk");
           if(line.contains("disk"))icon=QIcon::fromTheme("drive-harddisk");
           if(line.contains("volume"))icon=QIcon::fromTheme("drive-harddisk");
        }
        int position = 0;
        while (position < line.length()) {
            if (line.mid(position, 1) != " ")
                break;
            position++;
        }

        QString lineData = line.mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings;
            columnStrings << lineData.section(":",0,0)<<lineData.section(":",1);// QString::SkipEmptyParts);
            QList<QVariant> columnData;
            //columnData<<icon;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(columnData, icon, parents.last()));
        }

        number++;
    }
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::DecorationRole)
    {
        return item->getIcon();

    }
    if (role != Qt::DisplayRole)
        return QVariant();



    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}






















