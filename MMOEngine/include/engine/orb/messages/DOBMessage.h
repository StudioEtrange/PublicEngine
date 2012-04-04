/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef DOBMESSAGE_H_
#define DOBMESSAGE_H_

#include "system/lang.h"

namespace engine {
  namespace ORB {

	class DOBMessage : public Packet {
	protected:
		class DOBServiceClient* client;

		uint32 sequence;

		Condition replyCondition;

	public:
		enum MessageTypes { REPLYMESSAGE,
							LOOKUPOBJECTMESSAGE, LOOKUPOBJECTBYIDMESSAGE,
							DEPLOYOBJECTMESSAGE, UNDEPLOYOBJECTMESSAGE,
							INVOKEMETHODMESSAGE,
							LOADPERSISTENTOBJECTMESSAGE, UPDATEPERSISTENTOBJECTMESSAGE,
							GETNEXTFREEOBJECTIDMESSAGE };

	public:	
		DOBMessage(uint32 messageType) : Packet(20) {
			insertInt(messageType);
			insertInt(0); // sequence
		}

		DOBMessage(uint32 messageType, uint32 initialBufferSize) : Packet(initialBufferSize) {
			insertInt(messageType);
			insertInt(0); // sequence
		}

		DOBMessage(Packet* packet) : Packet(40) {
			sequence = packet->parseInt();

			insertInt(REPLYMESSAGE); // messageType
			insertInt(sequence); // sequence
		}

		virtual void execute() = 0;

		virtual void handleReply(Packet* response) {
		}

		void signalReply() {
			replyCondition.signal();
		}

		bool waitForReply(uint32 timeout = 10000) {
			Time time;
			time.addMiliTime(timeout);

			return replyCondition.timedWait(&time) == 0;
		}

		DOBServiceClient* getClient() {
			return client;
		}

		uint32 getSequence() {
			return sequence;
		}

		void setClient(DOBServiceClient* cli) {
			client = cli;
		}

		void setSequence(uint32 seq) {
			sequence = seq;
			insertInt(4, seq); // sequence
		}
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*DOBMESSAGE_H_*/