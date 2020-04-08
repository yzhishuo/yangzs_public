#include "upfile_obs_thread.h"
#include<QDir>
#include <windows.h>
#include <io.h>
#include <sys\stat.h>
#include<QTextStream>
#include <iostream>
#include <fstream>



#pragma execution_character_set("utf-8")
obs_status response_properties_callback(const obs_response_properties *properties, void *callback_data);
void mobs_complete_callback(obs_status status, const obs_error_details *error, void *callback_data);
int put_file_data_callback(int buffer_size, char *buffer, void *callback_data);
//obs_status get_response_properties_callback(const obs_response_properties *properties, void *callback_data);

FILE * write_to_file(char *localfile);
void get_object_complete_callback(obs_status status, const obs_error_details *error, void *callback_data);
obs_status get_object_data_callback(int buffer_size, const char *buffer, void *callback_data);

QMutex m_mutex_obs;

UpFile_OBS_Thread::UpFile_OBS_Thread(QObject *parent)
	: QThread(parent)
{
	//将当前线程移到另外一个线程
	m_ptrThread = new QThread;
	this->moveToThread(m_ptrThread);
	m_ptrThread->start();
	host_name = "";
	bucket_name = "";
	access_key = "";
	secret_access_key = "";
	file_montor_obs = "";

	obs_status retu = OBS_STATUS_BUTT;
	retu = obs_initialize(OBS_INIT_ALL);
#if DEBUG_RELEASE

	qDebug() << "OBS初始化结果：" << retu;
#endif // DEBUG_RELEASE

}

UpFile_OBS_Thread::~UpFile_OBS_Thread()
{
	//m_db.close();

	obs_deinitialize();

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
	else
	{
#if DEBUG_RELEASE

		qDebug() << "文件上传结束";
#endif // DEBUG_RELEASE
		
		fclose(data->infile);
	}
	//fclose(data->infile);
	return ret;
}

//obs_status get_response_properties_callback(const obs_response_properties *properties, void *callback_data)
//{
//	obs_status rtn = OBS_STATUS_OK;
//
//	(void)callback_data;
//	//qDebug
//	return rtn;
//}

FILE *write_to_file(char *localfile)
{
	FILE *outfile = 0;
	if (localfile) {
		struct stat buf;
		if (stat(localfile, &buf) == -1) {
			outfile = fopen(localfile, "wb");
			
		}
		else {
			outfile = fopen(localfile, "wb");
			
		}

		if (!outfile) {
			fprintf(stderr, "\nERROR: Failed to open output file %s: ",
				localfile);
			perror(0);
			exit(-1);
		}
	}
	else if (1) {
		fprintf(stderr, "\nERROR: get -s requires a file_name parameter\n");
	}
	else {
		outfile = stdout;
	}
	return outfile;
}
void get_object_complete_callback(obs_status status, const obs_error_details *error, void *callback_data)
{
	get_object_callback_data *data = (get_object_callback_data *)callback_data;
	data->ret_status = status;
}
int token_bucket = 0;
time_t produce_time = 0;

uint64_t LIMIT_FLOW_MAX_SPEED = 0;
void preduce_token(void)
{
	if (token_bucket == LIMIT_FLOW_MAX_SPEED)
	{
		return;
	}
	int times = 0; //
	if (produce_time == 0)
	{
		produce_time = time(0);
		times = 1;
	}
	else
	{
		time_t cur_time = time(0);
		times = (cur_time - produce_time);
		if (times > 0)
		{
			produce_time = cur_time;
		}
	}

	if (times > 0)
	{
		token_bucket = LIMIT_FLOW_MAX_SPEED;
	}
}
int get_token(int buffer_size)
{
	if (0 == LIMIT_FLOW_MAX_SPEED)
	{
		return 1;
	}
	preduce_token();

	if (token_bucket < buffer_size)
	{
		printf("has token %d  need token %d.\n", token_bucket, buffer_size);
		return 0;
	}

	token_bucket -= buffer_size;
	return 1;
}
obs_status get_object_data_callback(int buffer_size, const char *buffer, void *callback_data)
{
	m_mutex_obs.lock();
	while (0 == get_token(buffer_size))
	{
		Sleep(1);
	}
	m_mutex_obs.unlock();
	obs_status rtn = OBS_STATUS_BUTT;
	get_object_callback_data *data = (get_object_callback_data *)callback_data;
	size_t wrote = fwrite(buffer, 1, buffer_size, data->outfile);
	rtn = (wrote < (size_t)buffer_size) ? OBS_STATUS_AbortedByCallback : OBS_STATUS_OK;
#if DEBUG_RELEASE

	qDebug() << "写入文件大小" << wrote << "buffer_size=" << buffer_size;
	qDebug() << "写文件结果=" << obs_get_status_name(rtn);

#endif // DEBUG_RELEASE

	return rtn;
}
void UpFile_OBS_Thread::upfile_OBS(QStringList filepath)
{
	qDebug() << "上传文件"<< filepath.size();
	upoklist.clear();
	//uperrlist.clear();
	QByteArray  access_keyby = access_key.toLocal8Bit();
	QByteArray  secret_access_keyby = secret_access_key.toLocal8Bit();
	QByteArray  host_nameby = host_name.toLocal8Bit();
	QByteArray  bucket_nameby = bucket_name.toLocal8Bit();
	for (int i = 0; i < filepath.size(); i++)
	{
		qDebug() << "上传文件" << filepath[i];
		//qDebug() << "access_keyby" << access_keyby.data();
		//qDebug() << "secret_access_keyby" << secret_access_keyby.data();
		//qDebug() << "host_nameby" << host_nameby.data();
		//qDebug() << "bucket_nameby" << bucket_nameby.data();

		//QString path = QDir::toNativeSeparators(filepath[i]);
		QString path = filepath[i].replace("\\", "/");
		//上传对象名
		QString s_key = filepath[i];
		QString s_name = file_montor_obs+"/"+ path;
		//qDebug() << "上传文件KEY=" << s_key;
		qDebug() << "上传文件路径=" << s_name;

		QByteArray bay = s_key.toLocal8Bit();
		char *key = bay.data();
		//上传文件
		QByteArray bay_name = s_name.toLocal8Bit();
		char *file_name = bay_name.data();
		uint64_t content_length = 0;
		//初始化option
		obs_options option;
		init_obs_options(&option);

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
		//else
		//{
		//	uperrlist << filepath[i];
		//}
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
void UpFile_OBS_Thread::down_obs_inifile(QString down_obs_path)
{
	//char *file_name = "D:/1/2.txt";
	//QString ini_name= down_obs_path+"/OBS_file_bak.ini";
	//QString ini_name ="D:/1.rar";
	QByteArray filepath = down_obs_path.toLocal8Bit();
	//QByteArray filepath = ini_name.toLocal8Bit();
	char *file_name = filepath.data();
	obs_object_info object_info;
	obs_options option;
	init_obs_options(&option);

	QByteArray  access_keyby = down_access_key.toLocal8Bit();
	QByteArray  secret_access_keyby = down_secret_access_key.toLocal8Bit();
	QByteArray  host_nameby = down_host_name.toLocal8Bit();
	QByteArray  bucket_nameby = down_bucket_name.toLocal8Bit();

	option.bucket_options.access_key = access_keyby.data();
	option.bucket_options.secret_access_key = secret_access_keyby.data();
	option.bucket_options.host_name = host_nameby.data();
	option.bucket_options.bucket_name = bucket_nameby.data();

	option.bucket_options.protocol = OBS_PROTOCOL_HTTPS;

	// 设置下载的对象
	memset(&object_info, 0, sizeof(obs_object_info));
	object_info.key = "OBS_file.ini";
	//object_info.key = "q.rar";
	//根据业务需要设置存放下载对象数据的结构
	get_object_callback_data data;
	data.ret_status = OBS_STATUS_BUTT;
	data.outfile = write_to_file(file_name);
	// 定义范围下载参数
	obs_get_conditions getcondition;
	memset(&getcondition, 0, sizeof(obs_get_conditions));
	init_get_properties(&getcondition);
	getcondition.start_byte = 0;

	// 定义下载的回调函数
	obs_get_object_handler get_object_handler =
	{
		{ NULL,&get_object_complete_callback },
		&get_object_data_callback
	};
	get_object(&option, &object_info, &getcondition, 0, &get_object_handler, &data);

	if (data.ret_status == OBS_STATUS_OK)
	{
		//ui.textEdit->append("获取存储桶内对象信息成功:" + QString("%1").arg(obs_get_status_name(data.ret_status)));
	}
	else
	{
		//ui.textEdit->append("获取存储桶内对象信息失败！ret_status:" + QString("%1").arg(obs_get_status_name(data.ret_status)));
	}
#if DEBUG_RELEASE

	qDebug() << "文件写完成";

#endif // DEBUG_RELEASE
	
	fclose(data.outfile);
	//ui.textEdit->append("获取存储桶内对象信息结束");
}