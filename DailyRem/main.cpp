#include "dailyrem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DailyRem w;
	w.show();
	return a.exec();
}
