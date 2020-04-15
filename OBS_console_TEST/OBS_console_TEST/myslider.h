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

	int current;//��ǰ��갴�µ�λ��
	int curr_dur;//�ϴ����ò���ʱ�����λ��

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
