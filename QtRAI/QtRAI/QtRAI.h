#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtRAI.h"
#include "QtResult.h"
#include "QtErrorList.h"
#include <QVector>
#include "qmessagebox.h"
#include <QGraphicsScene>
#include <QWheelEvent>

using namespace std;

class QtRAI : public QMainWindow
{
    Q_OBJECT

private:
    Ui::QtRAI ui;
    QGraphicsScene* scene = new QGraphicsScene;
    void SceneClear();
    void InputValidation();
    int N = 3;
    int n, rad;
    int error = 0;
    QString str_err;
    QVector <QString> error_list;

public:
    QtRAI(QWidget* parent = Q_NULLPTR);
    vector <Point> points;

public slots:
    void calculation();
    void changingNumberMeasurements(int& N);
    void showPoints(int value = 2);
    void clear_the_screen();
    void mouseWheelZoom(int step);
    void wheelEvent(QWheelEvent* event);


signals:
    void valueChanged(int new_N);
    

private:
    QtResult* rWidget;
    QtErrorList* erWidget;
};

