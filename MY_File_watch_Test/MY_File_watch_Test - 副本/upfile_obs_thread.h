/**
***只做上传文件到数据库，无其他操作
***
****/



#ifndef UPFILE_OBS_THREAD_H
#define UPFILE_OBS_THREAD_H

#include <QThread>
#include"obs/eSDKOBS.h"
#include<QDebug>
#include<QMap>
//#include<QTimer>
//#include"SQL/dbSqlClass.h"


typedef struct put_file_object_callback_data
{
	FILE *infile;
	uint64_t content_length;
	obs_status ret_status;
} put_file_object_callback_data;
typedef struct head_object_data
{
	obs_status ret_status;
	int object_length;
}head_object_data;

class UpFile_OBS_Thread : public QThread
{
	Q_OBJECT

public:
	UpFile_OBS_Thread(QObject *parent=NULL);
	~UpFile_OBS_Thread();
	QString dbsqlpath;
	uint64_t open_file_and_get_length(char *localfile, put_file_object_callback_data *data);
	QString host_name;
	QString bucket_name;
	QString access_key;
	QString secret_access_key;
signals:
	void send_obs_up_eror(QStringList errlist);
	void send_obs_up_ok(QStringList upoklist);
	

public slots:
	//void upfile_OBS(QMap<int,QString> filepath);
	void upfile_OBS(QStringList filepath);
	
private:


private:
	QThread *m_ptrThread;
	//QTimer *obs_time;
	//dbSqlClass *m_obs_lpdbSqlClass;
	//bool sql_open;
	//QSqlDatabase m_db;
	QStringList upoklist;
	QStringList uperrlist;

};

#endif // UPFILE_OBS_THREAD_H
