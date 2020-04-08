#include "upfile_obs_thread.h"

#pragma execution_character_set("utf-8")
obs_status response_properties_callback(const obs_response_properties *properties, void *callback_data);
void mobs_complete_callback(obs_status status, const obs_error_details *error, void *callback_data);
int put_file_data_callback(int buffer_size, char *buffer, void *callback_data);

UpFile_OBS_Thread::UpFile_OBS_Thread(QObject *parent)
	: QThread(parent)
{
	//将当前线程移到另外一个线程
	m_ptrThread = new QThread;
	this->moveToThread(m_ptrThread);
	m_ptrThread->start();
	//dbsqlpath = "";
	//sql_open = false;
	//obs_time = new QTimer(this);

	//connect(obs_time,SIGNAL(timeout()),this,SLOT(upfile_OBS()));
	//设备运行时检查是否存在未上传文件
	//m_obs_lpdbSqlClass = new dbSqlClass;
	//upfile_OBS();
	//sleep(5);
	//obs_time->start(1000*10);
	host_name = "";
	bucket_name = "";
	access_key = "";
	secret_access_key = "";

	obs_status retu = OBS_STATUS_BUTT;
	retu = obs_initialize(OBS_INIT_ALL);
	qDebug() << "OBS初始化结果：" << retu;



}

UpFile_OBS_Thread::~UpFile_OBS_Thread()
{
	//m_db.close();

	m_ptrThread->terminate();
	m_ptrThread->wait();
	m_ptrThread->deleteLater();
	m_ptrThread = nullptr;
}
//回调函数

obs_status response_properties_callback(const obs_response_properties *properties, void *callback_data)
{
	obs_status rtn = OBS_STATUS_OK;
	(void)callback_data;
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
void mobs_complete_callback(obs_status status, const obs_error_details *error, void *callback_data)
{
	head_object_data *data = (head_object_data *)callback_data;
	data->ret_status = status;
	qDebug() << "进入回调函数mobs_complete_callback";
}
int put_file_data_callback(int buffer_size, char *buffer, void *callback_data)
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
	fclose(data->infile);
	return ret;
}

void UpFile_OBS_Thread::upfile_OBS(QStringList filepath)
{
	//qDebug() << "上传文件"<< filepath.size();
	upoklist.clear();
	uperrlist.clear();
	QByteArray  access_keyby = access_key.toLocal8Bit();
	QByteArray  secret_access_keyby = secret_access_key.toLocal8Bit();
	QByteArray  host_nameby = host_name.toLocal8Bit();
	QByteArray  bucket_nameby = bucket_name.toLocal8Bit();
	for (int i = 0; i < filepath.size(); i++)
	{
		qDebug() << "上传文件" << filepath[i];
		qDebug() << "access_keyby" << access_keyby.data();
		qDebug() << "secret_access_keyby" << secret_access_keyby.data();
		qDebug() << "host_nameby" << host_nameby.data();
		qDebug() << "bucket_nameby" << bucket_nameby.data();

		//上传对象名
		//QString s_key = "1.txt";
		//QString s_name = "D:/1.txt";
		QString s_key = filepath[i];
		QString s_name = filepath[i];
		QByteArray bay = s_key.toLocal8Bit();
		char *key = bay.data();
		//上传文件
		QByteArray bay_name = s_name.toLocal8Bit();
		char *file_name = bay_name.data();
		uint64_t content_length = 0;
		//初始化option
		obs_options option;
		init_obs_options(&option);
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
			{ &response_properties_callback,&mobs_complete_callback },
			&put_file_data_callback
		};
		put_object(&option, key, content_length, &put_properties, 0, &putobjectHandler, &data);
		if (data.ret_status == OBS_STATUS_OK)
		{
			upoklist << filepath[i];
		}
		else
		{
			uperrlist << filepath[i];
		}
	}
	//emit send_obs_up_eror(uperrlist);
	emit send_obs_up_ok(upoklist);

}
uint64_t UpFile_OBS_Thread::open_file_and_get_length(char *localfile, put_file_object_callback_data *data)
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
