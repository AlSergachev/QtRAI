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
        str_err = QString::number(error) + " errors";

    /*
    Point p1, p2, p3, p4;							//	Вариант 16  OK
    p1.p_x = 16600.897;								//	
    p1.p_y = 10955.701;								//  В цикл, 	
    p1.deg_angle_meas = 0;							//  который	
    points.push_back(p1);							//  будет		
    p2.p_x = 14570.805;								//  извлекать	
    p2.p_y = 15515.515;								//  эти данные	
    p2.deg_angle_meas = 57.59444444;				//  из	
    points.push_back(p2);							//  таблицы
    p3.p_x = 10561.699;								//  формы
    p3.p_y = 9277.652;								//
    p3.deg_angle_meas = 157.1369444;				//
    points.push_back(p3);							//
    p4.p_x = 12642.341;								//
    p4.p_y = 7136.127;								//
    p4.deg_angle_meas = 210.0105556;				//
    points.push_back(p4);							
    */
/*
    Point p1, p2, p3, p4;							//	Вариант 1
    p1.p_x = 22365.348;								//	
    p1.p_y = 13224.791;								//  В цикл, 	
    p1.deg_angle_meas = 0;							//  который	
    points.push_back(p1);							//  будет		
    p2.p_x = 21954.951;								//  извлекать	
    p2.p_y = 11644.834;								//  эти данные	
    p2.deg_angle_meas = 8.9958333333;				//  из	
    points.push_back(p2);							//  таблицы
    p3.p_x = 16600.897;								//  формы
    p3.p_y = 10955.701;								//
    p3.deg_angle_meas = 61.99333333;				//  X = 22770.786
    points.push_back(p3);							//  Y = 8298.251
    p4.p_x = 20145.267;								//  mP = 17.1
    p4.p_y = 7870.345;								//  mX = 13.2
    p4.deg_angle_meas = 94.55194444;				//  mY = 10.8
    points.push_back(p4);							//  ma = 0.356
   */
    /*
    Point p1, p2, p3, p4;							//	Вариант 2  OK
    p1.p_x = 22365.348;								//
    p1.p_y = 13224.791;								//  В цикл,
    p1.deg_angle_meas = 0;							//  который
    points.push_back(p1);							//  будет
    p2.p_x = 21954.951;								//  извлекать
    p2.p_y = 11644.834;								//  эти данные
    p2.deg_angle_meas = 8.630000;				    //  из
    points.push_back(p2);							//  таблицы
    p3.p_x = 16600.897;								//  формы
    p3.p_y = 10955.701;								//
    p3.deg_angle_meas = 72.555833;				    //  X = 22309.241
    points.push_back(p3);							//  Y = 9076.803
    p4.p_x = 20145.267;								//  mP = 27.87613135
    p4.p_y = 7870.345;								//  mX = 17.3328191
    p4.deg_angle_meas = 119.915556;				    //  mY = 21.83236317
    points.push_back(p4);							//  ma = 0.741639905
    */
/*
    Point p1, p2, p3, p4;							//	Вариант 10
    p1.p_x = 20650.281;								//
    p1.p_y = 18304.881;								//  В цикл,
    p1.deg_angle_meas = 0;							//  который
    points.push_back(p1);							//  будет
    p2.p_x = 17455.208 ;								//  извлекать
    p2.p_y = 18939.510;								//  эти данные
    p2.deg_angle_meas = 62.92111111;				//  из
    points.push_back(p2);							//  таблицы
    p3.p_x = 17477.071;								//  формы
    p3.p_y = 16193.792;								//
    p3.deg_angle_meas = 130.6047222;				//  X = 18227.908
    points.push_back(p3);							//  Y = 16100.386
    p4.p_x = 22365.348;								//  mP = 7.025805271
    p4.p_y = 13224.791;								//  mX = 6.863024809
    p4.deg_angle_meas = 282.8961111;				//  mY = 1.503605725
    points.push_back(p4);							//  ma = 0.48527717
    */
    /*
    Point p1, p2, p3, p4;							//	Вариант 17
    p1.p_x = 16600.897;								//
    p1.p_y = 10955.701;								//  В цикл,
    p1.deg_angle_meas = 0;							//  который
    points.push_back(p1);							//  будет
    p2.p_x = 14570.805;								//  извлекать
    p2.p_y = 15515.515;								//  эти данные
    p2.deg_angle_meas = 76.99000000;				//  из
    points.push_back(p2);							//  таблицы
    p3.p_x = 11948.562;								//  формы
    p3.p_y = 10270.656;								//
    p3.deg_angle_meas = 187.1491666;				//  X = 13920,794
    points.push_back(p3);							//  Y = 10706,497
    p4.p_x = 12642.341;								//  mP = 1.1
    p4.p_y = 7136.127;								//  mX = 1.0
    p4.deg_angle_meas = 244.98666666;				//  mY = 0.36
    points.push_back(p4);							//  ma = 0.0655
    

    Point p1, p2, p3, p4, p5;					    //	Вариант 18
    p1.p_x = 14570.805;								//
    p1.p_y = 15515.515;								//  В цикл,
    //p1.deg_angle_meas = 0;							//  который
    p1.deg = 0;
    p1.min = 0;
    p1.sec = 0;
    points.push_back(p1);							//  будет
    p2.p_x = 8175.364;								//  извлекать
    p2.p_y = 12800.380;								//  эти данные
    //p2.deg_angle_meas = 74.99666667;				//  из
    p2.deg = 74;
    p2.min = 59;
    p2.sec = 48;
    points.push_back(p2);							//  таблицы
    p3.p_x = 11948.562;								//  формы
    p3.p_y = 10270.656;								//
    //p3.deg_angle_meas = 88.17555556;				//  X = 13009.398
    p3.deg = 88;
    p3.min = 10;
    p3.sec = 32;
    points.push_back(p3);							//  Y = 9936.970
    p4.p_x = 10561.699;								//  mP = 8.11
    p4.p_y = 9277.652;								//  mX = 7.01
    //p4.deg_angle_meas = 120.7125000;				//  mY = 4.08
    p4.deg = 120;
    p4.min = 42;
    p4.sec = 45;
    points.push_back(p4);							//  ma = 0.85455
    p5.p_x = 12642.341;                             //
    p5.p_y = 7136.127;                              //
    //p5.deg_angle_meas = 188.1702778;                //
    p5.deg = 188;
    p5.min = 10;
    p5.sec = 13;
    points.push_back(p5);                           //
*/


    ui.statusBar->showMessage(str_err, 3000);
    if (error == 0)
    {
        rWidget = new QtResult(N, points);
        rWidget->show();
    }
}

void QtRAI::changingNumberMeasurements(int& n)
{
    n = ui.spinBox_N->value();
    ui.tableWidget->setRowCount(n);
    ui.statusBar->showMessage("The number of dimensions is " + QString::number(n), 3000);
    N = n;
}


