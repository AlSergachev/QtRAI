#include "QtErrorList.h"

QtErrorList::QtErrorList(QVector <QString>& error_list, QWidget *parent)
	: QWidget(parent)
{
	QString s_error_list = (QString::number(1) + "  " + error_list[0] + "\n");
	ui.setupUi(this);
	for (size_t i = 1; i < error_list.size(); i++)
	{
		s_error_list += (QString::number(i+1) + "  " + error_list[i] + "\n");
	}
	
	ui.errors->setText(s_error_list);

}

QtErrorList::~QtErrorList()
{
}
