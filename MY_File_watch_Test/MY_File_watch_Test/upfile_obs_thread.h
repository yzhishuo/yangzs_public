/**
***只做上传文件到obs，无其他操作
***
****/



#ifndef UPFILE_OBS_THREAD_H
#define UPFILE_OBS_THREAD_H

#include <QThread>
#include"obs/eSDKOBS.h"
#include<QDebug>
#include<QMap>
#include<QMutex>

//#include<QTimer>
//#include"SQL/dbSqlClass.h"

#define DEBUG_RELEASE 1


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
typedef struct get_object_callback_data
{
	FILE *outfile;
	obs_status ret_status;
}get_object_callback_data;
class UpFile_OBS_Thread : public QThread
{
	Q_OBJECT

public:
	UpFile_OBS_Thread(QObject *parent=NULL);
	~UpFile_OBS_Thread();
	//QString dbsqlpath;
	uint64_t open_file_and_get_length(char *localfile, put_file_object_callback_data *data);
	QString host_name;
	QString bucket_name;
	QString access_key;
	QString secret_access_key;

	QString down_host_name;
	QString down_bucket_name;
	QString down_access_key;
	QString down_secret_access_key;

	QString file_montor_obs;
	//QString down_obs_path;
	void down_obs_inifile(QString down_obs_path);


signals:
	void send_obs_up_eror(QStringList errlist);
	void send_obs_up_ok(QStringList upoklist);
	

public slots:
	//void upfile_OBS(QMap<int,QString> filepath);
	void upfile_OBS(QStringList filepath);
	



private:
	QThread *m_ptrThread;
	QStringList upoklist;
	//QStringList uperrlist;
	

};

#endif // UPFILE_OBS_THREAD_H
