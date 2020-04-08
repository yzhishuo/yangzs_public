#include "my_file_watch_test.h"
//#include<QDebug>
#include<QDateTime>
#include<Windows.h>
#include<TlHelp32.h>
#include<QDebug>
#include<QSqlRecord>
#include <QFileDialog>

#include<QSettings>//读写ini文件

//设置utf8编码
#pragma execution_character_set("utf-8")


obs_status mresponse_properties_callback(const obs_response_properties *properties, void *callback_data);
void mmobs_complete_callback(obs_status status, const obs_error_details *error, void *callback_data);
int mput_file_data_callback(int buffer_size, char *buffer, void *callback_data);


MY_File_watch_Test::MY_File_watch_Test(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	ui.textEdit->append("开始时检查文件夹变化");
	ui.Lined_folder_path->setText(" ");
	sql_file_PathID = "";
	sql_file_DateTime = "";
	monitor_time = 0;

	mlfielthread = new File_Monitoring_Thread;
	//mlfielthread->addFilePath("D://1");
	connect(this, &MY_File_watch_Test::sen_mondir,mlfielthread,&File_Monitoring_Thread::start_FileMoniforing);
	connect(mlfielthread, &File_Monitoring_Thread::send_addfile,	 this, &MY_File_watch_Test::slot_addfile);
	connect(mlfielthread, &File_Monitoring_Thread::send_deletefile,  this, &MY_File_watch_Test::slot_deletefile);
	connect(mlfielthread, &File_Monitoring_Thread::send_moniforfile, this, &MY_File_watch_Test::slot_moniforfile);
	connect(mlfielthread, &File_Monitoring_Thread::send_oldnamefile, this, &MY_File_watch_Test::slot_oldnamefile);
	
	m_lpdbSqlClass = new dbSqlClass;

	mupfielobsthread = new UpFile_OBS_Thread;
	connect(this,&MY_File_watch_Test::sen_upfilepath,mupfielobsthread,&UpFile_OBS_Thread::upfile_OBS);
	connect(mupfielobsthread, &UpFile_OBS_Thread::send_obs_up_ok, this, &MY_File_watch_Test::slot_obs_sql_fileflg);
	//mupfielobsthread->dbsqlpath = QApplication::applicationDirPath() + "/LocalDcmMonitor.db";
	//obs_status retu = OBS_STATUS_BUTT; 
	//retu = obs_initialize(OBS_INIT_ALL);
	//ui.textEdit->append("OBS初始化="+QString("%1").arg(retu));
	obs_time = new QTimer(this);
	connect(obs_time, SIGNAL(timeout()), this, SLOT(time_out_upobs()));
	open_ini();
	obs_time->start(1000 * monitor_time);




}

MY_File_watch_Test::~MY_File_watch_Test()
{

}
int MY_File_watch_Test::open_ini(void)
{
	int rtn = 0;
	QString runPath = QApplication::applicationDirPath();
	QSettings *configini = new QSettings(runPath+"/OBS_file.ini",QSettings::IniFormat);
	//qDebug() << "host_name=" << configini->value("host_name/host_name").toString();
	//qDebug() << "bucket_name=" << configini->value("bucket_name/bucket_name").toString();
	//qDebug() << "AK_SK/access_key=" << configini->value("AK_SK/access_key").toString();
	//qDebug() << "AK_SK/secret_access_key=" << configini->value("AK_SK/secret_access_key").toString();
	mupfielobsthread->host_name = configini->value("host_name/host_name").toString();
	mupfielobsthread->bucket_name = configini->value("bucket_name/bucket_name").toString();
	mupfielobsthread->access_key = configini->value("AK_SK/access_key").toString();
	mupfielobsthread->secret_access_key = configini->value("AK_SK/secret_access_key").toString();

	 mhost_name = configini->value("host_name/host_name").toString();
	 mbucket_name = configini->value("bucket_name/bucket_name").toString();
	 maccess_key = configini->value("AK_SK/access_key").toString();
	 msecret_access_key = configini->value("AK_SK/secret_access_key").toString();

	 monitor_time = configini->value("monitor_time/monitor_time").toInt();
	 file_up_obs= configini->value("file_up_obs/file_up_obs").toInt();

	return rtn;
}
void MY_File_watch_Test::on_btn_open_filedir_clicked(void)
{
	//QString dirpath = getExistingDirectory(this, "选择目录", "./", QFileDialog::ShowDirsOnly);
	//GetOpenFileName();
	QString dirpath=QFileDialog::getExistingDirectory(this, "选择目录","./", QFileDialog::ShowDirsOnly);
	//qDebug() << "路径=" << dirpath;
	m_file_montor = dirpath;
	ui.Lined_folder_path->setText(m_file_montor);
}


void MY_File_watch_Test::on_btn_monitor_clicked(void)
{

	ui.textEdit->append("开启文件监控");
	if ((monitor_time == 0) | (monitor_time < 0))
	{
		ui.textEdit->append("开启文件监控时间值错误,值为:"+QString("1").arg(monitor_time));
		return;
	}
	//emit sen_mondir("D://1");
	emit sen_mondir(m_file_montor);
	//obs_time->start(1000 * monitor_time);
}
//回调函数

obs_status mresponse_properties_callback(const obs_response_properties *properties, void *callback_data)
{
	obs_status rtn = OBS_STATUS_OK;
	(void)callback_data;
	//qDebug
#define print_nonnull(name, field)                                 \
    do {                                                           \
        if (properties-> field) {                                  \
            printf("%s: %s\n", name, properties-> field);          \
        }                                                          \
    } while (0)

	print_nonnull("ETag", etag);
	print_nonnull("expiration", expiration);
	print_nonnull("website_redirect_location", website_redirect_location);
	print_nonnull("version_id", version_id);
	if (properties->last_modified > 0) {
		char timebuf[256] = { 0 };
		time_t t = (time_t)properties->last_modified;
		strftime(timebuf, sizeof(timebuf), "%Y-%m-%dT%H:%M:%SZ", gmtime(&t));
		printf("Last-Modified: %s\n", timebuf);
	}
	int i;
	for (i = 0; i < properties->meta_data_count; i++) {
		printf("x-amz-meta-%s: %s\n", properties->meta_data[i].name,
			properties->meta_data[i].value);
	}

	return rtn;
}
void mmobs_complete_callback(obs_status status, const obs_error_details *error, void *callback_data)
{
	head_object_data *data = (head_object_data *)callback_data;
	data->ret_status = status;
	qDebug() << "进入回调函数mobs_complete_callback";
}
int mput_file_data_callback(int buffer_size, char *buffer,void *callback_data)
{
	put_file_object_callback_data *data =
		(put_file_object_callback_data *)callback_data;
	int ret = 0;
	if (data->content_length) {
		int toRead = ((data->content_length > (unsigned)buffer_size) ?
			(unsigned)buffer_size : data->content_length);
		ret = fread(buffer, 1, toRead, data->infile);
	}
	uint64_t originalContentLength = data->content_length;
	data->content_length -= ret;
	if (data->content_length) {
		printf("%llu bytes remaining ", (unsigned long long)data->content_length);
		printf("(%d%% complete) ...\n",
			(int)(((originalContentLength - data->content_length) * 100) / originalContentLength));
	}
	int clo=fclose(data->infile);
	//qDebug() << "文件关闭情况" << clo;
	return ret;
}

void MY_File_watch_Test::on_btn_insert_clicked(void)
{


	/*
	QMap<QString, QVariant> addMap;
	QString keyID;
	QString valueID;
	QString sqlTableName;
	static int num = 111;
	num++;

	QString dateTime = QDateTime::currentDateTime().toString(_MYDATETIMEFORM);

	addMap.insert("FilePathID", QString::number(num));
	addMap.insert("DateTime", dateTime);
	addMap.insert("UpFinished", false);
	addMap.insert("Remark", "1");

	keyID = "FilePathID";
	valueID = num;
	sqlTableName = "DcmMonitorDb";

	bool flg = m_lpdbSqlClass->insert_DataTo_table_wait(addMap, keyID, valueID, sqlTableName);
	qDebug() << "数据库插入=" << flg;
	*/
	
	ui.textEdit->append("上传文件开始开始！");
	
	//上传对象名
	QString s_key = "D:/1.txt";//1.txt
	QString s_name = "D:/1.txt";
	
	QByteArray bay = s_key.toLocal8Bit();
	char *key = bay.data();
	//上传文件
	QByteArray bay_name = s_name.toLocal8Bit();
	char *file_name = bay_name.data();
	uint64_t content_length = 0;
	//初始化option
	obs_options option;
	init_obs_options(&option);


	QByteArray  access_keyby = maccess_key.toLocal8Bit();
	QByteArray  secret_access_keyby = msecret_access_key.toLocal8Bit();
	QByteArray  host_nameby = mhost_name.toLocal8Bit();
	QByteArray  bucket_nameby = mbucket_name.toLocal8Bit();


	//option.bucket_options.access_key = "HGQMSABSMPLCVQSSUTVW";
	//option.bucket_options.secret_access_key = "momVjOBXXlvDCDRAfiIFr5z2v3j8KwSl8cPWBxW6";
	//option.bucket_options.host_name = "obs.cn-east-3.myhuaweicloud.com";
	//option.bucket_options.bucket_name = "yangzs2";

	option.bucket_options.access_key = access_keyby.data();
	option.bucket_options.secret_access_key = secret_access_keyby.data();
	option.bucket_options.host_name = host_nameby.data();
	option.bucket_options.bucket_name = bucket_nameby.data();

	//使用HTTPS上传
	option.bucket_options.protocol = OBS_PROTOCOL_HTTPS;
	//初始化上传对象属性
	obs_put_properties put_properties;
	init_put_properties(&put_properties);
	//初始化存储上传数据结构体
	put_file_object_callback_data data;
	memset(&data, 0, sizeof(put_file_object_callback_data));
	//打开文件，并获取文件长度
	content_length = open_file_and_get_length(file_name, &data);
	//设置回调函数
	obs_put_object_handler putobjectHandler =
	{
		{ &mresponse_properties_callback,&mmobs_complete_callback },
		&mput_file_data_callback
	};
	put_object(&option, key, content_length, &put_properties, 0, &putobjectHandler, &data);
	if (data.ret_status == OBS_STATUS_OK)
	{
		ui.textEdit->append("上传文件成功:" + QString("%1").arg(obs_get_status_name(data.ret_status)));
	}
	else
	{
		ui.textEdit->append("上传文件失败！ret_status:" + QString("%1").arg(obs_get_status_name(data.ret_status)));
	}
	//int clo=fclose(data.infile);
	ui.textEdit->append("上传文件结束");
	
}

uint64_t MY_File_watch_Test::open_file_and_get_length(char *localfile, put_file_object_callback_data *data)
{
	uint64_t content_length = 0;
	const char *body = 0;
	if (!content_length)
	{
		struct stat statbuf;
		if (stat(localfile, &statbuf) == -1)
		{
			//qDebug() << "Failed to stat file";
			fprintf(stderr, "\nERROR: Failed to stat file %s: ",
				localfile);
			perror(0);
			exit(-1);
		}
		content_length = statbuf.st_size;
	}
	if (!(data->infile = fopen(localfile, "rb")))
	{
		//qDebug() << "Failed to open input file";
		fprintf(stderr, "\nERROR: Failed to open input file %s: ",
			localfile);
		perror(0);
		exit(-1);
	}
	data->content_length = content_length;


	return content_length;
}


void MY_File_watch_Test::on_btn_find_clicked(void)
{
	//列出所有信息
	QSqlDatabase m_db;
	if (QSqlDatabase::contains("UMISQL"))
		m_db = QSqlDatabase::database("UMISQL");
	else
		m_db = QSqlDatabase::addDatabase("QSQLITE", "UMISQL");

	QString runPath = QApplication::applicationDirPath();
	QString sqlPath = runPath + "/LocalDcmMonitor.db";
	//	m_db.setDatabaseName("./localdb.db3");
	m_db.setDatabaseName(sqlPath);
	if (m_db.open())
	{
		qDebug() << "打开成功";
	}
	else
	{
		qDebug() << "打开失败";
	}


	//QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
	QSqlQuery query(m_db);
	query.exec("select * from DcmMonitorDb");
	QSqlRecord rec = query.record();
	qDebug() << QObject::tr("DcmMonitorDb表字段数：") << rec.count();
	int index = 0;
	QString file_path = "";
	QVariant addMap;
	while (query.next())
	{
		//for (int index = 0; index < 4; index++)
		//{
		//	qDebug() << query.value(index) << " ";
		//}
		qDebug() << query.value(0) << " ";
		qDebug() << query.value(1) << " ";
		qDebug() << query.value(2) << " ";
		qDebug() << query.value(3) << " ";
		addMap = query.value(0);
		file_path = addMap.toString();
		index = QString::compare(file_path, sql_file_PathID);
		if (0 == index)
		{
			addMap = query.value(1);
			sql_file_DateTime = addMap.toString();
			qDebug() << "数据库中数据=" << file_path << sql_file_DateTime;
			break;
		}
		qDebug() <<"123";
		qDebug() << "\n";
	}
	m_db.close();
}
void MY_File_watch_Test::on_btn_update_clicked(void)
{
	//QMap<int, QString> filepath;

	//查询数据库
	_StringVariantMap findDataMap;
	QString keyID;
	QString valueID;
	QString sqlTableName;
	_StringVariantMapVector destDataMap;
	QString sort_keyName = "DateTime";
	int SortordType = SQLSortord_Up;

	//	keyID = "FilePathID";
	//	valueID = QString::number(101);
	sqlTableName = "DcmMonitorDb";
	//findDataMap.insert("UpFinished", 0);
	findDataMap.insert("UpFinished", "false");

	bool flg = m_lpdbSqlClass->query_DataTo_table_wait(findDataMap, destDataMap, sqlTableName, sort_keyName, SortordType);
	QStringList filelist;
	filelist.clear();
	for (int i = 0; i<destDataMap.count(); i++)
	{
		_StringVariantMap tempMap = destDataMap.at(i);
		filelist << tempMap["FilePathID"].toString();
	}
	emit sen_upfilepath(filelist);
	//mupfielobsthread->upfile_OBS(filelist);
}
void MY_File_watch_Test::on_btn_delete_clicked(void)
{
	QString keyID;
	QStringList valueIDList;
	QString sqlTableName;
	//keyID = "FilePathID";
	keyID = "DateTime";
	//valueIDList << QString::number(112);
	//valueIDList << "20200326.112752.084";
	valueIDList << "20200326.112754.614";
	sqlTableName = "DcmMonitorDb";

	m_lpdbSqlClass->delete_DataTo_table(keyID, valueIDList, sqlTableName);

}
void MY_File_watch_Test::slot_addfile(QString path)
{
	ui.textEdit->append("新加文件="+ path);
	QMap<QString, QVariant> addMap;
	QString keyID;
	QString valueID;
	QString sqlTableName;
	static int num = 0;
	num++;
	QString filedir = "";
	filedir = m_file_montor + "/" + path;
	ui.textEdit->append("新加文件=" + filedir);

	QFile file(filedir);
	if (file.open(QIODevice::ReadOnly))
	{
		ui.textEdit->append("打开成功");
		file.close();
	}
	else
	{
		ui.textEdit->append("新添加的是文件夹不是文件，不能进行上传和添加到数据库，请添加一个文件！");
		return;
	}



	QString dateTime = QDateTime::currentDateTime().toString(_MYDATETIMEFORM);

	//addMap.insert("FilePathID", QString::number(num));//变化的文件名使用绝对路径
	addMap.insert("FilePathID", filedir);//变化的文件名使用绝对路径
	addMap.insert("DateTime", dateTime);
	//addMap.insert("UpFinished", false);
	addMap.insert("UpFinished", "false");
	addMap.insert("Remark", "1");

	keyID = "FilePathID";
	valueID = num;
	sqlTableName = "DcmMonitorDb";

	bool flg = m_lpdbSqlClass->insert_DataTo_table_wait(addMap, keyID, valueID, sqlTableName);
	qDebug() << "数据库插入=" << flg;



}
void MY_File_watch_Test::slot_deletefile(QString path)
{

	
	QString filedir = "";
	filedir = m_file_montor + "/" + path;
	ui.textEdit->append("删除文件=" + filedir);

	QString keyID;
	QStringList valueIDList;
	QString sqlTableName;
	keyID = "FilePathID";
	valueIDList << filedir;

	sqlTableName = "DcmMonitorDb";

	m_lpdbSqlClass->delete_DataTo_table(keyID, valueIDList, sqlTableName);


}
void MY_File_watch_Test::slot_moniforfile(QString path)
{
	//判断传进来的路径是否为文件
	//path.endsWith(".doc")
	QString filedir = "";
	filedir = m_file_montor + "/" + path;
	//ui.textEdit->append("被修改文件=" + filedir);
	//if (!path.endsWith(".txt"))
	//{
	//	ui.textEdit->append("被修改的不是文件而是文件夹");
	//	return;
	//}

	QFile file(filedir);
	if (file.open(QIODevice::ReadOnly))
	{
		//ui.textEdit->append("打开成功");
		file.close();
	}
	else
	{
		//ui.textEdit->append("打开失败");
		return;
	}
	ui.textEdit->append("被修改文件为：" + filedir);
	//ui.textEdit->append("被修改的是文件而不是文件夹");
	//on_btn_find_clicked();
	//sql_file_PathID = filedir;
	QMap<QString, QVariant> updateMap;
	QString keyID;
	QString valueID;
	QString sqlTableName;
	keyID = "FilePathID";
	valueID = filedir;
	sqlTableName = "DcmMonitorDb";

	//updateMap.insert("UpFinished", false);
	updateMap.insert("UpFinished", "false");
	//updateMap.insert("Remark", "1");

	bool flg = m_lpdbSqlClass->Update_DataTo_table_wait(updateMap, keyID, valueID, sqlTableName);

}
void MY_File_watch_Test::slot_oldnamefile(QString oldpath, QString newpath)
{
	//ui.textEdit->append("文件被重命名-原名：" + oldpath+"现名："+ newpath);
	QString dateTime = QDateTime::currentDateTime().toString(_MYDATETIMEFORM);
	QString oldfiledir = "";
	QString newfiledir = "";
	oldfiledir = m_file_montor + "/" + oldpath;
	ui.textEdit->append("文件原名=" + oldfiledir);
	newfiledir = m_file_montor + "/" + newpath;
	ui.textEdit->append("文件现名=" + newfiledir);
	sql_file_PathID = oldfiledir;

	//删除数据库中原数据
	slot_deletefile(oldpath);
	//新增数据库数据
	slot_addfile(newpath);



//	on_btn_find_clicked();

	//更新文件名
//	QMap<QString, QVariant> updateMap;
//	QString keyID;
//	QString valueID;
//	QString sqlTableName;
//	keyID = "DateTime";
//	valueID = sql_file_DateTime;
//	sqlTableName = "DcmMonitorDb";
//	updateMap.insert("FilePathID", newfiledir);
//	bool flg = m_lpdbSqlClass->Update_DataTo_table_wait(updateMap, keyID, valueID, sqlTableName);
	//更新修改时间
//	if (flg)
//	{
	//	updateMap.clear();
	//	Sleep(1000);
	//	keyID = "FilePathID";
	//	valueID = newfiledir;
	//	sqlTableName = "DcmMonitorDb";
	//	updateMap.insert("DateTime", dateTime);
	//	flg = m_lpdbSqlClass->Update_DataTo_table_wait(updateMap, keyID, valueID, sqlTableName);
//	}

}

void MY_File_watch_Test::slot_obs_sql_fileflg(QStringList upoklist)
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

}
void MY_File_watch_Test::time_out_upobs(void )
{
	QString dateTime = QDateTime::currentDateTime().toString("hh");
	//qDebug() << "当前系统时间：" << dateTime;
	int timInt = dateTime.toInt();
	//qDebug() << "时间=" << timInt;
	if ((timInt == file_up_obs))
	{
		qDebug() << "到达设定上传时间";
		on_btn_update_clicked();
			
	}
	else
	{
		qDebug() << "未到达设定上传时间";
	}
}