
#ifndef DLOGGERTARGET_H
#define DLOGGERTARGET_H
#include <string>

enum Level {
	INFO, WARN, ERROR,
};

class DLoggerTarget {
public:
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

#endif
