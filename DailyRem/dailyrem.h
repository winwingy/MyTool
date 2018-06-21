#ifndef DAILYREM_H
#define DAILYREM_H

#include <QtWidgets/QMainWindow>
#include "ui_dailyrem.h"

class DailyRem : public QMainWindow
{
	Q_OBJECT

public:
	DailyRem(QWidget *parent = 0);
	~DailyRem();

private:
	void connection();
	Ui::DailyRemClass ui;
};

#endif // DAILYREM_H
