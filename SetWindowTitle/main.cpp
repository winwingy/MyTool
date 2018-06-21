#include "setwindowtitle.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SetWindowTitle w;
	w.show();
	return a.exec();
}
