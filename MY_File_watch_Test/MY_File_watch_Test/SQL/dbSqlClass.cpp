#include "dbSqlClass.h"
#include <QApplication>
#include <QDebug>
#include <QDate>
#include <QMetaType>
#include <QSqlRecord>


//设置utf8编码
#pragma execution_character_set("utf-8")

dbSqlClass::dbSqlClass(QObject *parent)
	: QObject(parent)
{


	qDebug() << "patientSqlClass main thread" << QThread::currentThread();

	m_lpThread = new QThread(this);
	connect(m_lpThread, &QThread::started, this, &dbSqlClass::isDatabaseConnect);
	this->moveToThread(m_lpThread);
	m_lpThread->start();
}

dbSqlClass::~dbSqlClass()
{
	m_db.close();
	m_lpThread->terminate();
	m_lpThread->wait();
	m_lpThread->deleteLater();
}



/************************************************************************/
/* local database                                                      */
/************************************************************************/
bool dbSqlClass::isDatabaseConnect()
{
	qDebug() << "isDatabaseConnect begin" << QThread::currentThread();

	if (QSqlDatabase::contains("UMISQL"))
		m_db = QSqlDatabase::database("UMISQL");
	else
		m_db = QSqlDatabase::addDatabase("QSQLITE", "UMISQL");


	QString runPath = QApplication::applicationDirPath();
	QString sqlPath = runPath + "/LocalDcmMonitor.db";
	//	m_db.setDatabaseName("./localdb.db3");
	m_db.setDatabaseName(sqlPath);
	if (m_db.open())
		return true;
	else
		return false;
}

void dbSqlClass::insertOrUpdate_DataTo_table(const _StringVariantMap &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName)
{
	QMetaObject::invokeMethod(this, "invoke_insertOrUpdate_DataTo_table", Qt::QueuedConnection, Q_ARG(const _StringVariantMap &, addMap), Q_ARG(const QString &, keyID), Q_ARG(const QString &, valueID), Q_ARG(const QString &, sqlTableName));
}

bool dbSqlClass::invoke_insertOrUpdate_DataTo_table(const _StringVariantMap &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName)
{
	_StringVariantMapVector destDataMap;
	_StringVariantMap findMap;
	findMap.insert(keyID, valueID);
	bool findFlg = invoke_query_SQL(findMap, destDataMap, sqlTableName);

	if (destDataMap.count() == 0)
	{
		//插入
		return invoke_insert_DataTo_table(addMap, keyID, valueID, sqlTableName);
	}
	else
	{
		//update
		return invoke_Update_SQL(addMap, keyID, valueID, sqlTableName);
	}
}



void dbSqlClass::insert_DataTo_table(const _StringVariantMap &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName)
{
	QMetaObject::invokeMethod(this, "invoke_insert_DataTo_table", Qt::QueuedConnection, Q_ARG(const _StringVariantMap &, addMap), Q_ARG(const QString &, keyID), Q_ARG(const QString &, valueID), Q_ARG(const QString &, sqlTableName));
}

bool dbSqlClass::insert_DataTo_table_wait(const QMap<QString, QVariant> &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName)
{
	bool bRet = false;
	QMetaObject::invokeMethod(this, "invoke_insert_DataTo_table", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, bRet), Q_ARG(const _StringVariantMap &, addMap), Q_ARG(const QString &, keyID), Q_ARG(const QString &, valueID), Q_ARG(const QString &, sqlTableName));
	return bRet;
}

/*

QSqlQuery query;
query.prepare("INSERT INTO person (id, forename, surname) "
"VALUES (?, ?, ?)");
query.addBindValue(1001);
query.addBindValue("Bart");
query.addBindValue("Simpson");
query.exec();
*/
bool dbSqlClass::invoke_insert_DataTo_table(const _StringVariantMap &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName)
{
	if (!isDatabaseConnect())
	{
#if (_DEBUGLOG_dbSqlClass == 1)
		qDebug() << "数据库文件打不开";
#endif
		return false;
	}

	if (addMap.isEmpty() || keyID.isNull() || sqlTableName.isEmpty())
	{
#if (_DEBUGLOG_dbSqlClass == 1)
		qDebug() << "插入参数设置错误 addMap:"  << addMap << "keyID: " << keyID << "sqlTableName:" << sqlTableName;
#endif
		return false;
	}

	QSqlQuery query(m_db);

	QString keyStr = QString("(");
	QString valueStr = QString("VALUES (");

	QStringList keysList = addMap.keys();
	for (int i=0; i<keysList.count(); i++)
	{
		QString tempKey = keysList.at(i);

		qDebug() << tempKey << ": "
			<< addMap[tempKey].toString().toUtf8().data() << endl;

		keyStr += QString("'%1', ").arg(tempKey);
		valueStr += "?, ";
	}

	if (keyStr.endsWith(", "))
	{
		keyStr = keyStr.left(keyStr.length() - QString(", ").length());
		valueStr = valueStr.left(valueStr.length() - QString(", ").length());
		keyStr += ")";
		valueStr += ")";
	}
	else
		return false;


	//查找个数
	QString queryStr;
	queryStr += QString("INSERT INTO %1 ").arg(sqlTableName);
	queryStr += keyStr + " " + valueStr + ";";

	query.prepare(queryStr);

	for (int i = 0; i < keysList.count(); i++)
	{
		QString tempKey = keysList.at(i);
		query.bindValue(i, addMap[tempKey]);
	}

	bool result = query.exec();

	if (!result)
	{
#if (_DEBUGLOG_PROJECTYIYING == 1)
		qDebug() << "insert_series_table error: " << __LINE__ << __FILE__;
#endif
	}

	return result;
}



bool dbSqlClass::query_DataTo_table_wait(const _StringVariantMap &findMap, _StringVariantMapVector &destDataMap, const QString &sqlTableName, QString sort_keyName, int SortordType, int StartNO, int limitCnt)
{
	bool bRet = false;
	QMetaObject::invokeMethod(this, "invoke_query_SQL", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, bRet), Q_ARG(const _StringVariantMap &, findMap), Q_ARG(_StringVariantMapVector &, destDataMap),
		Q_ARG(const QString &, sqlTableName), Q_ARG(const QString &, sort_keyName), Q_ARG(int, SortordType), Q_ARG(int, StartNO), Q_ARG(int, limitCnt));
	return bRet;
}

bool dbSqlClass::invoke_query_SQL(const _StringVariantMap &findMap, _StringVariantMapVector &destDataMap, const QString &sqlTableName, QString sort_keyName, int SortordType, int StartNO, int limitCnt)
{
	destDataMap.clear();

	if (!isDatabaseConnect())
	{
		//do something
#if (_DEBUGLOG_dbSqlClass == 1)
		qDebug() << "openSQL ERROR!" << __LINE__ << __FILE__;
#endif
		return false;
	}

	if (findMap.isEmpty() || sqlTableName.isEmpty())
	{
#if (_DEBUGLOG_dbSqlClass == 1)
		qDebug() << "数据库名或 关键词 为空  sqlTableName：" << sqlTableName << "findMap: "  << findMap << __LINE__ << __FILE__;
#endif
		return false;
	}

	QString queryStr;
	queryStr += QString("select * from %1 where").arg(sqlTableName);

	QMapIterator<QString, QVariant> i(findMap);
	while (i.hasNext()) {
		i.next();
		queryStr += QString(" %1 = '%2' and").arg(i.key()).arg(i.value().toString());
	}

	if (queryStr.endsWith("and"))
	{
		queryStr = queryStr.left(queryStr.length() - QString("and").length());
	}

	if (!sort_keyName.isEmpty())
	{
		//排序
		queryStr += " ORDER BY";
		//排序
		if (SortordType == (int)SQLSortord_Up)
		{
			queryStr += QString(" %1").arg(sort_keyName);
		}
		else if (SortordType == SQLSortord_Down)
		{
			queryStr += QString(" %1 DESC").arg(sort_keyName);
		}

		////整理
		if (queryStr.endsWith(" ORDER BY"))
		{
			queryStr = queryStr.left(queryStr.length() - QString(" ORDER BY").length());
		}
	}

	//添加限制条数
	if (StartNO >= 0 && limitCnt > 0)
	{
		queryStr += QString(" LIMIT %1,%2").arg(StartNO).arg(limitCnt);
	}
	

	QSqlQuery query(m_db);
	bool result = query.exec(queryStr);

	if (!result)
	{
#if (_DEBUGLOG_PROJECTYIYING == 1)
		qDebug() << "query error: " << __LINE__ << __FILE__ << queryStr;
#endif
	}
	else
	{
		while (query.next())
		{
			QSqlRecord resultsql = query.record();
			_StringVariantMap tempMap;

			for (int i = 0; i < resultsql.count(); i++)
			{
				QString keyName = resultsql.fieldName(i);
				QVariant value = resultsql.value(i);

				tempMap.insert(keyName, value);
				//qDebug() << keyName.toUtf8().data() << ": "
				//	<< value.toString().toUtf8().data() << endl;
			}

			destDataMap << tempMap;
		}
	}

	return result;
}

bool dbSqlClass::Update_DataTo_table_wait(const _StringVariantMap &updateMap, const QString &keyID, const QString &valueID, const QString &sqlTableName)
{
	bool bRet = false;
	QMetaObject::invokeMethod(this, "invoke_Update_SQL", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, bRet), Q_ARG(const _StringVariantMap &, updateMap), Q_ARG(const QString &, keyID), Q_ARG(const QString &, valueID), Q_ARG(const QString &, sqlTableName));
	return bRet;
}

Q_INVOKABLE bool dbSqlClass::invoke_Update_SQL(const _StringVariantMap &updateMap, const QString &keyID, const QString &valueID, const QString &sqlTableName)
{
	if (!isDatabaseConnect())
	{
		//do something
#if (_DEBUGLOG_dbSqlClass == 1)
		qDebug() << "openSQL ERROR!" << __LINE__ << __FILE__;
#endif
		return false;
	}

	if (updateMap.isEmpty() || keyID.isNull() || sqlTableName.isEmpty())
	{
#if (_DEBUGLOG_dbSqlClass == 1)
		qDebug() << "更新参数设置错误 addMap:" << addMap << "keyID: " << keyID << "sqlTableName:" << sqlTableName;
#endif
		return false;
	}


	QSqlQuery query(m_db);
	//	QString queryStr = QString("UPDATE Patient SET %1 = %2 WHERE Pid = %3;").arg(attribTag).arg(attribValue).arg(Pid);
	QString queryStr = QString("UPDATE %1 SET ").arg(sqlTableName);

	QMapIterator<QString, QVariant> it(updateMap);
	while (it.hasNext())
	{
		it.next();
		queryStr += QString("%1 = '%2', ").arg(it.key()).arg(it.value().toString());
	}

	if (queryStr.endsWith(", "))
	{
		queryStr = queryStr.left(queryStr.length() - QString(", ").length());
		queryStr += " ";
	}

	queryStr += QString("WHERE %1 = '%2';").arg(keyID).arg(valueID);
	bool result = query.prepare(queryStr);
	result = query.exec();
	

	if (!result)
	{
#if (_DEBUGLOG_PROJECTYIYING == 1)
		qDebug() << "query error: " << __LINE__ << __FILE__ << queryStr;
#endif
	}

	return result;
}

void dbSqlClass::delete_DataTo_table(const QString &keyID, const QStringList &valueIDList, const QString &sqlTableName)
{
	QMetaObject::invokeMethod(this, "invoke_delete_SQL", Qt::QueuedConnection, Q_ARG(const QString &, keyID), Q_ARG(const QStringList &, valueIDList), Q_ARG(const QString &, sqlTableName));
}

bool dbSqlClass::delete_DataTo_table_wait(const QString &keyID, const QStringList &valueIDList, const QString &sqlTableName)
{
	bool bRet = false;
	QMetaObject::invokeMethod(this, "invoke_delete_SQL", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, bRet), Q_ARG(const QString &, keyID), Q_ARG(const QStringList &, valueIDList), Q_ARG(const QString &, sqlTableName));
	return bRet;
}

Q_INVOKABLE bool dbSqlClass::invoke_delete_SQL(const QString &keyID, const QStringList &valueIDList, const QString &sqlTableName)
{

	if (!isDatabaseConnect())
	{
		//do something
#if (_DEBUGLOG_dbSqlClass == 1)
		qDebug() << "openSQL ERROR!" << __LINE__ << __FILE__;
#endif
		return false;
	}

	if (keyID.isNull() || sqlTableName.isEmpty())
	{
#if (_DEBUGLOG_dbSqlClass == 1)
		qDebug() << "删除参数设置错误 " << "keyID: " << keyID << "sqlTableName:" << sqlTableName;
#endif
		return false;
	}


	//删除patient
//	QString queryStr = "DELETE FROM Patient WHERE";
	QString queryStr = QString("DELETE FROM %1 WHERE ").arg(sqlTableName);
	for (int i = 0; i < valueIDList.count(); i++)
	{
		queryStr += QString(" %1 = '%2' or").arg(keyID).arg(valueIDList.at(i));
	}

	if (queryStr.endsWith("or"))
	{
		queryStr = queryStr.left(queryStr.length() - QString("or").length());
	}

	QSqlQuery query(m_db);
	bool result = query.exec(queryStr);

	if (!result)
	{
#if (_DEBUGLOG_PROJECTYIYING == 1)
		qDebug() << "delete_patient_table error: " << __LINE__ << __FILE__ << queryStr;
#endif
	}

	return result;
}