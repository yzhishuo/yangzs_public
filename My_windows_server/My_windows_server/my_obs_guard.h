#ifndef MY_OBS_GUARD_H
#define MY_OBS_GUARD_H

#include <QObject>
#include<QTimer>
#include<QProcess>
#include<QDebug>
#include<QSettings>
#include<QApplication>
#include<QFile>
class My_obs_Guard : public QObject
{
	Q_OBJECT

public:
	My_obs_Guard(QObject *parent=NULL);
	~My_obs_Guard();
	//void init(void);
private slots:
	//void open_obs(void);
	//void sltStateChanged(QProcess::ProcessState staproce);
	//void sltStateChanged(QProcess::ProcessState staproce);
	//void sltStateChangedError(QProcess::ProcessError proerror);
	//void sltStateChangedReadOutput(void);
	void sltStateChangedfinshed(int exitCode,QProcess::ExitStatus exitStatus);
private:
	//QTimer *Guard_time;
	QProcess *process;
	QString runPath;
};

#endif // MY_OBS_GUARD_H
