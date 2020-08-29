#include "QtRAI.h"

QtRAI::QtRAI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.graphicsView->setScene(scene);
    ui.graphicsView->rotate(270);
    SceneClear();

    connect(ui.pBCalculation, SIGNAL(clicked()), this, SLOT(calculation));
    connect(ui.spinBox_N, QOverload<int>::of(&QSpinBox::valueChanged),
        [=](int i) {changingNumberMeasurements(i); }
    );
    connect(ui.pushButton_show, SIGNAL(clicked()), this, SLOT(showPoints));
    connect(ui.pBclear, SIGNAL(clicked()), this, SLOT(clear_the_screen));
    connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(showPoints(int)));

    ui.graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);


}


void QtRAI::SceneClear()
{
    scene->clear();
    QPen grid(Qt::green, 1.0);
    grid.setCosmetic(true);
    scene->addLine(-90, 0, 90, 0, grid);
    scene->addLine(0, 90, 0, -90, grid);
    ui.graphicsView->setScene(scene);
}

void QtRAI::InputValidation() 
{
    error = 0;
    error_list.clear();
    points.clear();

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
                error_list.push_back("Cell X" + QString::number(i + 1) + " is NOT a number.");
                error += 1;
            }
        }
        else
        {
            error_list.push_back("Enter the value in cell X" + QString::number(i + 1));
            error += 1;
        }

        QTableWidgetItem* item_y = ui.tableWidget->item(i, 1);
        if (NULL != item_y && item_y->text() != "")
        {
            p.p_y = item_y->text().toDouble(&isOK);
            if (isOK == false)
            {
                error_list.push_back("Cell Y" + QString::number(i + 1) + " is NOT a number.");
                error += 1;
            }
        }
        else
        {
            error_list.push_back("Enter the value in cell Y" + QString::number(i + 1));
            error += 1;
        }

        QTableWidgetItem* item_deg = ui.tableWidget->item(i, 2);
        if (NULL != item_deg && item_deg->text() != "")
        {
            p.deg = item_deg->text().toInt(&isOK);
            if (isOK == false)
            {
                error_list.push_back("Cell DEGREES" + QString::number(i + 1) + " is NOT an integer.");
                error += 1;
            }
        }
        else
        {
            error_list.push_back("Enter the value in cell DEGREES" + QString::number(i + 1));
            error += 1;
        }

        QTableWidgetItem* item_min = ui.tableWidget->item(i, 3);
        if (NULL != item_min && item_min->text() != "")
        {
            p.min = item_min->text().toInt(&isOK);
            if (isOK == false)
            {
                error_list.push_back("Cell MINUTES" + QString::number(i + 1) + " is NOT an integer.");
                error += 1;
            }
        }
        else
        {
            error_list.push_back("Enter the value in cell MINUTES" + QString::number(i + 1));
            error += 1;
        }

        QTableWidgetItem* item_sec = ui.tableWidget->item(i, 4);
        if (NULL != item_sec && item_sec->text() != "")
        {
            p.sec = item_sec->text().toDouble(&isOK);
            if (isOK == false)
            {
                error_list.push_back("Cell SECONDS" + QString::number(i + 1) + " is NOT a number.");
                error += 1;
            }
        }
        else
        {
            error_list.push_back("Enter the value in cell SECONDS" + QString::number(i + 1));
            error += 1;
        }

        if (error == 0)
            points.push_back(p);
    }
    if (error == 1)
        str_err = QString::number(error) + " error";
    else
        str_err = QString::number(error) + " errors";

    ui.statusBar->showMessage(str_err, 3000);
}

void QtRAI::calculation()
{    
    emit showPoints();

    if (error == 0)
    {        
        rWidget = new QtResult(N, points);
        rWidget->setWindowTitle(" RAI");
        rWidget->setWindowIcon(QIcon(":/QtRAI/png/Icon.ico"));
        rWidget->show();
    }
}

void QtRAI::showPoints(int value)
{
    QPen point(Qt::red, 1.6);
    point.setCosmetic(true);

    InputValidation();

    if (error == 0)
    {
        //rad = 2;
        for (size_t i = 0; i < N; i++)
        {
            scene->addEllipse(points[i].p_x - rad, points[i].p_y - rad, 1, 1);
        }
        ui.graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
        SceneClear();
        rad = value;
        for (size_t i = 0; i < N; i++)
        {
            scene->addEllipse(points[i].p_x - rad, points[i].p_y - rad, rad * 2.0, rad * 2.0, point, QBrush(Qt::NoBrush));
        }
        ui.graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
    else
    {
        erWidget = new QtErrorList(error_list);
        erWidget->setWindowTitle(" RAI");
        erWidget->setWindowIcon(QIcon(":/QtRAI/png/Icon.ico"));
        erWidget->show();
    }

    


    
}

void QtRAI::changingNumberMeasurements(int& n)
{
    n = ui.spinBox_N->value();
    ui.tableWidget->setRowCount(n);
    ui.statusBar->showMessage("The number of dimensions is " + QString::number(n), 3000);
    N = n;
}

void QtRAI::clear_the_screen()
{
    SceneClear();
    ui.graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void QtRAI::wheelEvent(QWheelEvent* event)
{    
    if (!event->angleDelta().y() == 0)
        emit mouseWheelZoom(event->angleDelta().y());
    else
        emit mouseWheelZoom(0);
}

void QtRAI::mouseWheelZoom(int step)
{
    double scale_factor = 1.1;
    if (step > 0)
    {
        ui.graphicsView->scale(scale_factor, scale_factor);
    }
    else if (step < 0)
    {
        ui.graphicsView->scale(1 / scale_factor, 1 / scale_factor);
    }

    repaint();

}

