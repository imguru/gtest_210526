
#include <stdio.h>

// Dependency Injection
//  2) Template - Policy Based Design(단위 전략)
//    => 암묵적인 인터페이스
struct Packet {};
class ConcreatePacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {
		printf("ConcreatePacketStream::GetPacket\n");
		return nullptr;
	}
};

class PacketReader {
public:
	template <typename PacketStream>
	void ReadPacket(PacketStream* stream, size_t packet_number) {
		stream->AppendPacket(nullptr);
		// stream->GetPacket(packet_number);
	}
};

#include <gmock/gmock.h>

class MockPacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
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




