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
	void directoryUpdated(const QString &path);  // Ŀ¼����ʱ���ã�path�Ǽ�ص�·��
	void fileUpdated(const QString &path);   // �ļ����޸�ʱ���ã�path�Ǽ�ص�·��

private:
	explicit FileSystemWatcher(QObject *parent = 0);

private:
	static FileSystemWatcher *m_pInstance; // ����
	QFileSystemWatcher *m_pSystemWatcher;  // QFileSystemWatcher����
	QMap<QString, QStringList> m_currentContentsMap; // ��ǰÿ����ص�����Ŀ¼�б�


	QStringList m_addPathFilesList;				//���
	QStringList m_updatePathFilesList;			//�޸�
	QStringList m_deletePathFilesList;			//ɾ��

	QMutex m_lock;
};

#endif // FILE_SYSTEM_WATCHER_H

