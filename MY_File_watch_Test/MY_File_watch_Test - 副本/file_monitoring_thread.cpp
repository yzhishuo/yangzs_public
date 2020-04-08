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
	qDebug() << "��ɳ�ʼ��";
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
		//·��Ϊ��
		qDebug() << "·��Ϊ��!";
		return ;
	}
	//�ж�·���Ƿ�Ϊ�ո�
	//�жϴ���·���Ƿ����
	QDir mdir(dir);
	if (!mdir.exists())
	{
		//�ļ���·��������
		qDebug() << "�ļ���·��������!";
		return ;
	}
	
	//start_FileMoniforing(dir);

}
int File_Monitoring_Thread::start_FileMoniforing(QString dir)
{
	int rtn = 0;
	//QByteArray bay= dir.toLocal8Bit();
	//TCHAR *tdir = bay.constData();
	//qDebug() << "�������!";
//	char *s = "D:\\1";
//	const char ss[256] = "D:\\1";
	//TCHAR *tdir = TEXT("D:/1");
	//WCHAR *tdirs= TEXT("D:/�ܼ�");
	wchar_t s;
	//QString pat = "D:/�ܼ�";
	//pat.toWCharArray(&s);
	dir.toWCharArray(&s);
	HANDLE hRootHandle = CreateFile(
		//szRootPath,		//���·��
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
		//AfxMessageBox(TEXT("����̴߳���ʧ��!"));
		qDebug() << "����̴߳���ʧ��!";
		return -1;
	}
	qDebug() << "����̴߳����ɹ�!";
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
			qDebug() << "�ļ�����ӡ" << pNotify->FileName;
			//������ʱ�ļ�
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
				//qDebug() << "����ļ� file_name=" << file_name << "file_name_t=" << file_name_t << "file_name2=" << file_name2;
				//qDebug() << "����ļ�" << QString("%1").arg(file_name)<< "file_name_t=" << QString("%1").arg(file_name_t) << "file_name2=" << QString("%1").arg(file_name2);;
				send_addfile(QString("%1").arg(file_name));
				file_first = true;
				break;
			case FILE_ACTION_MODIFIED:
				qDebug() << "�ļ����޸�  ----------------------";
				if (true == file_first)
				{
					file_first = false;
				}
				else
				{
					qDebug() << "�ļ����޸�" << QString("%1").arg(file_name);
					send_moniforfile(QString("%1").arg(file_name));
				}
				
				
				break;
			case FILE_ACTION_REMOVED:
				count++;
				//qDebug() << "�ļ���ɾ��" << file_name;
				//qDebug() << "�ļ���ɾ��" << QString("%1").arg(file_name);
				file_first = true;
				send_deletefile(QString("%1").arg(file_name));
				break;
			case FILE_ACTION_RENAMED_OLD_NAME:
				//qDebug() << "�ļ���������" << file_name<< file_name2;
				//qDebug() << "�ļ���������" << QString("%1").arg(file_name2) << "ԭ����" << file_name;
				//qDebug() << "�ļ���������" << (file_name2) << "ԭ����" << (file_name) << "ԭ����2" << file_name_t;
				file_first = true;
				send_oldnamefile(QString("%1").arg(file_name), QString("%1").arg(file_name2));
				break;
			default:
				qDebug() << "δ֪";

			}
		}
	}





	return rtn;
}