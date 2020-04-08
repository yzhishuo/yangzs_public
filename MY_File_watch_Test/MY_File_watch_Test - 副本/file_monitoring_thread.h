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
	void addFilePath(QString dir);//���·��
	

public slots:
	int  start_FileMoniforing(QString dir);//�������

signals:
	void send_addfile(QString dirfile);//����ļ�
	void send_deletefile(QString dirfile);//ɾ���ļ�
	void send_moniforfile(QString dirfile);//�ļ��޸�
	void send_oldnamefile(QString olddirfile, QString newdirfile);//�ļ�������



private:
	QString File_monif;
	QThread *m_ptrThread;
	bool file_first;//����ص��ļ����Ƿ��һ���޸�
	
};

#endif // FILE_MONITORING_THREAD_H
