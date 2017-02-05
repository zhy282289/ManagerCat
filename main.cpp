#include "stdafx.h"
#include "managercat.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ManagerCat w;
	w.show();
	return a.exec();
}
