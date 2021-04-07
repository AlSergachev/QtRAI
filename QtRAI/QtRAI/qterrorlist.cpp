#include "qterrorlist.h"

QtErrorList::QtErrorList(QVector <QString>& error_list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtErrorList)
{
    ui->setupUi(this);
    QString s_error_list = (QString::number(1) + "  " + error_list[0] + "\n");
        //ui->setupUi(this);
        for (int i = 1; i < error_list.size(); i++)
        {
            s_error_list += (QString::number(i+1) + "  " + error_list[i] + "\n");
        }
        ui->errors->setText(s_error_list);
}

QtErrorList::~QtErrorList()
{
    delete ui;
}
