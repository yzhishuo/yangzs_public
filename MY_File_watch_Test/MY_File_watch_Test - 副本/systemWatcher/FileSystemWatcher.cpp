#include <QDir>
#include <QFileInfo>
#include <qDebug>
#include <time.h>
#include "FileSystemWatcher.h"

FileSystemWatcher* FileSystemWatcher::m_pInstance = NULL;

FileSystemWatcher::FileSystemWatcher(QObject *parent)
	: QObject(parent)
{

}

// ����ļ���Ŀ¼
void FileSystemWatcher::addWatchPath(QString path)
{
	qDebug() << QString("Add to watch: %1").arg(path);

	if (m_pInstance == NULL)
	{
		m_pInstance = new FileSystemWatcher();
		m_pInstance->m_pSystemWatcher = new QFileSystemWatcher();

		// ����QFileSystemWatcher��directoryChanged��fileChanged�źŵ���Ӧ�Ĳ�
		connect(m_pInstance->m_pSystemWatcher, SIGNAL(directoryChanged(QString)), m_pInstance, SLOT(directoryUpdated(QString)));
		connect(m_pInstance->m_pSystemWatcher, SIGNAL(fileChanged(QString)), m_pInstance, SLOT(fileUpdated(QString)));
	}

	// ��Ӽ��·��
	m_pInstance->m_pSystemWatcher->addPath(path);

	// ������·����һ��Ŀ¼�����浱ǰ�����б�
	QFileInfo file(path);
	if (file.isDir())
	{
		const QDir dirw(path);
		m_pInstance->m_currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
	}
}

// ֻҪ�κμ�ص�Ŀ¼���£���ӡ�ɾ���������������ͻ���á�
void FileSystemWatcher::directoryUpdated(const QString &path)
{
	qDebug() << QString("begin  Directory updated: %1").arg(path) << clock();

	// �Ƚ����µ����ݺͱ���������ҳ�����(�仯)
	QStringList currEntryList = m_currentContentsMap[path];
	const QDir dir(path);

	QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

	QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
	QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);

	// ������ļ�
	QSet<QString> newFiles = newDirSet - currentDirSet;
	QStringList newFile = newFiles.toList();

	// �ļ��ѱ��Ƴ�
	QSet<QString> deletedFiles = currentDirSet - newDirSet;
	QStringList deleteFile = deletedFiles.toList();

	// ���µ�ǰ����
	m_currentContentsMap[path] = newEntryList;

	if (!newFile.isEmpty() && !deleteFile.isEmpty())
	{
		// �ļ�/Ŀ¼������
		if ((newFile.count() == 1) && (deleteFile.count() == 1))
		{
			qDebug() << QString("File Renamed from %1 to %2").arg(deleteFile.first()).arg(newFile.first());
		}
	}
	else
	{
		// ������ļ�/Ŀ¼��Dir
		if (!newFile.isEmpty())
		{
			qDebug() << "New Files/Dirs added: " << newFile;

			foreach(QString file, newFile)
			{
				// �������ÿ�����ļ�....
			}
		}

		// ��Dir��ɾ���ļ�/Ŀ¼
		if (!deleteFile.isEmpty())
		{
			qDebug() << "Files/Dirs deleted: " << deleteFile;

			foreach(QString file, deleteFile)
			{
				// �������ÿ����ɾ�����ļ�....
			}
		}
	}

	qDebug() << QString("end  Directory updated: %1").arg(path) << clock();
}

// �ļ��޸�ʱ����
void FileSystemWatcher::fileUpdated(const QString &path)
{
	QFileInfo file(path);
	QString strPath = file.absolutePath();
	QString strName = file.fileName();

	qDebug() << QString("The file %1 at path %2 is updated").arg(strName).arg(strPath);
}
