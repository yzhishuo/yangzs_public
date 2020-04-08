#ifndef MY_FILE_MONITOR_H
#define MY_FILE_MONITOR_H

#include <QObject>
#include<QApplication>
#include<QFile>
#include<QSettings>
#include "file_monitoring_thread.h"
#include"upfile_obs_thread.h"
#include"SQL/dbSqlClass.h"
#include<QDateTime>
#include<QDir>
#include<QTimer>


class My_File_Monitor : public QObject
{
	Q_OBJECT

public:
	My_File_Monitor(QObject *parent=NULL);
	~My_File_Monitor();
	int open_ini(void);
	void init(void);


signals:
	//发送监控文件路径
	void sen_mondir(QString dir);
	//上传到OBS文件列表
	void sen_upfilepath(QStringList filepath);

private slots:

	void slot_addfile(QString path);
	void slot_deletefile(QString path);
	void slot_moniforfile(QString path);
	void slot_oldnamefile(QString oldpath, QString newpath);
	//根据上传结果重置sql数据库状态
	void slot_obs_sql_fileflg(QStringList upoklist);
	//定时器超时槽函数
	void time_out_upobs(void);//上传obs
	void time_out_upfileinfor(void);//获取文件监控信息
private:
	//void start_file_monitor(void);//开启文件监控
	void findsql_stateinfo(void);//查找数据库准备上传obs
	void open_onsini_writeini(void);//下载配置文件更新本地配置文件
private:
	File_Monitoring_Thread *mlfielthread;
	UpFile_OBS_Thread *mupfielobsthread;
	dbSqlClass *m_lpdbSqlClass;

	QString m_file_montor;//文件监控路径
	bool inifile_check;
	//bool check_upobs;
	QTimer *obs_time;
	QTimer *file_time;
	int monitor_time;//检查文件间隔时间单位秒
	int file_up_obs;//设置上传文件到obs的每天固定时间
	int updatefile_time;//获取文件变化的定时时间
	QString file_type;
	//QString down_obs_ini_path;//从obs上下载ini文件保存的路径

	QString mhost_name;
	QString mbucket_name;
	QString maccess_key;
	QString msecret_access_key;


	QString mdown_host_name;
	QString mdown_bucket_name;
	QString mdown_access_key;
	QString mdown_secret_access_key;

};

#endif // MY_FILE_MONITOR_H
