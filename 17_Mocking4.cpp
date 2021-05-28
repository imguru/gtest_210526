
#include <stdio.h>

// Dependency Injection
//  1) 인터페이스 / 추상 클래스
//  2) Template - Policy Based Design(단위 전략)

struct Packet {};
class PacketStream {
public:
	virtual ~PacketStream() {}

	virtual void AppendPacket(Packet* new_packet) = 0;
	virtual const Packet* GetPacket(size_t packet_number) const = 0;
};

class ConcreatePacketStream : public PacketStream {
public:
	void AppendPacket(Packet* new_packet) override {
		printf("ConcreatePacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const override {
		printf("ConcreatePacketStream::GetPacket\n");
		return nullptr;
	}
};


class PacketReader {
public:
	void ReadPacket(PacketStream* stream, size_t packet_number) {
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_number);
	}
};

int main() {
	ConcreatePacketStream stream;
	PacketReader reader;
	
	reader.ReadPacket(&stream, 42);
}






