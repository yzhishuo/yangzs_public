#pragma once

#include <QString>
#include <QMetaType>
#include <QImage>
#include <QPixmap>
#include <QVariant>
#include <QtMath>
#include <QObject>
#include <QDebug>
#include <QFont>
#include <time.h>


#define  _DEBUGLOG_dbSqlClass		0				//1打开log 0关闭

#define  _MYDATETIMEFORM	"yyyyMMdd.hhmmss.zzz"


//数据库查找排序
enum SQLSearchSortord
{

	SQLSortord_Up = 0,			// : 升序
	SQLSortord_Down,			// : 降序

};