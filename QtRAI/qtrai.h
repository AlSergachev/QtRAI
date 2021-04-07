#ifndef QTRAI_H
#define QTRAI_H

#include <QMainWindow>
#include "qterrorlist.h"
#include "qtresult.h"
#include <QVector>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <vector>
#include "ui_qtrai.h"
#include "qtresult.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class QtRAI; }
QT_END_NAMESPACE

class QtRAI : public QMainWindow
{
    Q_OBJECT

public:
    QtRAI(QWidget *parent = nullptr);
    ~QtRAI();
    vector <Point> points;

private:
    Ui::QtRAI *ui;
    QGraphicsScene* scene = new QGraphicsScene;
    void SceneClear();
    void InputValidation();
    int N = 3;
    int n, rad;
    int error = 0;
    QString str_err;
    QVector <QString> error_list;


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

#endif // QTRAI_H
