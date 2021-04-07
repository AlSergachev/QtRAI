#ifndef QTERRORLIST_H
#define QTERRORLIST_H

#include <QWidget>
#include <QVector>
#include "ui_qterrorlist.h"

namespace Ui {
class QtErrorList;
}

class QtErrorList : public QWidget
{
    Q_OBJECT

public:
    explicit QtErrorList(QVector <QString>& error_list, QWidget *parent = nullptr);
    ~QtErrorList();

private:
    Ui::QtErrorList *ui;
};

#endif // QTERRORLIST_H
