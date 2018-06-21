#ifndef SETWINDOWTITLE_H
#define SETWINDOWTITLE_H

#include <QtWidgets/QMainWindow>
#include "ui_setwindowtitle.h"
class QTimer;

class SetWindowTitle : public QMainWindow
{
	Q_OBJECT

public:
	SetWindowTitle(QWidget *parent = 0);
	~SetWindowTitle();
	void _connect();

private Q_SLOTS:

	void OnFindButtonClick(bool checked);
	void OnRunButtonClicked(bool checked);
	void OnHoldButtonClick(bool checked);	
	HWND GetSelectHwnd();
private:
	Ui::SetWindowTitleClass ui;
	HWND m_selectHwnd;
	QTimer* m_timerSetText;
};

#endif // SETWINDOWTITLE_H
