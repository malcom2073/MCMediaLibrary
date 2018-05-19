#include "mediascanner.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <QDir>
#include <QStringList>
#include <QDebug>
MediaScanner::MediaScanner(QObject *parent) : QObject(parent)
{
	QString basedir = "E:\\Backup\\Users\\Michael\\Desktop\\Mikes Playlist rock&metal\\";
	QString filename = basedir + "07 Awake and Alive.mp3";
	//qDebug() << "Tag:" << gettags(filename);
	QDir base(basedir);
	foreach (QString filename,base.entryList(QDir::Files | QDir::NoDotAndDotDot))
	{
		updateMeta(base.absoluteFilePath(filename));
//		m_metaList.append(gettags(base.absoluteFilePath(filename)));
	}

	QString scandir = "E:\\music";
	scanFolder(scandir);
	qDebug() << "Done scanning";
	emit scanningDone();
}
void MediaScanner::scanFolder(QString foldername)
{
	QDir base(foldername);
	foreach (QString filename,base.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
	{
		scanFolder(base.absoluteFilePath(filename));
//		m_metaList.append(gettags(base.absoluteFilePath(filename)));
	}

	foreach (QString filename,base.entryList(QDir::Files | QDir::NoDotAndDotDot))
	{
		updateMeta(base.absoluteFilePath(filename));
//		m_metaList.append(gettags(base.absoluteFilePath(filename)));
	}

}

void MediaScanner::updateMeta(QString filename)
{
	qDebug() << "Meta for:" << filename;
	if (m_metaList.contains(filename))
	{
		m_metaList.remove(filename);
	}
	m_metaList.insert(filename,gettags(filename));
}

MediaMeta MediaScanner::gettags(QString mediafile)
{
	MediaMeta retval;
	TagLib::FileRef file(TagLib::FileName(mediafile.toStdString().c_str()));
	if (file.tag())
	{
		TagLib::String artist_string = file.tag()->artist();
		TagLib::String title_string = file.tag()->title();
		TagLib::String album_string = file.tag()->album();
		QString artist = QString::fromLatin1(artist_string.toCString());
		QString title = QString::fromStdString(title_string.toCString());
		QString album = QString::fromStdString(album_string.toCString());
		retval.artist = artist;
		retval.title = title;
		retval.album = album;
	}
	return retval;
}
