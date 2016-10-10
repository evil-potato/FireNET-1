// Copyright � 2016 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: http://opensource.org/licenses/MIT

#include "redisconnector.h"
#include "global.h"
#include <QDebug>

RedisConnector::RedisConnector(QObject *parent)
{
	connection = 0; 
    connectStatus = false;
	m_thread = 0;
}

void RedisConnector::run()
{
	if (Connect())
	{
		qInfo() << "Redis connected!";

		m_thread = QThread::currentThread();

		qInfo() << "Redis work on " << m_thread;
	}
	else
	{
        qCritical() << "Failed connect to Redis! Database functions not be work!";
		return;
	}
}

bool RedisConnector::Connect()
{
	qInfo()<< "Init qredisclient...";
    initRedisClient();

	qInfo()<< "Create connection to Redis... ("<< gEnv->redisHost <<")";
    RedisClient::ConnectionConfig config(gEnv->redisHost);
    connection = new RedisClient::Connection(config);
    connection->connect(false);

    connectStatus = connection->isConnected();

    return connection->isConnected();
}

QString RedisConnector::SendSyncQuery(QString command)
{
	RedisClient::Response r;

	if (connectStatus && connection != nullptr)
	{
		r = connection->commandSync(command);
		return r.getValue().toString();
	}
	else
		qCritical() << "Error send sync query to Redis DB";

	return QString();
}

QString RedisConnector::SendSyncQuery(QString command, QString key)
{
	RedisClient::Response r;

	if (connectStatus && connection != nullptr)
	{
		r = connection->commandSync(command, key);
		return r.getValue().toString();
	}
	else
		qCritical() << "Error send sync query to Redis DB";

	return QString();
}

QString RedisConnector::SendSyncQuery(QString command, QString key, QString value)
{
	RedisClient::Response r;

	if (connectStatus && connection != nullptr)
	{
		r = connection->commandSync(command, key, value);
		return r.getValue().toString();
	}
	else
		qCritical() << "Error send sync query to Redis DB";

	return QString();
}

QString RedisConnector::SendSyncQuery(QList<QByteArray>& rawCmd)
{
	RedisClient::Response r;

	if (connectStatus && connection != nullptr)
	{
		r = connection->commandSync(rawCmd);

		if (r.isArray())
			return r.toRawString();

		return r.getValue().toString();
	}
	else
		qCritical() << "Error send sync query to Redis DB";

	return QString();
}

