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


#define  _DEBUGLOG_dbSqlClass		0				//1��log 0�ر�

#define  _MYDATETIMEFORM	"yyyyMMdd.hhmmss.zzz"


//���ݿ��������
enum SQLSearchSortord
{

	SQLSortord_Up = 0,			// : ����
	SQLSortord_Down,			// : ����

};