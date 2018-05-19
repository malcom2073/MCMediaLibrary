#ifndef MEDIASCANNER_H
#define MEDIASCANNER_H

#include <QObject>
#include "mediameta.h"
#include <QMap>

class MediaScanner : public QObject
{
	Q_OBJECT
public:
	explicit MediaScanner(QObject *parent = 0);
private:
	MediaMeta gettags(QString mediafile);
	void updateMeta(QString filename);
	void scanFolder(QString foldername);
public:
	//TODO: Make this a database
	//Currently a Path to Meta map.
	QMap<QString,MediaMeta> m_metaList;
signals:
	void scanningDone();
public slots:
};

#endif // MEDIASCANNER_H
