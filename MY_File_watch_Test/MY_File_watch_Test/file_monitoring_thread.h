#ifndef FILE_MONITORING_THREAD_H
#define FILE_MONITORING_THREAD_H

#include <QThread>
#include <QThread>
#include <QSharedPointer>
#include<Windows.h>
#include<TlHelp32.h>
#include<QStringList>

#include<QMutex>
#include<QMutexLocker>



class File_Monitoring_Thread : public QThread
{
	Q_OBJECT

public:
	File_Monitoring_Thread(QObject *parent=NULL);
	~File_Monitoring_Thread();
	QStringList FileListType;//监控文件的类型列表
	QString file_dir;//开启文件监控的路径

protected:
	void run();


	


	
};

#endif // FILE_MONITORING_THREAD_H
