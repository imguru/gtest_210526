
#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR,
};

class DLoggerTarget {
public:
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class FileTarget : public DLoggerTarget {
public:
	void Write(Level level, const std::string& message) override {
		printf("File 기록 - %d[%s]\n", level, message.c_str());
	}
};

class NetworkTarget : public DLoggerTarget {
public:
	void Write(Level level, const std::string& message) override {
		printf("Network 기록 - %d[%s]\n", level, message.c_str());
	}
};


class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* p : targets) {
			p->Write(level, message);
		}
	}
};

int main() {
	DLogger logger;
	FileTarget t1;
	NetworkTarget t2;

	logger.AddTarget(&t1);
	logger.AddTarget(&t2);

	logger.Write(INFO, "test_message1");
	logger.Write(WARN, "test_message2");
}













