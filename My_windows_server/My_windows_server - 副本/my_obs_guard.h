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
	void init(void);
private slots:
	void open_obs(void);
private:
	QTimer *Guard_time;
};

#endif // MY_OBS_GUARD_H
