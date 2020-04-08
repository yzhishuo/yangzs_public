#include "my_file_monitor.h"


QStringList addfileList;
QStringList deletefileList;
QStringList moniforfileList;
QStringList oldnamefileList;

QMutex m_mutex_add;
QMutex m_mutex_dele;
QMutex m_mutex_monifor;
QMutex m_mutex_oldname;

//设置utf8编码
#pragma execution_character_set("utf-8")
My_File_Monitor::My_File_Monitor(QObject *parent)
	: QObject(parent)
{
#if DEBUG_RELEASE

	qDebug() << "My_File_Monitor My_File_Monitor My_File_Monitor My_File_Monitor";

#endif // DEBUG_RELEASE
	

}

My_File_Monitor::~My_File_Monitor()
{
	obs_time->stop();
	file_time->stop();

	mlfielthread->terminate();
	mlfielthread->wait();
	mlfielthread->deleteLater();
	mlfielthread = NULL;
}

void My_File_Monitor::init()
{
#if DEBUG_RELEASE

	qDebug() << "My_File_Monitor init";

#endif // DEBUG_RELEASE
	
	monitor_time = 0;
	updatefile_time = 0;
	file_up_obs = 0;
	inifile_check = false;
	m_file_montor = "";
	mhost_name = "";

	mlfielthread = new File_Monitoring_Thread;

	m_lpdbSqlClass = new dbSqlClass;

	mupfielobsthread = new UpFile_OBS_Thread;
	connect(this, &My_File_Monitor::sen_upfilepath, mupfielobsthread, &UpFile_OBS_Thread::upfile_OBS);
	connect(mupfielobsthread, &UpFile_OBS_Thread::send_obs_up_ok, this, &My_File_Monitor::slot_obs_sql_fileflg);

	open_ini();

	//配置文件出错什么也不干
	if (inifile_check)
	{
		//连接服务器下载更新配置文件
		QString runPath = QApplication::applicationDirPath();
		//mupfielobsthread->down_obs_inifile(runPath + "/OBS_file_bak.ini");
		//判断下载的文件是否存在
		QFile file_obs(runPath + "/OBS_file_bak.ini");
		if (file_obs.exists())//文件存在
		{
			file_obs.close();
			//下载的文件存在，读取文件写入配置文件和备份配置文件
			open_onsini_writeini();
			//qDebug() << "My_File_Monitor open_onsini_writeini";
			//删除下载的配置文件
			file_obs.remove();
		}
		if (monitor_time > 0)
		{
			obs_time = new QTimer();
			connect(obs_time, &QTimer::timeout, this, &My_File_Monitor::time_out_upobs);
			obs_time->start(1000 * monitor_time);
		}
		if (updatefile_time > 0)
		{
			file_time = new QTimer();
			connect(file_time, &QTimer::timeout, this, &My_File_Monitor::time_out_upfileinfor);
			file_time->start(1000 * updatefile_time);
		}
		//开启文件监控
		//start_file_monitor();
		QDir dir(m_file_montor);
		if (dir.exists())
		{
			mlfielthread->start();		
		}
	}

}

int My_File_Monitor::open_ini(void)
{
	int rtn = 0;
	QString runPath = QApplication::applicationDirPath();
	
	QFile file_obs(runPath + "/OBS_file.ini");
	if (!file_obs.exists())//配置文件不存在
	{
		//qDebug() << "配置文件不存在";
		QFile file_obsback(runPath + "/OBS_fileback.ini");
		if (!file_obs.exists())//备份配置文件也不存在
		{
			inifile_check = false;
			//创建空白配置文件(默认参数)
			QSettings *configiniback = new QSettings(runPath + "/OBS_fileback.ini", QSettings::IniFormat);
			configiniback->beginGroup("host_name");
			configiniback->setValue("host_name", "obs.cn-east-3.myhuaweicloud.com");
			configiniback->setValue("down_host_name", "obs.cn-east-3.myhuaweicloud.com");
			configiniback->endGroup();

			configiniback->beginGroup("bucket_name");
			configiniback->setValue("bucket_name", "yangzs2");
			configiniback->setValue("down_bucket_name", "yangzs2");
			configiniback->endGroup();

			configiniback->beginGroup("AK_SK");
			configiniback->setValue("access_key", "K0KDPGBMGODH7VWM3KCS");
			configiniback->setValue("secret_access_key", "4pJa4y25BO0qgeTbPdwliXbQ4dm4HTcLHAbAnjRC");
			configiniback->setValue("down_access_key", "K0KDPGBMGODH7VWM3KCS");
			configiniback->setValue("down_secret_access_key", "4pJa4y25BO0qgeTbPdwliXbQ4dm4HTcLHAbAnjRC");
			configiniback->endGroup();

			configiniback->beginGroup("monitor_time");
			configiniback->setValue("monitor_time", 00);
			configiniback->endGroup();

			configiniback->beginGroup("file_up_obs");
			configiniback->setValue("file_up_obs", 00);
			configiniback->endGroup();

			configiniback->beginGroup("file_type");
			configiniback->setValue("file_type", ".drw");
			configiniback->endGroup();

			configiniback->beginGroup("upfile_time");
			configiniback->setValue("upfile_time", 10);
			configiniback->endGroup();

			configiniback->beginGroup("monitor_filepath");
			configiniback->setValue("monitor_filepath", "D:/YiYing");
			configiniback->endGroup();

			//configiniback->beginGroup("down_obs_ini_path");
			//configiniback->setValue("down_obs_ini_path", "D:/YiYing/ini");
			//configiniback->endGroup();
		}
		else
		{
			//读取备份配置文件
			//QSettings *configini = new QSettings("C:/YiYing/OBS_fileback.ini", QSettings::IniFormat);
			QSettings *configini = new QSettings(runPath + "/OBS_fileback.ini", QSettings::IniFormat);

			mupfielobsthread->host_name = configini->value("host_name/host_name").toString();
			mupfielobsthread->bucket_name = configini->value("bucket_name/bucket_name").toString();
			mupfielobsthread->access_key = configini->value("AK_SK/access_key").toString();
			mupfielobsthread->secret_access_key = configini->value("AK_SK/secret_access_key").toString();

			mhost_name = configini->value("host_name/host_name").toString();
			mbucket_name = configini->value("bucket_name/bucket_name").toString();
			maccess_key = configini->value("AK_SK/access_key").toString();
			msecret_access_key = configini->value("AK_SK/secret_access_key").toString();

			mupfielobsthread->down_host_name = configini->value("host_name/down_host_name").toString();
			mupfielobsthread->down_bucket_name = configini->value("bucket_name/down_bucket_name").toString();
			mupfielobsthread->down_access_key = configini->value("AK_SK/down_access_key").toString();
			mupfielobsthread->down_secret_access_key = configini->value("AK_SK/down_secret_access_key").toString();

			mdown_host_name = configini->value("host_name/down_host_name").toString();
			mdown_bucket_name = configini->value("bucket_name/down_bucket_name").toString();
			mdown_access_key = configini->value("AK_SK/down_access_key").toString();
			mdown_secret_access_key = configini->value("AK_SK/down_secret_access_key").toString();

			monitor_time = configini->value("monitor_time/monitor_time").toInt();
			file_up_obs = configini->value("file_up_obs/file_up_obs").toInt();

			file_type = configini->value("file_type/file_type").toString();
			updatefile_time = configini->value("upfile_time/upfile_time").toInt();
			m_file_montor = configini->value("monitor_filepath/monitor_filepath").toString();
			//down_obs_ini_path = configini->value("down_obs_ini_path/down_obs_ini_path").toString();
			mupfielobsthread->file_montor_obs = m_file_montor;

			mlfielthread->FileListType = file_type.split(QRegExp("[ ]"), QString::SkipEmptyParts);
			mlfielthread->file_dir = m_file_montor;
			if (configini != NULL)
			{
				delete configini;
				configini = NULL;
			}
			if ((monitor_time > 0) & (updatefile_time > 0) & (!m_file_montor.isEmpty()) & (file_up_obs >0))
			{
				inifile_check = true;
			}
			//写配置文件
			QSettings *configiniback = new QSettings(runPath + "/OBS_file.ini", QSettings::IniFormat);
			configiniback->beginGroup("host_name");
			configiniback->setValue("host_name", mhost_name);
			configiniback->setValue("down_host_name", mdown_host_name);
			configiniback->endGroup();
			configiniback->beginGroup("bucket_name");
			configiniback->setValue("bucket_name", mbucket_name);
			configiniback->setValue("down_bucket_name", mdown_bucket_name);
			configiniback->endGroup();
			configiniback->beginGroup("AK_SK");
			configiniback->setValue("access_key", maccess_key);
			configiniback->setValue("secret_access_key", msecret_access_key);
			configiniback->setValue("down_access_key", mdown_access_key);
			configiniback->setValue("down_secret_access_key", mdown_secret_access_key);
			configiniback->endGroup();

			configiniback->beginGroup("monitor_time");
			configiniback->setValue("monitor_time", monitor_time);
			configiniback->endGroup();

			configiniback->beginGroup("file_up_obs");
			configiniback->setValue("file_up_obs", file_up_obs);
			configiniback->endGroup();

			configiniback->beginGroup("file_type");
			configiniback->setValue("file_type", file_type);
			configiniback->endGroup();

			configiniback->beginGroup("upfile_time");
			configiniback->setValue("upfile_time", updatefile_time);
			configiniback->endGroup();

			configiniback->beginGroup("monitor_filepath");
			configiniback->setValue("monitor_filepath", m_file_montor);
			configiniback->endGroup();

			//configiniback->beginGroup("down_obs_ini_path");
			//configiniback->setValue("down_obs_ini_path", down_obs_ini_path);
			//configiniback->endGroup();

			if (configiniback != NULL)
			{
				delete configiniback;
				configiniback = NULL;
			}

		}

	}
	else
	{
		//配置文件存在
		//qDebug() << "配置文件存在";
		QSettings *configini = new QSettings(runPath + "/OBS_file.ini", QSettings::IniFormat);

		mupfielobsthread->host_name = configini->value("host_name/host_name").toString();
		mupfielobsthread->bucket_name = configini->value("bucket_name/bucket_name").toString();
		mupfielobsthread->access_key = configini->value("AK_SK/access_key").toString();
		mupfielobsthread->secret_access_key = configini->value("AK_SK/secret_access_key").toString();


		mhost_name = configini->value("host_name/host_name").toString();
		mbucket_name = configini->value("bucket_name/bucket_name").toString();
		maccess_key = configini->value("AK_SK/access_key").toString();
		msecret_access_key = configini->value("AK_SK/secret_access_key").toString();

		mupfielobsthread->down_host_name = configini->value("host_name/down_host_name").toString();
		mupfielobsthread->down_bucket_name = configini->value("bucket_name/down_bucket_name").toString();
		mupfielobsthread->down_access_key = configini->value("AK_SK/down_access_key").toString();
		mupfielobsthread->down_secret_access_key = configini->value("AK_SK/down_secret_access_key").toString();

		mdown_host_name = configini->value("host_name/down_host_name").toString();
		mdown_bucket_name = configini->value("bucket_name/down_bucket_name").toString();
		mdown_access_key = configini->value("AK_SK/down_access_key").toString();
		mdown_secret_access_key = configini->value("AK_SK/down_secret_access_key").toString();

		monitor_time = configini->value("monitor_time/monitor_time").toInt();
		file_up_obs = configini->value("file_up_obs/file_up_obs").toInt();

		file_type = configini->value("file_type/file_type").toString();
		updatefile_time = configini->value("upfile_time/upfile_time").toInt();
		m_file_montor = configini->value("monitor_filepath/monitor_filepath").toString();
		//down_obs_ini_path = configini->value("down_obs_ini_path/down_obs_ini_path").toString();
		mupfielobsthread->file_montor_obs = m_file_montor;

		//mlfielthread->FileType = file_type;
		mlfielthread->FileListType = file_type.split(QRegExp("[ ]"), QString::SkipEmptyParts);
		mlfielthread->file_dir = m_file_montor;

		if (configini != NULL)
		{
			delete configini;
			configini = NULL;
		}
		if ((monitor_time > 0) & (updatefile_time > 0) & (!m_file_montor.isEmpty()) & (file_up_obs >0))
		{
			inifile_check = true;
		}
		//写备份配置文件
		QSettings *configiniback = new QSettings(runPath + "/OBS_fileback.ini", QSettings::IniFormat);
		configiniback->beginGroup("host_name");
		configiniback->setValue("host_name", mhost_name);
		configiniback->setValue("down_host_name", mdown_host_name);
		configiniback->endGroup();
		configiniback->beginGroup("bucket_name");
		configiniback->setValue("bucket_name", mbucket_name);
		configiniback->setValue("down_bucket_name", mdown_bucket_name);
		configiniback->endGroup();
		configiniback->beginGroup("AK_SK");
		configiniback->setValue("access_key", maccess_key);
		configiniback->setValue("secret_access_key", msecret_access_key);
		configiniback->setValue("down_access_key", mdown_access_key);
		configiniback->setValue("down_secret_access_key", mdown_secret_access_key);
		configiniback->endGroup();

		configiniback->beginGroup("monitor_time");
		configiniback->setValue("monitor_time", monitor_time);
		configiniback->endGroup();
		configiniback->beginGroup("file_up_obs");
		configiniback->setValue("file_up_obs", file_up_obs);
		configiniback->endGroup();
		configiniback->beginGroup("file_type");
		configiniback->setValue("file_type", file_type);
		configiniback->endGroup();

		configiniback->beginGroup("upfile_time");
		configiniback->setValue("upfile_time", updatefile_time);
		configiniback->endGroup();
		configiniback->beginGroup("monitor_filepath");
		configiniback->setValue("monitor_filepath", m_file_montor);
		configiniback->endGroup();

		//configiniback->beginGroup("down_obs_ini_path");
		//configiniback->setValue("down_obs_ini_path", down_obs_ini_path);
		//configiniback->endGroup();
		if (configiniback != NULL)
		{
			delete configiniback;
			configiniback = NULL;
		}
	}

	return rtn;
}
void My_File_Monitor::slot_addfile(QString path)
{
	QMap<QString, QVariant> addMap;
	QString keyID;
	QString valueID;
	QString sqlTableName;
	static int num = 1;
	QString dateTime = QDateTime::currentDateTime().toString(_MYDATETIMEFORM);
	addMap.insert("FilePathID", path);//变化的文件名使用相对路径
	addMap.insert("RelativePath", m_file_montor);//监控文件路径
	addMap.insert("DateTime", dateTime);
	addMap.insert("UpFinished", "false");
	addMap.insert("Remark", "1");

	keyID = "FilePathID";
	valueID = num;
	sqlTableName = "DcmMonitorDb";
	bool flg = m_lpdbSqlClass->insert_DataTo_table_wait(addMap, keyID, valueID, sqlTableName);
}
void My_File_Monitor::slot_deletefile(QString path)
{
	QString keyID;
	QStringList valueIDList;
	QString sqlTableName;
	keyID = "FilePathID";
	valueIDList << path;

	sqlTableName = "DcmMonitorDb";

	m_lpdbSqlClass->delete_DataTo_table(keyID, valueIDList, sqlTableName);
}
void My_File_Monitor::slot_moniforfile(QString path)
{
	QMap<QString, QVariant> updateMap;
	QString keyID;
	QString valueID;
	QString sqlTableName;
	keyID = "FilePathID";
	valueID = path;
	sqlTableName = "DcmMonitorDb";

	updateMap.insert("UpFinished", "false");

	bool flg = m_lpdbSqlClass->Update_DataTo_table_wait(updateMap, keyID, valueID, sqlTableName);
}
void My_File_Monitor::slot_oldnamefile(QString oldpath, QString newpath)
{
	//删除数据库中原数据
	slot_deletefile(oldpath);
	//新增数据库数据
	slot_addfile(newpath);
}
void My_File_Monitor::slot_obs_sql_fileflg(QStringList upoklist)
{
	//文件是否上传状态
	QMap<QString, QVariant> updateMap;
	QString keyID;
	QString valueID;
	QString sqlTableName;
	for (int i = 0; i < upoklist.size(); i++)
	{
		keyID = "FilePathID";
		valueID = upoklist.at(i);
		sqlTableName = "DcmMonitorDb";
		//updateMap.insert("UpFinished", true);
		updateMap.insert("UpFinished", "true");
		bool flg = m_lpdbSqlClass->Update_DataTo_table_wait(updateMap, keyID, valueID, sqlTableName);
	}
	obs_time->start(1000 * monitor_time);
}
//void My_File_Monitor::start_file_monitor(void)
//{
//	QDir dir(m_file_montor);
//	if (!dir.exists())
//	{
//		return;
//	}
//
//	emit sen_mondir(m_file_montor);
//}

void My_File_Monitor::time_out_upobs(void)
{
	QString dateTime = QDateTime::currentDateTime().toString("hh");
	int timInt = dateTime.toInt();

	if ((timInt == file_up_obs))
	{
#if DEBUG_RELEASE

		qDebug() << "到达设定上传时间";

#endif // DEBUG_RELEASE

		obs_time->stop();

		findsql_stateinfo();
		
	}
}
void My_File_Monitor::time_out_upfileinfor(void)
{
	//获取监控数据
	QStringList myaddfileList;
	QStringList mydeletefileList;
	QStringList mymoniforfileList;
	QStringList moldnamefileList;
#if DEBUG_RELEASE

	qDebug() << "进入文件更新数据库环节";

#endif // DEBUG_RELEASE
	
	myaddfileList.clear();
	mydeletefileList.clear();
	mymoniforfileList.clear();
	moldnamefileList.clear();
	//file_time->stop();
	if (addfileList.size() > 0)
	{
#if DEBUG_RELEASE

		qDebug() << "进入添加文件更新数据库";

#endif // DEBUG_RELEASE
		
		m_mutex_add.lock();
		myaddfileList = addfileList;
		addfileList.clear();
		m_mutex_add.unlock();
		for (int i = 0; i < myaddfileList.size(); i++)
		{
			QString path = myaddfileList.at(i);
			slot_addfile(path.replace("\\", "/"));
			//qDebug() << "添加文件为" << path.replace("\\","/");
			//qDebug() << "添加文件为" << myaddfileList.at(i);
			 //slot_addfile(myaddfileList.at(i));
		}
	}

	if (deletefileList.size() > 0)
	{
		
#if DEBUG_RELEASE

		qDebug() << "进入删除文件更新数据库";

#endif // DEBUG_RELEASE
		m_mutex_dele.lock();
		mydeletefileList = deletefileList;
		deletefileList.clear();
		m_mutex_dele.unlock();//slot_moniforfile
		for (int i = 0; i < mydeletefileList.size(); i++)
		{
			//slot_deletefile(mydeletefileList.at(i));
			QString path = mydeletefileList.at(i);
			slot_deletefile(path.replace("\\", "/"));
		}
	}

	if (moniforfileList.size() > 0)
	{
		
#if DEBUG_RELEASE

		qDebug() << "进入更新文件更新数据库";

#endif // DEBUG_RELEASE
		m_mutex_monifor.lock();
		mymoniforfileList = moniforfileList;
		moniforfileList.clear();
		m_mutex_monifor.unlock();
		for (int i = 0; i < mymoniforfileList.size(); i++)
		{
			//slot_moniforfile(mymoniforfileList.at(i));
			QString path = mymoniforfileList.at(i);
			slot_moniforfile(path.replace("\\", "/"));
		}
	}

	if (oldnamefileList.size() > 0)
	{
		
#if DEBUG_RELEASE

		qDebug() << "文件重命名更新数据库";

#endif // DEBUG_RELEASE
		m_mutex_oldname.lock();
		moldnamefileList = oldnamefileList;
		oldnamefileList.clear();
		m_mutex_oldname.unlock();
		for (int i = 0; i < moldnamefileList.size(); i = i + 2)
		{
			//slot_oldnamefile(moldnamefileList.at(i), moldnamefileList.at(i + 1));
			QString path1 = moldnamefileList.at(i);
			QString path2 = moldnamefileList.at(i + 1);
			slot_oldnamefile(path1.replace("\\", "/"), path2.replace("\\", "/"));
			qDebug() << "文件原名字" << path1.replace("\\", "/");
			qDebug() << "文件现名字" << path2.replace("\\", "/");
		}
	}

	//file_time->start(1000 * updatefile_time);
}
void My_File_Monitor::findsql_stateinfo(void)
{
	//查询数据库
	_StringVariantMap findDataMap;
	QString keyID;
	QString valueID;
	QString sqlTableName;
	_StringVariantMapVector destDataMap;
	QString sort_keyName = "DateTime";
	int SortordType = SQLSortord_Up;

	sqlTableName = "DcmMonitorDb";

	findDataMap.insert("UpFinished", "false");

	bool flg = m_lpdbSqlClass->query_DataTo_table_wait(findDataMap, destDataMap, sqlTableName, sort_keyName, SortordType);
#if DEBUG_RELEASE

	qDebug() << "新数据库查询结果" << flg << "destDataMap.count()="<< destDataMap.count();

#endif // DEBUG_RELEASE

	QStringList filelist;
	filelist.clear();
	for (int i = 0; i<destDataMap.count(); i++)
	{
		_StringVariantMap tempMap = destDataMap.at(i);
		filelist << tempMap["FilePathID"].toString();
	}
	emit sen_upfilepath(filelist);
}
void My_File_Monitor::open_onsini_writeini(void)
{
	QString runPath = QApplication::applicationDirPath();
	//读取下载的文件
	QSettings *ons_configini = new QSettings(runPath +"/OBS_file_bak.ini", QSettings::IniFormat);

	mupfielobsthread->host_name = ons_configini->value("host_name/host_name").toString();
	mupfielobsthread->bucket_name = ons_configini->value("bucket_name/bucket_name").toString();
	mupfielobsthread->access_key = ons_configini->value("AK_SK/access_key").toString();
	mupfielobsthread->secret_access_key = ons_configini->value("AK_SK/secret_access_key").toString();

	mhost_name = ons_configini->value("host_name/host_name").toString();
	mbucket_name = ons_configini->value("bucket_name/bucket_name").toString();
	maccess_key = ons_configini->value("AK_SK/access_key").toString();
	msecret_access_key = ons_configini->value("AK_SK/secret_access_key").toString();

	mupfielobsthread->down_host_name = ons_configini->value("host_name/down_host_name").toString();
	mupfielobsthread->down_bucket_name = ons_configini->value("bucket_name/down_bucket_name").toString();
	mupfielobsthread->down_access_key = ons_configini->value("AK_SK/down_access_key").toString();
	mupfielobsthread->down_secret_access_key = ons_configini->value("AK_SK/down_secret_access_key").toString();

	mdown_host_name = ons_configini->value("host_name/down_host_name").toString();
	mdown_bucket_name = ons_configini->value("bucket_name/down_bucket_name").toString();
	mdown_access_key = ons_configini->value("AK_SK/down_access_key").toString();
	mdown_secret_access_key = ons_configini->value("AK_SK/down_secret_access_key").toString();

	//qDebug() << "下载下来的文件 mhost_name=" << mhost_name;
	//qDebug() << "下载下来的文件 mbucket_name=" << mbucket_name;
	//qDebug() << "下载下来的文件 maccess_key=" << maccess_key;
	//qDebug() << "下载下来的文件 msecret_access_key=" << msecret_access_key;

	//qDebug() << "下载下来的文件 mdown_host_name=" << mdown_host_name;
	//qDebug() << "下载下来的文件 mdown_bucket_name=" << mdown_bucket_name;
	//qDebug() << "下载下来的文件 mdown_access_key=" << mdown_access_key;
	//qDebug() << "下载下来的文件 mdown_secret_access_key=" << mdown_secret_access_key;

	monitor_time = ons_configini->value("monitor_time/monitor_time").toInt();
	file_up_obs = ons_configini->value("file_up_obs/file_up_obs").toInt();
	file_type = ons_configini->value("file_type/file_type").toString();
	updatefile_time = ons_configini->value("upfile_time/upfile_time").toInt();
	m_file_montor = ons_configini->value("monitor_filepath/monitor_filepath").toString();
	//down_obs_ini_path = ons_configini->value("down_obs_ini_path/down_obs_ini_path").toString();
	mupfielobsthread->file_montor_obs = m_file_montor;
	//addfiel_currentsize = 0;
	//mlfielthread->FileType = file_type;
	mlfielthread->FileListType = file_type.split(QRegExp("[ ]"), QString::SkipEmptyParts);
	mlfielthread->file_dir = m_file_montor;

	if ((monitor_time > 0) & (updatefile_time > 0) & (!m_file_montor.isEmpty()) & (file_up_obs >0))
	{
		inifile_check = true;
	}
	else
	{
		inifile_check = false;
	}


	//写入配置文件
	QSettings *configini = new QSettings(runPath + "/OBS_file.ini", QSettings::IniFormat);
	configini->beginGroup("host_name");
	configini->setValue("host_name", mhost_name);
	configini->setValue("down_host_name", mdown_host_name);
	configini->endGroup();
	configini->beginGroup("bucket_name");
	configini->setValue("bucket_name", mbucket_name);
	configini->setValue("down_bucket_name", mdown_bucket_name);
	configini->endGroup();
	configini->beginGroup("AK_SK");
	configini->setValue("access_key", maccess_key);
	configini->setValue("secret_access_key", msecret_access_key);
	configini->setValue("down_access_key", mdown_access_key);
	configini->setValue("down_secret_access_key", mdown_secret_access_key);
	configini->endGroup();

	configini->beginGroup("monitor_time");
	configini->setValue("monitor_time", monitor_time);
	configini->endGroup();
	configini->beginGroup("file_up_obs");
	configini->setValue("file_up_obs", file_up_obs);
	configini->endGroup();
	configini->beginGroup("file_type");
	configini->setValue("file_type", file_type);
	configini->endGroup();

	configini->beginGroup("upfile_time");
	configini->setValue("upfile_time", updatefile_time);
	configini->endGroup();
	configini->beginGroup("monitor_filepath");
	configini->setValue("monitor_filepath", m_file_montor);
	configini->endGroup();

	//configini->beginGroup("down_obs_ini_path");
	//configini->setValue("down_obs_ini_path", down_obs_ini_path);
	//configini->endGroup();



	//写备份配置文件
	QSettings *configiniback = new QSettings(runPath+"/OBS_fileback.ini", QSettings::IniFormat);
	configiniback->beginGroup("host_name");
	configiniback->setValue("host_name", mhost_name);
	configiniback->setValue("down_host_name", mdown_host_name);
	configiniback->endGroup();
	configiniback->beginGroup("bucket_name");
	configiniback->setValue("bucket_name", mbucket_name);
	configiniback->setValue("down_bucket_name", mdown_bucket_name);
	configiniback->endGroup();
	configiniback->beginGroup("AK_SK");
	configiniback->setValue("access_key", maccess_key);
	configiniback->setValue("secret_access_key", msecret_access_key);
	configiniback->setValue("down_access_key", mdown_access_key);
	configiniback->setValue("down_secret_access_key", mdown_secret_access_key);
	configiniback->endGroup();

	configiniback->beginGroup("monitor_time");
	configiniback->setValue("monitor_time", monitor_time);
	configiniback->endGroup();
	configiniback->beginGroup("file_up_obs");
	configiniback->setValue("file_up_obs", file_up_obs);
	configiniback->endGroup();
	configiniback->beginGroup("file_type");
	configiniback->setValue("file_type", file_type);
	configiniback->endGroup();

	configiniback->beginGroup("upfile_time");
	configiniback->setValue("upfile_time", updatefile_time);
	configiniback->endGroup();
	configiniback->beginGroup("monitor_filepath");
	configiniback->setValue("monitor_filepath", m_file_montor);
	configiniback->endGroup();

	//configiniback->beginGroup("down_obs_ini_path");
	//configiniback->setValue("down_obs_ini_path", down_obs_ini_path);
	//configiniback->endGroup();

	if (configini != NULL)
	{
		delete configini;
		configini = NULL;
	}
	if (configiniback != NULL)
	{
		delete configiniback;
		configiniback = NULL;
	}
	if (ons_configini != NULL)
	{
		delete ons_configini;
		ons_configini = NULL;
	}
}