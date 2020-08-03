#include "QtRAI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtRAI w;
    w.setWindowTitle(" RAI");
    w.setWindowIcon(QIcon(":/QtRAI/png/Icon.ico"));
    w.show();
    return a.exec();
}
