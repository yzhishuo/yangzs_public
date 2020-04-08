#ifndef MY_FILE_WATCH_TEST_H
#define MY_FILE_WATCH_TEST_H

#include <QtWidgets/QWidget>
#include "ui_my_file_watch_test.h"
//#include<QFileSystemWatcher>
//#include"filesystemwatcher.h"
#include "file_monitoring_thread.h"
#include<QDateTime>
#include"systemWatcher/FileSystemWatcher.h"
#include"Common/upDcmToCloudGloabs.h"
#include"SQL/dbSqlClass.h"

#include"upfile_obs_thread.h"
#include<QTimer>




/*
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
*/



class MY_File_watch_Test : public QWidget
{
	Q_OBJECT

public:
	MY_File_watch_Test(QWidget *parent = 0);
	~MY_File_watch_Test();
	uint64_t open_file_and_get_length(char *localfile, put_file_object_callback_data *data);
	int open_ini(void);
public slots:

	void slot_addfile(QString path);
	void slot_deletefile( QString path);
	void slot_moniforfile(QString path);
	void slot_oldnamefile(QString oldpath, QString newpath);
	//根据上传结果重置sql数据库状态
	void slot_obs_sql_fileflg(QStringList upoklist);


	void on_btn_open_filedir_clicked(void);
	void on_btn_monitor_clicked(void);
	void on_btn_insert_clicked(void);
	void on_btn_find_clicked(void);
	void on_btn_update_clicked(void);
	void on_btn_delete_clicked(void);

	void time_out_upobs(void);
private:
signals:
	   void sen_mondir(QString dir);
	   void sen_upfilepath(QStringList filepath);
	  
private:
	Ui::MY_File_watch_TestClass ui;
	File_Monitoring_Thread *mlfielthread;
	UpFile_OBS_Thread *mupfielobsthread;
	dbSqlClass *m_lpdbSqlClass;
	QString m_file_montor;
	QString sql_file_PathID;
	QString sql_file_DateTime;
	QTimer *obs_time;
	int monitor_time;//检查文件间隔时间单位秒
	int file_up_obs;//设置上传文件到obs的每天固定时间

	QString mhost_name;
	QString mbucket_name;
	QString maccess_key;
	QString msecret_access_key;


};

#endif // MY_FILE_WATCH_TEST_H
