#include "file_monitoring_thread.h"
#include<QDir>
#include<QDebug>



#pragma execution_character_set("utf-8")
File_Monitoring_Thread::File_Monitoring_Thread(QObject *parent)
	: QThread(parent)
{
	m_ptrThread = new QThread;
	this->moveToThread(m_ptrThread);
	m_ptrThread->start();
	init();
	qDebug() << "完成初始化";
}

File_Monitoring_Thread::~File_Monitoring_Thread()
{
	m_ptrThread->terminate();
	m_ptrThread->wait();
	m_ptrThread->deleteLater();
	m_ptrThread = nullptr;
}
void File_Monitoring_Thread::init(void)
{
	File_monif = "";
	file_first = false;
}
void File_Monitoring_Thread::addFilePath(QString dir)
{
	File_monif = dir;
	if (dir.isEmpty())
	{
		//路径为空
		qDebug() << "路径为空!";
		return ;
	}
	//判断路径是否为空格
	//判断传入路径是否存在
	QDir mdir(dir);
	if (!mdir.exists())
	{
		//文件夹路径不存在
		qDebug() << "文件夹路径不存在!";
		return ;
	}
	
	//start_FileMoniforing(dir);

}
int File_Monitoring_Thread::start_FileMoniforing(QString dir)
{
	int rtn = 0;
	//QByteArray bay= dir.toLocal8Bit();
	//TCHAR *tdir = bay.constData();
	//qDebug() << "开启监测!";
//	char *s = "D:\\1";
//	const char ss[256] = "D:\\1";
	//TCHAR *tdir = TEXT("D:/1");
	//WCHAR *tdirs= TEXT("D:/周记");
	wchar_t s;
	//QString pat = "D:/周记";
	//pat.toWCharArray(&s);
	dir.toWCharArray(&s);
	HANDLE hRootHandle = CreateFile(
		//szRootPath,		//监控路径
		//tdirs,
		&s,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);
	if (hRootHandle == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox(TEXT("监控线程创建失败!"));
		qDebug() << "监控线程创建失败!";
		return -1;
	}
	qDebug() << "监控线程创建成功!";
	wchar_t notify[1024];
	ZeroMemory(notify, 1024);
	DWORD dwBytes;
	//char file_name[1024];
	//char file_name2[1024];

	CHAR file_name[1024];
	CHAR file_name_t[1024];
	CHAR file_name2[1024];

	int count = 0;
	//callbackinfo info;
	FILE_NOTIFY_INFORMATION *pNotify = (FILE_NOTIFY_INFORMATION *)notify;
	while (1)
	{
		//memset(file_name, 0, strlen(file_name));
		//memset(file_name_t, 0, strlen(file_name_t));
	//	memset(file_name2, 0, strlen(file_name2));
		if (ReadDirectoryChangesW(hRootHandle, notify, sizeof(notify), TRUE,
			FILE_NOTIFY_CHANGE_CREATION |
			FILE_NOTIFY_CHANGE_FILE_NAME |
			FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_LAST_WRITE,
			&dwBytes, NULL, NULL))
		{
			pNotify->FileName[pNotify->FileNameLength / 2] = '\0';
			qDebug() << "文件名打印" << pNotify->FileName;
			//过滤临时文件
			if (pNotify->FileName)
			{
				memset(file_name, 0, strlen(file_name));
				WideCharToMultiByte(CP_UTF8, 0, pNotify->FileName, pNotify->FileNameLength / 2, file_name, 99, NULL, NULL);

				PFILE_NOTIFY_INFORMATION p = (PFILE_NOTIFY_INFORMATION)((char*)pNotify + pNotify->NextEntryOffset);
				memset(file_name_t, 0, sizeof(file_name_t));
				WideCharToMultiByte(CP_UTF8, 0, p->FileName, p->FileNameLength / 2, file_name_t, 99, NULL, NULL);
			}
			if (pNotify->NextEntryOffset != 0 && (pNotify->FileNameLength > 0 && pNotify->FileNameLength < MAX_PATH))
			{
				PFILE_NOTIFY_INFORMATION p = (PFILE_NOTIFY_INFORMATION)((char*)pNotify + pNotify->NextEntryOffset);
				memset(file_name2, 0, sizeof(file_name2));
				WideCharToMultiByte(CP_UTF8, 0, p->FileName, p->FileNameLength / 2, file_name2, 99, NULL, NULL);
			}
			switch (pNotify->Action)
			{
			case FILE_ACTION_ADDED:
				count++;
				//qDebug() << "添加文件 file_name=" << file_name << "file_name_t=" << file_name_t << "file_name2=" << file_name2;
				//qDebug() << "添加文件" << QString("%1").arg(file_name)<< "file_name_t=" << QString("%1").arg(file_name_t) << "file_name2=" << QString("%1").arg(file_name2);;
				send_addfile(QString("%1").arg(file_name));
				file_first = true;
				break;
			case FILE_ACTION_MODIFIED:
				qDebug() << "文件被修改  ----------------------";
				if (true == file_first)
				{
					file_first = false;
				}
				else
				{
					qDebug() << "文件被修改" << QString("%1").arg(file_name);
					send_moniforfile(QString("%1").arg(file_name));
				}
				
				
				break;
			case FILE_ACTION_REMOVED:
				count++;
				//qDebug() << "文件被删除" << file_name;
				//qDebug() << "文件被删除" << QString("%1").arg(file_name);
				file_first = true;
				send_deletefile(QString("%1").arg(file_name));
				break;
			case FILE_ACTION_RENAMED_OLD_NAME:
				//qDebug() << "文件被重命名" << file_name<< file_name2;
				//qDebug() << "文件被重命名" << QString("%1").arg(file_name2) << "原名字" << file_name;
				//qDebug() << "文件被重命名" << (file_name2) << "原名字" << (file_name) << "原名字2" << file_name_t;
				file_first = true;
				send_oldnamefile(QString("%1").arg(file_name), QString("%1").arg(file_name2));
				break;
			default:
				qDebug() << "未知";

			}
		}
	}





	return rtn;
}