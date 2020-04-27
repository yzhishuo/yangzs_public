#include "my_obs_guard.h"




//设置utf8编码
#pragma execution_character_set("utf-8")
My_obs_Guard::My_obs_Guard(QObject *parent)
	: QObject(parent)
{
	process = new QProcess(this);
	//connect(process, &QProcess::stateChanged, this, &My_obs_Guard::sltStateChanged);
	//connect(process, &QProcess::errorOccurred, this, &My_obs_Guard::sltStateChangedError);
	//connect(process, &QProcess::readyReadStandardOutput, this, &My_obs_Guard::sltStateChangedReadOutput);

	connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(sltStateChangedfinshed(int, QProcess::ExitStatus)));
	runPath = QApplication::applicationDirPath();
	process->start("tasklist", QStringList() << "-fi" << "imagename eq MY_File_watch_Test.exe");
	process->waitForFinished(5000);
	QString outputstr = QString::fromLocal8Bit(process->readAllStandardOutput());
	qDebug() << "获取到进程数据" << outputstr;
	if (outputstr.contains("MY_File_watch_Test.exe"))
	{
		qDebug() << "检查到程序已启动";
		//关闭进程
		int pint= process->execute( "taskkill /im MY_File_watch_Test.exe /f");
		process->waitForFinished(3000);
		qDebug() << "程序关闭结果"<<pint;
		process->start(runPath + "/MY_File_watch_Test.exe");

	}
	else
	{
		qDebug() << "监测到程序未启动";
		process->start(runPath + "/MY_File_watch_Test.exe");
	}
}

My_obs_Guard::~My_obs_Guard()
{
	//Guard_time->stop();
	if (process)
	{
		process->close();
		delete process;
		process = NULL;
	}
}
/*
void My_obs_Guard::init(void)
{
	Guard_time = new QTimer();
	connect(Guard_time, &QTimer::timeout, this, &My_obs_Guard::open_obs);
	//Guard_time->start(1000);
}
/*
void My_obs_Guard::open_obs(void)
{

	QProcess::ProcessState staproce=process->state();
	switch (staproce)
	{
	case QProcess::NotRunning:
		qDebug() << "程序未启动-------";
		//process->start(runPath + "/MY_File_watch_Test.exe");
		break;
	case QProcess::Starting:
		qDebug() << "程序启动-------";
		break;
	case QProcess::Running:
		qDebug() << "程序运行-------";
		break;
	default:
		break;
	}

	//QProcess process;
	//process.start("tasklist", QStringList() << "-fi" << "imagename eq MY_File_watch_Test.exe");
	//process.waitForFinished(5000);
	//QString outputstr = QString::fromLocal8Bit(process.readAllStandardOutput());
	////qDebug() << "outputstr" << outputstr;
	//if (outputstr.contains("MY_File_watch_Test.exe"))
	//{
	//	//qDebug() << "程序启动";
	//}
	//else
	//{
	//	//qDebug() << "程序未启动";
	//	QString runPath = QApplication::applicationDirPath();
	//	process.startDetached(runPath +"/MY_File_watch_Test.exe");
	//}
	//process.close();
}

void My_obs_Guard::sltStateChanged(QProcess::ProcessState staproce)
{
	switch (staproce)
	{
	case QProcess::NotRunning:
		qDebug() << "程序未启动";
		//process->start(runPath + "/MY_File_watch_Test.exe");
		break;
	case QProcess::Starting:
		qDebug() << "程序启动";
		break;
	case QProcess::Running:
		qDebug() << "程序运行";
		break;
	default:
		break;
	}
}
void My_obs_Guard::sltStateChangedError(QProcess::ProcessError proerror)
{
	switch (proerror)
	{
	case QProcess::FailedToStart:
		qDebug() << "程序启动失败！";
		break;
	case QProcess::Crashed:
		qDebug() << "程序启动成功后崩溃！";
		break;
	case QProcess::Timedout:
		qDebug() << "最后一次调用waitFor....()函数超时，！";
		break;
	case QProcess::ReadError:
		qDebug() << "向程序写入时出错！";
		break;
	case QProcess::WriteError:
		qDebug() << "向程序中读取数据出错！";
		break;
	case QProcess::UnknownError:
		qDebug() << "程序未知错误！";
		break;
	default:
		break;
	}
}
void My_obs_Guard::sltStateChangedReadOutput(void)
{
	qDebug() << "程序读取到的信息！"<<QString( process->readAllStandardOutput());
}
*/
void My_obs_Guard::sltStateChangedfinshed(int exitCode, QProcess::ExitStatus exitStatus)
{
	qDebug() << "程序调用结果" << exitCode;
	switch (exitStatus)
	{
	case QProcess::NormalExit:
		qDebug() << "正常退出";
		if (exitCode != 0)
		{
			//process->start(runPath + "/MY_File_watch_Test.exe");
			process->start();
		}	
		break;
	case QProcess::CrashExit:
		qDebug() << "异常退出";

		break;
	default:
		break;
	}
}
