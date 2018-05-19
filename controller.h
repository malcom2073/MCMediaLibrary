#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include "mediascanner.h"

#include "mcipc.h"

class Controller : public QObject
{
	Q_OBJECT
public:
	explicit Controller(QObject *parent = 0);
private:
	MCIPC *m_ipc;
	QJsonObject serializeMediaObject(QString path, MediaMeta metadata);
signals:
private slots:
	void publishMessage(QString name,QByteArray data);
	void ipcConnected();
public slots:
};

#endif // CONTROLLER_H
