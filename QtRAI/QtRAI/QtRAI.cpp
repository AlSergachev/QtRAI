#include "QtRAI.h"

QtRAI::QtRAI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.pBCalculation, SIGNAL(clicked()), this, SLOT(calculation));
    connect(ui.spinBox_N, QOverload<int>::of(&QSpinBox::valueChanged),
        [=](int i) {changingNumberMeasurements(i); }
    );


}

void QtRAI::calculation()
{

    int error(0);
    /*
    for (size_t i = 0; i < N; i++)
    {
        Point p;
        bool isOK;

        QTableWidgetItem* item_x = ui.tableWidget->item(i, 0);
        if (NULL != item_x && item_x->text() != "")
        {
            p.p_x = item_x->text().toDouble(&isOK);
            if (isOK == false)
            {
                QMessageBox::warning(this, "Error", "Cell X" + QString::number(i + 1) + " is NOT a number. \nEnter a number!");
                error += 1;
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "Enter the value in cell X" + QString::number(i + 1));
            error += 1;
        }

        QTableWidgetItem* item_y = ui.tableWidget->item(i, 1);
        if (NULL != item_y && item_y->text() != "")
        {
            p.p_y = item_y->text().toDouble(&isOK);
            if (isOK == false)
            {
                QMessageBox::warning(this, "Error", "Cell Y" + QString::number(i + 1) + " is NOT a number. \nEnter a number!");
                error += 1;
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "Enter the value in cell Y" + QString::number(i + 1));
            error += 1;
        }

        QTableWidgetItem* item_deg = ui.tableWidget->item(i, 2);
        if (NULL != item_deg && item_deg->text() != "")
        {
            p.deg = item_deg->text().toInt(&isOK);
            if (isOK == false)
            {
                QMessageBox::warning(this, "Error", "Cell DEGREES" + QString::number(i + 1) + " is NOT an integer. \nEnter an integer!");
                error += 1;
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "Enter the value in cell DEGREES" + QString::number(i + 1));
            error += 1;
        }

        QTableWidgetItem* item_min = ui.tableWidget->item(i, 3);
        if (NULL != item_min && item_min->text() != "")
        {
            p.min = item_min->text().toInt(&isOK);
            if (isOK == false)
            {
                QMessageBox::warning(this, "Error", "Cell MINUTES" + QString::number(i + 1) + " is NOT an integer. \nEnter an integer!");
                error += 1;
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "Enter the value in cell MINUTES" + QString::number(i + 1));
            error += 1;
        }

        QTableWidgetItem* item_sec = ui.tableWidget->item(i, 4);
        if (NULL != item_sec && item_sec->text() != "")
        {
            p.sec = item_sec->text().toDouble(&isOK);
            if (isOK == false)
            {
                QMessageBox::warning(this, "Error", "Cell SECONDS" + QString::number(i + 1) + " is NOT a number. \nEnter a number!");
                error += 1;
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "Enter the value in cell SECONDS" + QString::number(i + 1));
            error += 1;
        }

        if (error == 0)
            points.push_back(p);
    }
    if (error == 1)
        str_err = QString::number(error) + " error";
    else
        str_err = QString::number(error) + " errors";*/

    Point p1, p2, p3, p4;							//	В цикл, 
    p1.p_x = 16600.897;								//	который
    p1.p_y = 10955.701;								//	будет
    p1.deg_angle_meas = 0;							//	извлекать
    points.push_back(p1);							//	эти данные	
    p2.p_x = 14570.805;								//	из
    p2.p_y = 15515.515;								//	таблицы
    p2.deg_angle_meas = 57.59444444;				//	формы
    points.push_back(p2);							//
    p3.p_x = 10561.699;								//
    p3.p_y = 9277.652;								//
    p3.deg_angle_meas = 157.1369444;				//
    points.push_back(p3);							//
    p4.p_x = 12642.341;								//
    p4.p_y = 7136.127;								//
    p4.deg_angle_meas = 210.0105556;				//
    points.push_back(p4);							//

    ui.statusBar->showMessage(str_err, 3000);
    if (error == 0)
    {
        rWidget = new QtResult(N, points);
        rWidget->show();
    }
}

void QtRAI::changingNumberMeasurements(int& N)
{
    N = ui.spinBox_N->value();
    ui.tableWidget->setRowCount(N);
    ui.statusBar->showMessage("The number of dimensions is " + QString::number(N), 3000);
}


