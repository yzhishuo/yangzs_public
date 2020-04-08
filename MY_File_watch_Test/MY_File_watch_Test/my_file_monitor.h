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
	//���ͼ���ļ�·��
	void sen_mondir(QString dir);
	//�ϴ���OBS�ļ��б�
	void sen_upfilepath(QStringList filepath);

private slots:

	void slot_addfile(QString path);
	void slot_deletefile(QString path);
	void slot_moniforfile(QString path);
	void slot_oldnamefile(QString oldpath, QString newpath);
	//�����ϴ��������sql���ݿ�״̬
	void slot_obs_sql_fileflg(QStringList upoklist);
	//��ʱ����ʱ�ۺ���
	void time_out_upobs(void);//�ϴ�obs
	void time_out_upfileinfor(void);//��ȡ�ļ������Ϣ
private:
	//void start_file_monitor(void);//�����ļ����
	void findsql_stateinfo(void);//�������ݿ�׼���ϴ�obs
	void open_onsini_writeini(void);//���������ļ����±��������ļ�
private:
	File_Monitoring_Thread *mlfielthread;
	UpFile_OBS_Thread *mupfielobsthread;
	dbSqlClass *m_lpdbSqlClass;

	QString m_file_montor;//�ļ����·��
	bool inifile_check;
	//bool check_upobs;
	QTimer *obs_time;
	QTimer *file_time;
	int monitor_time;//����ļ����ʱ�䵥λ��
	int file_up_obs;//�����ϴ��ļ���obs��ÿ��̶�ʱ��
	int updatefile_time;//��ȡ�ļ��仯�Ķ�ʱʱ��
	QString file_type;
	//QString down_obs_ini_path;//��obs������ini�ļ������·��

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
