#include "my_windows_server.h"
#include<QDebug>
#include <QProcess>
#include<QStringList>
#include<QFile>
//#include <synchapi.h>
//设置utf8编码
#pragma execution_character_set("utf-8")
My_windows_server::My_windows_server(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//Guard_time = new QTimer();
	//connect(Guard_time,&QTimer::timeout,this,&My_windows_server::open_obs);
	//Guard_time->start(1000);


}

My_windows_server::~My_windows_server()
{

}
void My_windows_server::on_btn_start_clicked()
{
	qDebug() << "点击事件";
	qDebug() << "启动第三方程序开始";

	QString workpath = QApplication::applicationDirPath();
	
	QProcess process(this);
	//process.setWorkingDirectory(workpath);
	//process.start("D:/Debug/MY_File_watch_Test.exe");
	//启动一个进程，然后使其和当前进程脱离进程的父子关系
	process.startDetached(workpath+"/MY_File_watch_Test.exe");

	qDebug() << "启动第三方程序结束";
}
void My_windows_server::open_obs(void)
{
	QProcess process;
	process.start("tasklist", QStringList() << "-fi" << "imagename eq MY_File_watch_Test.exe");
	process.waitForFinished(5000);
	QString outputstr = QString::fromLocal8Bit(process.readAllStandardOutput());
	//qDebug() << "outputstr" << outputstr;
	if (outputstr.contains("MY_File_watch_Test.exe"))
	{
		//process.close();
		qDebug() << "程序启动";
		//Sleep(1000);
	}
	else
	{
		qDebug() << "程序未启动";
		process.startDetached("D:/Debug/MY_File_watch_Test.exe");
		//Sleep(1000);
	}
	process.close();
}
void My_windows_server::on_btn_new_file_clicked(void)
{
	//int n = 0;
	QFile file("D:/q.rar");
	file.open(QIODevice::ReadOnly);
	QByteArray bu = file.readAll();
	for (int i = 0; i < 100; i++)
	{
		QFile file_er("D:/YYing/"+QString("%1").arg(i)+".rar");
		file_er.open(QIODevice::WriteOnly);
		file_er.write(bu);
		file_er.close();
	}
	file.close();

}
