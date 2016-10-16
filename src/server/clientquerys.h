// Copyright � 2016 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: http://opensource.org/licenses/MIT

#ifndef CLIENTQUERYS_H
#define CLIENTQUERYS_H

#include <QObject>
#include <QDebug>
#include <QSslSocket>
#include "redisconnector.h"
#include <QXmlStreamReader>
#include <QFile>
#include "global.h"

struct SShopItem
{
	QString name;
	QString icon;
	QString description;
	int cost;
	int minLnl;
};

class ClientQuerys : public QObject
{
    Q_OBJECT
public:
    explicit ClientQuerys(QObject *parent = 0);

public:
	void SetSocket(QSslSocket* socket) { this->m_socket = socket; }
    // Auth system
    void onLogin(QByteArray &bytes);
    void onRegister(QByteArray &bytes);
    // Profile querys
    void onCreateProfile(QByteArray &bytes);
    void onGetProfile();
    // Shop querys
    void onGetShopItems();
    void onBuyItem(QByteArray &bytes);
	void onRemoveItem(QByteArray &bytes);
    // Friend system
    void onAddFriend(QByteArray &bytes);
    void onRemoveFriend(QByteArray &bytes);
	// Chat system
	void onChatMessage(QByteArray &bytes);
	// Invite system
	void onInvite(QByteArray &bytes);
	void onDeclineInvite(QByteArray &bytes);
	// Matchmaking system
	void onGetGameServer(QByteArray &bytes);
	// Game server functionality
	void onGameServerRegister(QByteArray &bytes);
	void onGameServerUpdateInfo(QByteArray &bytes);
	void onGameServerGetOnlineProfile(QByteArray &bytes);
	void onGameServerUpdateOnlineProfile(QByteArray &bytes);

private:
	QXmlStreamAttributes GetAttributesFromArray(QByteArray &bytes);

    bool UpdateProfile(QSslSocket* socket, SProfile* profile);
	QString ProfileToString(SProfile* profile);
	SProfile* GetProfileFromString(QString &stringProfile);
	void AcceptProfileToGlobalList(QSslSocket* socket, SProfile* profile, int status);
	QSslSocket* GetSocketByUid(int uid);
	int GetUidBySocket(QSslSocket* socket);
	SShopItem GetShopItemByName(QString name);
	bool CheckAttributeInRow(QString source, QString tag, QString attribute, QString checkAttribute);
	QString RemoveElementFromRow(QString source, QString element);	
private:
	QSslSocket* m_socket;
	SProfile* clientProfile;
	int clientStatus;
	int startMoney;
};



#endif // CLIENTQUERYS_H
