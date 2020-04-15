#include "my_obs_guard.h"




//ÉèÖÃutf8±àÂë
#pragma execution_character_set("utf-8")
My_obs_Guard::My_obs_Guard(QObject *parent)
	: QObject(parent)
{

}

My_obs_Guard::~My_obs_Guard()
{
	Guard_time->stop();
}
void My_obs_Guard::init(void)
{
	Guard_time = new QTimer();
	connect(Guard_time, &QTimer::timeout, this, &My_obs_Guard::open_obs);
	Guard_time->start(1000);
}
void My_obs_Guard::open_obs(void)
{
	QProcess process;
	process.start("tasklist", QStringList() << "-fi" << "imagename eq MY_File_watch_Test.exe");
	process.waitForFinished(5000);
	QString outputstr = QString::fromLocal8Bit(process.readAllStandardOutput());
	//qDebug() << "outputstr" << outputstr;
	if (outputstr.contains("MY_File_watch_Test.exe"))
	{
		//qDebug() << "³ÌÐòÆô¶¯";
	}
	else
	{
		//qDebug() << "³ÌÐòÎ´Æô¶¯";
		QString runPath = QApplication::applicationDirPath();
		process.startDetached(runPath +"/MY_File_watch_Test.exe");
	}
	process.close();
}