#include "myslider.h"


#pragma execution_character_set("utf-8")



int myslidnum = 0;//使用自定义控制测量时滑块变化时的距离
int myvalue = 0;
bool myslider_check = false;//点击的位置是否为滑块
bool slider_strateg = false;//是否启用自定义控制策略

MySlider::MySlider(QWidget *parent)
	: QSlider(parent)
{
	current = 0;
	curr_dur = 0;
	
	vale = 0;

	//安装事件过滤器
	this->installEventFilter(this);
}

MySlider::~MySlider()
{

}
void MySlider::setsliderterval(int terval)
{
	qDebug() << "设置滑块切换间隔 terval" << terval;
	myslidnum = terval;
}
void MySlider::setslidnum(int slidnum)
{
	qDebug() << "设置滑块步数 slidnum"<< slidnum;
	if (slidnum <= 0 )
	{
		slidnum = 1;
	}

	qDebug() << "滑动条宽度 mywidth" << this->width();
	//每个间隔距离
	int sdnum = this->width() / slidnum;
	qDebug() << "设置滑块切换间隔距离 slidnum"<< slidnum<<"       slidnum/2" << sdnum/2;

	//判断滑块切换间隔是否大于滑块步距一半，大于使用QT步距切换功能，小于则启用自定义步距切换功能
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
		qDebug() << "不做控制";
		return QObject::eventFilter(obj, event);
	}

	if (myslider_check)
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		if (event->type() == QEvent::MouseButtonRelease)
		{
			curr_dur = 0;
			current = 0;
			qDebug() << " 过滤事件下 鼠标松开";
		}
		if (event->type() == QEvent::MouseButtonPress)
		{
			qDebug() << "过滤事件下 鼠标按下";

			curr_dur = mouseEvent->pos().x();
			current = curr_dur;

		}
		vale = myvalue;
		if (event->type() == QEvent::MouseMove)//判断类型
		{
			qDebug() << "过滤事件下 鼠标移动";
			//获取当前鼠标按下的位置
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
				qDebug() << "增加 vale=" << vale;
				this->setValue(vale);
				
				//更新设置步骤位置
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
				qDebug() << "减小 vale=" << vale;
				this->setValue(vale);
				//更新设置步骤位置
				curr_dur = mouseEvent->pos().x();
				return true;
			}
			else
			{
				qDebug() << "保持不变 vale=" << vale;
				this->setValue(vale);
				return true;
			}
		}

	}

	return QObject::eventFilter(obj, event);
}
//滑块按下槽函数
void MySlider::MysliderPressed(void)
{
	qDebug() << "按下滑块";
	myslider_check = true;
}
//滑块松开槽函数
void MySlider::MysliderRelease(void)
{
	qDebug() << "松开滑块";

	myslider_check = false;
}
//滑块移动槽函数
void MySlider::MysliderMoved(int value)
{
	qDebug() << "滑块移动" << value;
	myvalue = value;
}
