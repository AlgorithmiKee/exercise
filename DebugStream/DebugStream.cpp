#include <unistd.h>
#include <cstring>
#include <cmath>
#include "DebugStream.h"


using std::round, std::abs;

/////////////////////// Globals ///////////////////////
DebugStream dout;  // global out put stream
ManipNewline newline; // global variable

DebugStream& DebugStream::operator<<(const std::string& message) {
	write(STDOUT_FILENO, message.c_str(), message.size());
	return *this;
}

DebugStream& DebugStream::operator<<(int num) {
	return *this << std::to_string(num);
}

DebugStream& DebugStream::operator<<(double v) {
	int p = round(pow(10.0, double(_precision)));
	v *= p;    
	int const iv = round(v);
	int const ipart = iv / p;
	int const rpart = iv < 0 ? -iv % p: iv % p;
	
	return *this << ipart << "." << rpart;
}

// Handle manipulators like std::endl without using OOD
DebugStream& DebugStream::operator<<(DebugStream& (*manip)(DebugStream&)) {
	return manip(*this);
}

// Handle manipulators like std:setprecision --> must use OOD
DebugStream& DebugStream::operator<<(const Manipulator& manip) {
	manip.apply(*this);
	return *this;
}

// Flush function to flush the output buffer
void DebugStream::flush() {
	fsync(STDOUT_FILENO);
}

// Setter
void DebugStream::set_precision(unsigned int precision){
	_precision = precision;
}
	

/////////////////////// Non OOD Manipulator Functions ///////////////////////
DebugStream& endl(DebugStream& stream) {
	const char* newline = "\n";
	stream << newline;
	stream.flush();
	return stream;
}


