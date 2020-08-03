#pragma once

#include <QWidget>
#include "ui_QtErrorList.h"
#include <QVector>

class QtErrorList : public QWidget
{
	Q_OBJECT

public:
	QtErrorList(QVector <QString>& error_list, QWidget *parent = Q_NULLPTR);
	~QtErrorList();

private:
	Ui::QtErrorList ui;
};
