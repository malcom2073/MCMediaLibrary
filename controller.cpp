#include "controller.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "MediaStatusMessage.pb.h"
#include "Playlist.pb.h"
#include "MediaFile.pb.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
	m_ipc = new MCIPC("MCMediaLibrary",this);
	connect(m_ipc,SIGNAL(si_publishMessage(QString,QByteArray)),this,SLOT(publishMessage(QString,QByteArray)));
	m_ipc->connectToHost("127.0.0.1",12345);
	connect(m_ipc,SIGNAL(si_connected()),this,SLOT(ipcConnected()));
	connect(m_ipc,SIGNAL(si_ptpMessageReceived(QString,QString,QByteArray)),this,SLOT(ptpMessageReceived(QString,QString,QByteArray)));
	MCMediaLibrary::Status statusmsg;
	statusmsg.set_status("test");
	statusmsg.set_numentries(23);
	//MCMediaLibrary::MediaFile file;

	//statusmsg.
}
void Controller::ptpMessageReceived(QString target,QString sender,QByteArray payload)
{
	qDebug() << "Got message from:" << target << "for" << sender;
	qDebug() << payload;
}

void Controller::ipcConnected()
{
	MediaScanner *scanner = new MediaScanner(this);
	MCMediaLibrary::Playlist playlist;
	QJsonArray medialist;
	for (QMap<QString,MediaMeta>::const_iterator i = scanner->m_metaList.cbegin();i!=scanner->m_metaList.cend();i++)
	{
		medialist.append(serializeMediaObject(i.key(),i.value()));
	}
	QJsonDocument doc(medialist);
	QByteArray jsonstring = doc.toJson();
	m_ipc->publishMessage("MediaList",jsonstring);

}

QJsonObject Controller::serializeMediaObject(QString path, MediaMeta metadata)
{
	QJsonObject retval;
	retval.insert("path",path);
	retval.insert("title",metadata.title);
	retval.insert("album",metadata.album);
	retval.insert("artist",metadata.artist);
	return retval;
}

void Controller::publishMessage(QString name,QByteArray data)
{

}
