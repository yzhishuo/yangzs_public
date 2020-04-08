#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QThread>
#include <QMutex>
#include <QMetaObject>
#include "common/upDcmToCloudGloabs.h"

#ifndef _StringVariantMap
typedef QMap<QString, QVariant> _StringVariantMap;
typedef QVector<_StringVariantMap> _StringVariantMapVector;
#endif // !_StringVariantMap


class dbSqlClass : public QObject
{
	Q_OBJECT

public:
	dbSqlClass(QObject *parent = nullptr);
	~dbSqlClass();

	void insertOrUpdate_DataTo_table(const QMap<QString, QVariant> &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName);

	void insert_DataTo_table(const QMap<QString, QVariant> &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName);
	bool insert_DataTo_table_wait(const QMap<QString, QVariant> &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName);

	/*
	const _StringVariantMap &updateMap		key value ¶¼Ê¹ÓÃ×Ö·û´®
	QString sort_keyName, ÅÅÐò¹Ø¼ü×Ö
	int SortordType,		ÅÅÐòÀàÐÍ µ¹Ðð Ë³Ðò
	*/
	bool query_DataTo_table_wait(const _StringVariantMap &findMap, _StringVariantMapVector &destDataMap, const QString &sqlTableName, QString sort_keyName = "", int SortordType = SQLSortord_Up, int StartNO = 0, int limitCnt = 20);

	bool Update_DataTo_table_wait(const _StringVariantMap &updateMap, const QString &keyID, const QString &valueID, const QString &sqlTableName);

	void delete_DataTo_table(const QString &keyID, const QStringList &valueIDList, const QString &sqlTableName);
	bool delete_DataTo_table_wait(const QString &keyID, const QStringList &valueIDList, const QString &sqlTableName);
private:
	Q_INVOKABLE bool isDatabaseConnect();

	Q_INVOKABLE bool invoke_insertOrUpdate_DataTo_table(const QMap<QString, QVariant> &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName);

	Q_INVOKABLE bool invoke_insert_DataTo_table(const _StringVariantMap &addMap, const QString &keyID, const QString &valueID, const QString &sqlTableName);
	Q_INVOKABLE bool invoke_query_SQL(const _StringVariantMap &findMap, _StringVariantMapVector &destDataMap, const QString &sqlTableName, QString sort_keyName = "", int SortordType = SQLSortord_Up, int StartNO = 0, int limitCnt = 20);
	Q_INVOKABLE bool invoke_Update_SQL(const _StringVariantMap &updateMap, const QString &keyID, const QString &valueID, const QString &sqlTableName);
	Q_INVOKABLE bool invoke_delete_SQL(const QString &keyID, const QStringList &valueIDList, const QString &sqlTableName);

private:
	///////////////local database///////////////
	QSqlDatabase m_db;
	QThread *m_lpThread;
};

