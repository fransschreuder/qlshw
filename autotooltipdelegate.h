#ifndef AUTOTOOLTIPDELEGATE_H
#define AUTOTOOLTIPDELEGATE_H
#include <QObject>
#include <QStyledItemDelegate>
#include <QHelpEvent>
#include <QAbstractItemView>
#include <QStyleOptionViewItem>

class AutoToolTipDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    AutoToolTipDelegate( QObject* parent );
    ~AutoToolTipDelegate();

public slots:
    bool helpEvent( QHelpEvent* e, QAbstractItemView* view, const QStyleOptionViewItem& option,
        const QModelIndex& index );
};

#endif // AUTOTOOLTIPDELEGATE_H
