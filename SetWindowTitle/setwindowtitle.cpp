#include "setwindowtitle.h"
#include <QStringListModel>
#include <windows.h>
#include <Psapi.h>
#include <vector>
#include <string>
#include <assert.h>
#include <qstandarditemmodel.h>
#include "qitemselectionmodel.h"
#include <QMessageBox>
#include <QTimer>
#pragma comment(lib, "psapi.lib")

SetWindowTitle::SetWindowTitle(QWidget *parent)
	: QMainWindow(parent)
	, m_selectHwnd(nullptr)
{
	ui.setupUi(this);
	_connect();
}

SetWindowTitle::~SetWindowTitle()
{

}

void SetWindowTitle::_connect()
{
	QObject::connect(ui.FindButton, SIGNAL(clicked(bool)), 
		 this, SLOT(OnFindButtonClick(bool)));

	QObject::connect(ui.HoldButton, SIGNAL(clicked(bool)), 
		this, SLOT(OnHoldButtonClick(bool)));
}

bool GetExePathFromHWND(HWND hwnd, std::wstring* exePath) 
{ 
	bool ret = false;
	do 
	{			
		int ErrorCode = 0; 
		DWORD idProcess = 0; 
		if (!hwnd || !exePath)
			break;

		GetWindowThreadProcessId(hwnd, &idProcess); 
		if (idProcess == 0)
			break;
		
		HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 
			FALSE, idProcess ); 
		if( NULL != hProcess ) 
		{
			HMODULE hMod = NULL; 
			DWORD cbNeeded = 0; 
			if( EnumProcessModules( hProcess, &hMod, sizeof( hMod ), &cbNeeded ) ) 
			{ 
				TCHAR szPath[MAX_PATH] = {0}; 
				DWORD dw = GetModuleFileNameEx( hProcess, hMod, szPath, MAX_PATH ); 
				if(dw > 0) 
				{ 
					*exePath = szPath;
					ret = true;					
				} 
			} 
			CloseHandle( hProcess ); 
		} 
	} while (0);

	return ret;
}

struct EnumWindowsData
{
	std::wstring findWhat;
	std::vector<HWND>* hWndList;
	std::vector<std::wstring>* titleList;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam)
{
	wchar_t szPath[1024] = {0};
	GetWindowText(hwnd, szPath, sizeof(szPath)/sizeof(szPath[0]));

	EnumWindowsData* enumDatas =
		reinterpret_cast<EnumWindowsData* >(lparam);
	if (enumDatas && enumDatas->hWndList)
	{
		if (std::wstring(szPath).find(enumDatas->findWhat) != std::wstring::npos)
		{
			enumDatas->hWndList->push_back(hwnd);
			enumDatas->titleList->push_back(szPath);
		}
	}
	return TRUE;
}

bool FindTitleExePathList(const std::wstring& title,
	std::vector<HWND>* hWndList,
	std::vector<std::wstring>* titlList)
{
	bool ret = false;
	do 
	{
		if (title.empty() || !titlList)
			break;

		EnumWindowsData enumData = {title, hWndList, titlList};
		EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&enumData));
		if (!titlList->empty())
		{
			ret = true;
		}

// 		for (auto iter = hWndList.begin(); iter != hWndList.end(); ++iter)
// 		{
// 			std::wstring exePath;
// 			if (GetExePathFromHWND(*iter, &exePath))
// 			{
// 				titlList->push_back(exePath);
// 				ret = true;
// 			}
// 		}
	} while (0);
	return ret;
}

enum enViewModalDataRole
{
	enViewModalDataRole_Hwnd = Qt::UserRole + 10,
};
Q_DECLARE_METATYPE(HWND)
void SetWindowTitle::OnFindButtonClick(bool checked)
{
	QString name = ui.OriginEdit->text();
	std::vector<HWND> hWndList;
	std::vector<std::wstring> titleList;
	if (FindTitleExePathList(name.toStdWString(), &hWndList, &titleList))
	{
		if (hWndList.size() != titleList.size())
		{
			assert("hWndList.size() != titleList" && 0);
			return;
		}
		QStandardItemModel* viewModal = new QStandardItemModel(ui.OriginlistView);
		ui.OriginlistView->setModel(viewModal);
		for (int i = 0; i < titleList.size(); ++i)
		{
			QStandardItem* item = new QStandardItem();
			item->setData(QVariant::fromValue(hWndList[i]), enViewModalDataRole_Hwnd);
			item->setText(QString::fromStdWString(titleList[i]));
			viewModal->appendRow(item);
		}		
	}
}

HWND SetWindowTitle::GetSelectHwnd()
{
	QItemSelectionModel* selectList = ui.OriginlistView->selectionModel();
	if (!selectList)
	{
		return nullptr;
	}	
	QModelIndexList selectIndexs =  selectList->selectedIndexes();
	if (selectIndexs.isEmpty())
	{
		return nullptr;
	}

	QAbstractItemModel* listModel = ui.OriginlistView->model();
	for (auto iter = selectIndexs.begin(); iter != selectIndexs.end(); ++iter)
	{
		QVariant itemData = iter->data(enViewModalDataRole_Hwnd);
		if (itemData.isValid())
		{
			HWND hWndWnd =  itemData.value<HWND>();
			return hWndWnd;
		}
	}
	return nullptr;
}

void SetWindowTitle::OnRunButtonClicked(bool checked)
{	
	BOOL ok = FALSE;
	HWND selectHwnd = GetSelectHwnd();
	if (selectHwnd)
	{
		QString targetText = ui.TargetEdit->text();
		ok = SetWindowText(selectHwnd, targetText.toStdWString().c_str());
		m_selectHwnd = selectHwnd;
	}
	std::wstring show = ok? L"OK" : L"Fail";
	QMessageBox::information(this, QString::fromStdWString(show), 
		QString::fromStdWString(show), QMessageBox::Yes);
}

void SetWindowTitle::OnHoldButtonClick(bool checked)
{
	m_timerSetText = new QTimer(this);
	m_timerSetText->setInterval(2000);
	m_timerSetText->start();
	connect(m_timerSetText, &QTimer::timeout, [&]()
	{
		BOOL ok = SetWindowText(m_selectHwnd,
			ui.TargetEdit->text().toStdWString().c_str());
	});
}
