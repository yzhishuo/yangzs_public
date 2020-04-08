#ifndef FILE_SYSTEM_WATCHER_H
#define FILE_SYSTEM_WATCHER_H

#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>
#include <QMutex>


class FileSystemWatcher : public QObject
{
	Q_OBJECT

public:
	static void addWatchPath(QString path);


	QStringList GetAddFilesList()
	{
		return m_addPathFilesList;
	}

	QStringList GetUpdateFilesList()
	{
		return m_updatePathFilesList;
	}

	QStringList GetDeleteFilesList()
	{
		return m_deletePathFilesList;
	}

	void ClearAllWatcherData()
	{
		m_lock.lock();
		m_addPathFilesList.clear();
		m_updatePathFilesList.clear();
		m_deletePathFilesList.clear();
		m_lock.unlock();
	}


public slots:
	void directoryUpdated(const QString &path);  // 目录更新时调用，path是监控的路径
	void fileUpdated(const QString &path);   // 文件被修改时调用，path是监控的路径

private:
	explicit FileSystemWatcher(QObject *parent = 0);

private:
	static FileSystemWatcher *m_pInstance; // 单例
	QFileSystemWatcher *m_pSystemWatcher;  // QFileSystemWatcher变量
	QMap<QString, QStringList> m_currentContentsMap; // 当前每个监控的内容目录列表


	QStringList m_addPathFilesList;				//添加
	QStringList m_updatePathFilesList;			//修改
	QStringList m_deletePathFilesList;			//删除

	QMutex m_lock;
};

#endif // FILE_SYSTEM_WATCHER_H

