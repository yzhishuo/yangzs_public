#include "myslider.h"


#pragma execution_character_set("utf-8")



int myslidnum = 0;//ʹ���Զ�����Ʋ���ʱ����仯ʱ�ľ���
int myvalue = 0;
bool myslider_check = false;//�����λ���Ƿ�Ϊ����
bool slider_strateg = false;//�Ƿ������Զ�����Ʋ���

MySlider::MySlider(QWidget *parent)
	: QSlider(parent)
{
	current = 0;
	curr_dur = 0;
	
	vale = 0;

	//��װ�¼�������
	this->installEventFilter(this);
}

MySlider::~MySlider()
{

}
void MySlider::setsliderterval(int terval)
{
	qDebug() << "���û����л���� terval" << terval;
	myslidnum = terval;
}
void MySlider::setslidnum(int slidnum)
{
	qDebug() << "���û��鲽�� slidnum"<< slidnum;
	if (slidnum <= 0 )
	{
		slidnum = 1;
	}

	qDebug() << "��������� mywidth" << this->width();
	//ÿ���������
	int sdnum = this->width() / slidnum;
	qDebug() << "���û����л�������� slidnum"<< slidnum<<"       slidnum/2" << sdnum/2;

	//�жϻ����л�����Ƿ���ڻ��鲽��һ�룬����ʹ��QT�����л����ܣ�С���������Զ��岽���л�����
	if (sdnum/2 > myslidnum)
	{
		slider_strateg = false;
	}
	else
	{
		slider_strateg = true;
	}

}
bool MySlider::eventFilter(QObject *obj, QEvent *event)
{
	if (slider_strateg)
	{
		qDebug() << "��������";
		return QObject::eventFilter(obj, event);
	}

	if (myslider_check)
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		if (event->type() == QEvent::MouseButtonRelease)
		{
			curr_dur = 0;
			current = 0;
			qDebug() << " �����¼��� ����ɿ�";
		}
		if (event->type() == QEvent::MouseButtonPress)
		{
			qDebug() << "�����¼��� ��갴��";

			curr_dur = mouseEvent->pos().x();
			current = curr_dur;

		}
		vale = myvalue;
		if (event->type() == QEvent::MouseMove)//�ж�����
		{
			qDebug() << "�����¼��� ����ƶ�";
			//��ȡ��ǰ��갴�µ�λ��
			current = mouseEvent->pos().x();

			if (curr_dur == 0)
			{
				curr_dur = current;
			}
			qDebug() << "current=" << current << "curr_dur=" << curr_dur << "myslidnum" << myslidnum;
			qDebug() << "vale=" << vale;

			if ((current - curr_dur) > myslidnum)
			{
				vale = myvalue + 1;
				if (vale > this->maximum())
				{
					vale = this->maximum();
				}
				qDebug() << "���� vale=" << vale;
				this->setValue(vale);
				
				//�������ò���λ��
				curr_dur = mouseEvent->pos().x();
				return true;
			}
			else if ((curr_dur - current) > myslidnum)
			{
				vale = myvalue - 1;
				if (vale < this->minimum())
				{
					vale = this->minimum();
				}
				qDebug() << "��С vale=" << vale;
				this->setValue(vale);
				//�������ò���λ��
				curr_dur = mouseEvent->pos().x();
				return true;
			}
			else
			{
				qDebug() << "���ֲ��� vale=" << vale;
				this->setValue(vale);
				return true;
			}
		}

	}

	return QObject::eventFilter(obj, event);
}
//���鰴�²ۺ���
void MySlider::MysliderPressed(void)
{
	qDebug() << "���»���";
	myslider_check = true;
}
//�����ɿ��ۺ���
void MySlider::MysliderRelease(void)
{
	qDebug() << "�ɿ�����";

	myslider_check = false;
}
//�����ƶ��ۺ���
void MySlider::MysliderMoved(int value)
{
	qDebug() << "�����ƶ�" << value;
	myvalue = value;
}
