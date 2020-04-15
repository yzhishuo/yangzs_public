#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>
#include<QMouseEvent>
#include<QDebug>

class MySlider : public QSlider
{
	Q_OBJECT

public:
	MySlider(QWidget *parent=nullptr);
	~MySlider();

	int current;//当前鼠标按下的位置
	int curr_dur;//上次设置步骤时的鼠标位置

	int vale ;
	
	bool eventFilter(QObject *obj, QEvent *event);
	void setslidnum(int slidnum);
	//void setslidVale(int vale);
	void setsliderterval(int terval);
public slots:
	void MysliderPressed(void);
	void MysliderRelease(void);
	void MysliderMoved(int value);
private:
	
	
};

#endif // MYSLIDER_H
