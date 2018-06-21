#include "dailyrem.h"
#include <QFileDialog>
#include <QRect>
#include <qDebug>

DailyRem::DailyRem(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connection();
}

QRect getAdjustRectByWidth(const QRect& rect, int width, int maxWidth)
{
	QRect rectRet(rect);
	int left = rect.left() - width/2;
	if (left < 0)
		left = 0;

	int right = rect.right() + width/2;
	if (right > maxWidth)
		right = maxWidth;

	rectRet.setLeft(left);
	rectRet.setRight(right);
	return rectRet;
}

void DailyRem::connection()
{
	connect(ui.action_open, &QAction::triggered, [&]()
	{
// 		const QString& strPath = QFileDialog::getOpenFileName(
// 			this,QObject::tr("Select File"),
// 			QLatin1String("//"),QString("DLR(*.dlr)"));
// 		if( strPath.isEmpty() )
// 			return;
		//QTextEdit *textEdit
		QRect rect = ui.textEdit->cursorRect();
		QRect rectAdjust = getAdjustRectByWidth(rect, 100, ui.textEdit->width());
		qDebug() << rectAdjust;

	});
}

DailyRem::~DailyRem()
{

}
