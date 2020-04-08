#ifndef FILE_MONITORING_THREAD_H
#define FILE_MONITORING_THREAD_H

#include <QThread>
#include <QThread>
#include <QSharedPointer>
#include<Windows.h>
#include<TlHelp32.h>
class File_Monitoring_Thread : public QThread
{
	Q_OBJECT

public:
	File_Monitoring_Thread(QObject *parent=NULL);
	~File_Monitoring_Thread();
	void init(void);
	void addFilePath(QString dir);//监控路径
	

public slots:
	int  start_FileMoniforing(QString dir);//开启监控

signals:
	void send_addfile(QString dirfile);//添加文件
	void send_deletefile(QString dirfile);//删除文件
	void send_moniforfile(QString dirfile);//文件修改
	void send_oldnamefile(QString olddirfile, QString newdirfile);//文件重命名



private:
	QString File_monif;
	QThread *m_ptrThread;
	bool file_first;//被监控的文件夹是否第一次修改
	
};

#endif // FILE_MONITORING_THREAD_H
