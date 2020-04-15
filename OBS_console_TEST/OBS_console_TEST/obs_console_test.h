#ifndef OBS_CONSOLE_TEST_H
#define OBS_CONSOLE_TEST_H

#include <QtWidgets/QWidget>
#include "ui_obs_console_test.h"

#include<QDebug>
#include<QMouseEvent>

#include"myslider.h"

class OBS_console_TEST : public QWidget
{
	Q_OBJECT

public:
	OBS_console_TEST(QWidget *parent = 0);
	~OBS_console_TEST();
	int slider_interval;

private slots:
	void setslidervalu(int value);


private:
	Ui::OBS_console_TESTClass ui;
	MySlider myslid;
};

#endif // OBS_CONSOLE_TEST_H
