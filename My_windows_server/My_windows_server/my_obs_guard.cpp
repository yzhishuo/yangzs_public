#include "my_obs_guard.h"




//����utf8����
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
	qDebug() << "��ȡ����������" << outputstr;
	if (outputstr.contains("MY_File_watch_Test.exe"))
	{
		qDebug() << "��鵽����������";
		//�رս���
		int pint= process->execute( "taskkill /im MY_File_watch_Test.exe /f");
		process->waitForFinished(3000);
		qDebug() << "����رս��"<<pint;
		process->start(runPath + "/MY_File_watch_Test.exe");

	}
	else
	{
		qDebug() << "��⵽����δ����";
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
		qDebug() << "����δ����-------";
		//process->start(runPath + "/MY_File_watch_Test.exe");
		break;
	case QProcess::Starting:
		qDebug() << "��������-------";
		break;
	case QProcess::Running:
		qDebug() << "��������-------";
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
	//	//qDebug() << "��������";
	//}
	//else
	//{
	//	//qDebug() << "����δ����";
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
		qDebug() << "����δ����";
		//process->start(runPath + "/MY_File_watch_Test.exe");
		break;
	case QProcess::Starting:
		qDebug() << "��������";
		break;
	case QProcess::Running:
		qDebug() << "��������";
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
		qDebug() << "��������ʧ�ܣ�";
		break;
	case QProcess::Crashed:
		qDebug() << "���������ɹ��������";
		break;
	case QProcess::Timedout:
		qDebug() << "���һ�ε���waitFor....()������ʱ����";
		break;
	case QProcess::ReadError:
		qDebug() << "�����д��ʱ����";
		break;
	case QProcess::WriteError:
		qDebug() << "������ж�ȡ���ݳ���";
		break;
	case QProcess::UnknownError:
		qDebug() << "����δ֪����";
		break;
	default:
		break;
	}
}
void My_obs_Guard::sltStateChangedReadOutput(void)
{
	qDebug() << "�����ȡ������Ϣ��"<<QString( process->readAllStandardOutput());
}
*/
void My_obs_Guard::sltStateChangedfinshed(int exitCode, QProcess::ExitStatus exitStatus)
{
	qDebug() << "������ý��" << exitCode;
	switch (exitStatus)
	{
	case QProcess::NormalExit:
		qDebug() << "�����˳�";
		if (exitCode != 0)
		{
			//process->start(runPath + "/MY_File_watch_Test.exe");
			process->start();
		}	
		break;
	case QProcess::CrashExit:
		qDebug() << "�쳣�˳�";

		break;
	default:
		break;
	}
}
