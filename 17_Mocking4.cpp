
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
		// stream->AppendPacket(nullptr);
		stream->GetPacket(packet_number);
	}
};

//-------
#include <gmock/gmock.h>

class MockPacketStream : public PacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet), (override));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const, override));
};

TEST(PacketReaderTest, ReadPacket) {
	MockPacketStream stream;
	PacketReader reader;

	EXPECT_CALL(stream, AppendPacket);
	EXPECT_CALL(stream, GetPacket);

	reader.ReadPacket(&stream, 42);
}


#if 0
int main() {
	ConcreatePacketStream stream;
	PacketReader reader;
	
	reader.ReadPacket(&stream, 42);
}
#endif






