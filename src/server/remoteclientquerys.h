// Copyright � 2016 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: http://opensource.org/licenses/MIT

#ifndef REMOTECLIENTQUERYS_H
#define REMOTECLIENTQUERYS_H

#include <QObject>
#include <QSslSocket>

#include "global.h"
#include "netpacket.h"


class RemoteClientQuerys : public QObject
{
    Q_OBJECT
public:
    explicit RemoteClientQuerys(QObject *parent = 0);
	~RemoteClientQuerys();
	void SetSocket(QSslSocket* socket) { this->m_socket = socket; }
	void SetClient(SRemoteClient* client);
public:
	// Administration functional
	void onAdminLogining(NetPacket &packet);
	void onConsoleCommandRecived(NetPacket &packet);
	// Game server functionality
	void onGameServerRegister(NetPacket &packet);
	void onGameServerUpdateInfo(NetPacket &packet);

	void onGameServerGetOnlineProfile(NetPacket &packet);
	void onGameServerUpdateOnlineProfile(NetPacket &packet);
private:
	bool CheckInTrustedList(QString name, QString ip, int port);
private:
	QSslSocket* m_socket;
	SRemoteClient* m_client;
};

#endif // REMOTECLIENTQUERYS_H