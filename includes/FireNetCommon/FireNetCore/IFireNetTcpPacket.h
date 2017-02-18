// Copyright (C) 2014-2017 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/FireNET/blob/master/LICENSE

#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

enum class EFireNetTcpPacketType : int
{
	Empty,
	Query,
	Result,
	Error,
	ServerMessage,
};

enum class EFireNetTcpPacketQuery : int
{
	Login,
	Register,
	CreateProfile,
	GetProfile,
	GetShop,
	BuyItem,
	RemoveItem,
	SendInvite,
	DeclineInvite,
	AcceptInvite,
	RemoveFriend,
	GetServer,
	SendChatMsg,
	// Remote only
	AdminLogin,
	AdminCommand,
	RegisterServer,
	UpdateServer,
	UpdateProfile,
};

enum class EFireNetTcpPacketResult : int
{
	LoginComplete,
	LoginCompleteWithProfile,
	RegisterComplete,
	ProfileCreationComplete,
	GetProfileComplete,
	GetShopComplete,
	BuyItemComplete,
	RemoveItemComplete,
	SendInviteComplete,
	DeclineInviteComplete,
	AcceptInviteComplete,
	RemoveFriendComplete,
	SendChatMsgComplete,
	GetServerComplete,
	// Remote only	
	AdminLoginComplete,
	AdminCommandComplete,
	RegisterServerComplete,
	UpdateServerComplete,
	UpdateProfileComplete,
};

enum class EFireNetTcpPacketError : int
{
	LoginFail,
	RegisterFail,
	ProfileCreationFail,
	GetProfileFail,
	GetShopFail,
	BuyItemFail,
	RemoveItemFail,
	SendInviteFail,
	DeclineInviteFail,
	AcceptInviteFail,
	RemoveFriendFail,
	SendChatMsgFail,
	GetServerFail,
	// Remote only
	AdminLoginFail,
	AdminCommandFail,
	RegisterServerFail,
	UpdateServerFail,
	UpdateProfileFail,
};

// Only server to client
enum class EFireNetTcpPacketSMessage : int
{
	GlobalChatMsg,
	PrivateChatMsg,
	ClanChatMsg,
	ServerMessage,
	ServerCommand,
};

class IFireNetTcpPacket
{
public:
	virtual void                       WriteQuery(EFireNetTcpPacketQuery query) { WriteInt(static_cast<int>(query)); }
	virtual void                       WriteResult(EFireNetTcpPacketResult result) { WriteInt(static_cast<int>(result)); }
	virtual void                       WriteError(EFireNetTcpPacketError error) { WriteInt(static_cast<int>(error)); }
	virtual void                       WriteServerMessage(EFireNetTcpPacketSMessage msg) { WriteInt(static_cast<int>(msg)); }
public:
	virtual EFireNetTcpPacketQuery     ReadQuery() { return (EFireNetTcpPacketQuery)ReadInt(); }
	virtual EFireNetTcpPacketResult    ReadResult() { return (EFireNetTcpPacketResult)ReadInt(); }
	virtual EFireNetTcpPacketError     ReadError() { return (EFireNetTcpPacketError)ReadInt(); }
	virtual EFireNetTcpPacketSMessage  ReadSMessage() { return (EFireNetTcpPacketSMessage)ReadInt(); }
public:
	virtual void                       WriteString(const std::string &value) = 0;
	virtual void                       WriteInt(int value) = 0;
	virtual void                       WriteBool(bool value) = 0;
	virtual void                       WriteFloat(float value) = 0;
	virtual void                       WriteDouble(double value) = 0;
public:
	virtual const char*                ReadString() = 0;
	virtual int                        ReadInt() = 0;
	virtual bool                       ReadBool() = 0;
	virtual float                      ReadFloat() = 0;
	virtual double                     ReadDouble() = 0;
public: 
	virtual const char*                toString() = 0;
	virtual std::size_t                getLength() { return strlen(m_Data.c_str()); }
public:
	EFireNetTcpPacketType              getType() { return m_Type; }
protected:
	void                               WritePacketType(EFireNetTcpPacketType type) { WriteInt(static_cast<int>(type)); }
	void                               WriteHeader() { WriteString(m_Header); }
	void                               WriteFooter() { m_Data = m_Data + m_Footer; };
protected:
	virtual void                       GenerateSession() = 0;
	virtual void                       ReadPacket() = 0;
protected:
	std::vector<std::string>           Split(const std::string &s, char separator)
	{
		std::stringstream ss;
		ss.str(s);
		std::string item;
		std::vector<std::string> m_vector;

		while (std::getline(ss, item, separator))
			m_vector.push_back(item);

		return m_vector;
	}
protected:
	std::string                        m_Data;
	char                               m_Separator;
	std::string                        m_Header;
	std::string                        m_Footer;

	std::vector<std::string>           m_Packet;
	EFireNetTcpPacketType              m_Type;

	// Only for reading
	bool                               bInitFromData;
	bool                               bIsGoodPacket;
	int                                m_LastIndex;
}; 