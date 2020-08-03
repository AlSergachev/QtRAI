#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtRAI.h"
#include "QtResult.h"
#include "QtErrorList.h"
#include <QVector>
#include "qmessagebox.h"

using namespace std;

class QtRAI : public QMainWindow
{
    Q_OBJECT

private:
    Ui::QtRAI ui;
    int N = 3;
    int n;
    QString str_err;
    QVector <QString> error_list;

public:
    QtRAI(QWidget* parent = Q_NULLPTR);
    vector <Point> points;

public slots:
    void calculation();
    void changingNumberMeasurements(int& N);


signals:
    void valueChanged(int new_N);

private:
    QtResult* rWidget;
    QtErrorList* erWidget;
};

