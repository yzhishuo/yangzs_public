#include "obs_console_test.h"
//#include<QDebug>

#pragma execution_character_set("utf-8")
OBS_console_TEST::OBS_console_TEST(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	
	
	connect(ui.slider, SIGNAL(valueChanged(int)), this, SLOT(setslidervalu(int)));

	connect(ui.slider, &QSlider::sliderPressed, &myslid, &MySlider::MysliderPressed);
	connect(ui.slider, &QSlider::sliderReleased, &myslid, &MySlider::MysliderRelease);
	connect(ui.slider, &QSlider::sliderMoved, &myslid, &MySlider::MysliderMoved);

	//设置最大值
	slider_interval = 10;
	ui.slider->setMaximum(slider_interval);

	myslid.setsliderterval(slider_interval * 2);
	myslid.setslidnum(slider_interval);
	
	
	//设置步长
	ui.slider->setPageStep(0);//鼠标点击滑块移动步进值
	//设置显示刻度的位置
	ui.slider->setTickPosition(QSlider::TicksBelow);

	ui.slider->setValue(1);


	
}

OBS_console_TEST::~OBS_console_TEST()
{

}
void OBS_console_TEST::setslidervalu(int value)
{
	ui.lineEdit->setText(QString("%1").arg(value));
	ui.lineEdit_2->setText(QString("%1").arg(ui.slider->value()));
}