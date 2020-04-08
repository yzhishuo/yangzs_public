#include "file_monitoring_thread.h"
#include<QDir>
#include<QDebug>


#pragma execution_character_set("utf-8")


extern QStringList addfileList;
extern QStringList deletefileList;
extern QStringList moniforfileList;
extern QStringList oldnamefileList;
extern QMutex m_mutex_add;
extern QMutex m_mutex_dele;
extern QMutex m_mutex_monifor;
extern QMutex m_mutex_oldname;

File_Monitoring_Thread::File_Monitoring_Thread(QObject *parent)
	: QThread(parent)
{
	//m_ptrThread = new QThread;
	//this->moveToThread(m_ptrThread);
	//m_ptrThread->start();
	addfileList.clear();
	deletefileList.clear();
	moniforfileList.clear();
	//oldnamefileList.clear();
	//FileType = "";
	file_dir = "";
	FileListType.clear();

}

File_Monitoring_Thread::~File_Monitoring_Thread()
{
	//m_ptrThread->terminate();
	//m_ptrThread->wait();
	//m_ptrThread->deleteLater();
	//m_ptrThread = nullptr;
}
void File_Monitoring_Thread::run()
{
	while (file_dir.isEmpty())
	{
		msleep(500);
		qDebug() << "file_dir 为空=" << file_dir;
	}
	qDebug() << "file_dir=" << file_dir;
	wchar_t s;
	file_dir.toWCharArray(&s);
	HANDLE hRootHandle = CreateFile(
		&s,//监控路径
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);
	if (hRootHandle == INVALID_HANDLE_VALUE)
	{
		qDebug() << "监控线程创建失败!";
		return ;
	}
	qDebug() << "监控线程创建成功!";
	wchar_t notify[1024];
	ZeroMemory(notify, 1024);
	DWORD dwBytes;
	CHAR file_name[1024];
	CHAR file_name2[1024];

	int count = 0;
	FILE_NOTIFY_INFORMATION *pNotify = (FILE_NOTIFY_INFORMATION *)notify;
	while (1)
	{
		if (ReadDirectoryChangesW(hRootHandle, notify, sizeof(notify), TRUE,
			FILE_NOTIFY_CHANGE_CREATION |
			FILE_NOTIFY_CHANGE_FILE_NAME |
			FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_LAST_WRITE,
			&dwBytes, NULL, NULL))
		{
			pNotify->FileName[pNotify->FileNameLength / 2] = '\0';
			if (pNotify->FileName)
			{
				memset(file_name, 0, strlen(file_name));
				WideCharToMultiByte(CP_UTF8, 0, pNotify->FileName, pNotify->FileNameLength / 2, file_name, 99, NULL, NULL);
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
				for (int i = 0; i < FileListType.size(); i++)
				{
					if (QString("%1").arg(file_name).endsWith(FileListType.at(i)))
					{
						m_mutex_add.lock();
						addfileList << QString("%1").arg(file_name);
						m_mutex_add.unlock();
					}
				}
				break;
			case FILE_ACTION_MODIFIED:
				for (int i = 0; i < FileListType.size(); i++)
				{
					if (QString("%1").arg(file_name).endsWith(FileListType.at(i)))
					{
						m_mutex_monifor.lock();
						moniforfileList << QString("%1").arg(file_name);
						m_mutex_monifor.unlock();
					}
				}
				break;
			case FILE_ACTION_REMOVED:
				for (int i = 0; i < FileListType.size(); i++)
				{
					if (QString("%1").arg(file_name).endsWith(FileListType.at(i)))
					{
						m_mutex_dele.lock();
						deletefileList << QString("%1").arg(file_name);
						m_mutex_dele.unlock();
					}
				}
				break;
			case FILE_ACTION_RENAMED_OLD_NAME:
				//if (QString("%1").arg(file_name).endsWith(FileType))
				//{
				//	m_mutex_oldname.lock();
				//	oldnamefileList << QString("%1").arg(file_name) << QString("%1").arg(file_name2);
				//	m_mutex_oldname.unlock();
				//}
				for (int i = 0; i < FileListType.size(); i++)
				{
					if (QString("%1").arg(file_name).endsWith(FileListType.at(i)))
					{
						m_mutex_oldname.lock();
						oldnamefileList << QString("%1").arg(file_name) << QString("%1").arg(file_name2);
						m_mutex_oldname.unlock();
					}
				}

				break;
			default:
				break;
			}
		}
	}
}
//int File_Monitoring_Thread::start_FileMoniforing(QString dir)
//{
//	int rtn = 0;
//	file_dir = dir;
	/*
	wchar_t s;
	dir.toWCharArray(&s);
	HANDLE hRootHandle = CreateFile(
		&s,//监控路径
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);
	if (hRootHandle == INVALID_HANDLE_VALUE)
	{
		//qDebug() << "监控线程创建失败!";
		return -1;
	}
	//qDebug() << "监控线程创建成功!";
	wchar_t notify[1024];
	ZeroMemory(notify, 1024);
	DWORD dwBytes;
	CHAR file_name[1024];
	//CHAR file_name_t[1024];
	CHAR file_name2[1024];

	int count = 0;
	FILE_NOTIFY_INFORMATION *pNotify = (FILE_NOTIFY_INFORMATION *)notify;
	while (1)
	{
		if (ReadDirectoryChangesW(hRootHandle, notify, sizeof(notify), TRUE,
			FILE_NOTIFY_CHANGE_CREATION |
			FILE_NOTIFY_CHANGE_FILE_NAME |
			FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_LAST_WRITE,
			&dwBytes, NULL, NULL))
		{
			pNotify->FileName[pNotify->FileNameLength / 2] = '\0';
			//qDebug() << "文件名打印" << pNotify->FileName;
			//过滤临时文件
			if (pNotify->FileName)
			{
				memset(file_name, 0, strlen(file_name));
				WideCharToMultiByte(CP_UTF8, 0, pNotify->FileName, pNotify->FileNameLength / 2, file_name, 99, NULL, NULL);

				//PFILE_NOTIFY_INFORMATION p = (PFILE_NOTIFY_INFORMATION)((char*)pNotify + pNotify->NextEntryOffset);
				//memset(file_name_t, 0, sizeof(file_name_t));
				//WideCharToMultiByte(CP_UTF8, 0, p->FileName, p->FileNameLength / 2, file_name_t, 99, NULL, NULL);
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

				//qDebug() << "添加文件 file_name=" << file_name ;
				//send_addfile(QString("%1").arg(file_name));
				if (QString("%1").arg(file_name).endsWith(FileType))
				{
					m_mutex_add.lock();
					addfileList << QString("%1").arg(file_name);
					//	qDebug() << "有效的添加文件" << QString("%1").arg(file_name);
					m_mutex_add.unlock();
				}

				break;
			case FILE_ACTION_MODIFIED:
				//	qDebug() << "文件被修改  ----------------------";
				//	qDebug() << "文件被修改" << QString("%1").arg(file_name);
					//send_moniforfile(QString("%1").arg(file_name));
				if (QString("%1").arg(file_name).endsWith(FileType))
				{
					m_mutex_monifor.lock();
					moniforfileList << QString("%1").arg(file_name);
					//	qDebug() << "有效的修改文件" << QString("%1").arg(file_name);
					m_mutex_monifor.unlock();
				}

				break;
			case FILE_ACTION_REMOVED:

				//send_deletefile(QString("%1").arg(file_name));
				if (QString("%1").arg(file_name).endsWith(FileType))
				{
					m_mutex_dele.lock();
					deletefileList << QString("%1").arg(file_name);
					//	qDebug() << "有效的删除文件" << QString("%1").arg(file_name);
					m_mutex_dele.unlock();
				}
				break;
			case FILE_ACTION_RENAMED_OLD_NAME:

				//	qDebug() << "文件被重命名" << (file_name2) << "原名字" << (file_name);			
					//send_oldnamefile(QString("%1").arg(file_name), QString("%1").arg(file_name2));

				if (QString("%1").arg(file_name).endsWith(FileType))
				{
					m_mutex_oldname.lock();
					oldnamefileList << QString("%1").arg(file_name) << QString("%1").arg(file_name2);
					//	qDebug() << "有效的重命名文件" << QString("%1").arg(file_name);
					m_mutex_oldname.unlock();
				}

				break;
			default:
				//	qDebug() << "未知";
				break;
			}
		}
	}
	*/
//	return rtn;
//}