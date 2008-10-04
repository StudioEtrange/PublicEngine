/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef BASEPACKETHANDLER_H_
#define BASEPACKETHANDLER_H_

#include "../../../system/lang.h"

#include "../../log/Logger.h"

#include "../ServiceClient.h"
#include "../ServiceMessageHandlerThread.h"

#include "BaseClient.h"

#include "BaseMessage.h"

namespace engine {
  namespace service {
    namespace proto {

	class BasePacketHandler : public Logger {
		MessageQueue* messageQueue;
	
	public:
		BasePacketHandler();	
		BasePacketHandler(const string& s, MessageQueue* queue);
	
		void handlePacket(BaseClient* client, Packet* pack);
	
		void doSessionStart(BaseClient* client, Packet* pack);
		void doSessionResponse(BaseClient* client, Packet* pack);

		void doDisconnect(BaseClient* client, Packet* pack);
		void doNetStatusResponse(BaseClient* client, Packet* pack);
		void doOutOfOrder(BaseClient* client, Packet* pack);
		void doAcknowledge(BaseClient* client, Packet* pack);
	
		void processBufferedPackets(BaseClient* client);
		
		void handleMultiPacket(BaseClient* client, Packet* pack);
		void handleDataChannelPacket(BaseClient* client, Packet* pack);
		void handleDataChannelMultiPacket(BaseClient* client, Packet* pack, sys::uint16 size);
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;

#endif /*BASEPACKETHANDLER_H_*/

