#ifndef DEBUG_STREAM_H
#define DEBUG_STREAM_H

#include <string>

/////////////////////// forward declaration ///////////////////////
class Manipulator; 
class ManipPrecision;
class ManipNewline;
class DebugStream; 
DebugStream& endl(DebugStream& stream); // non-OOD manip


/////////////////////// Globals ///////////////////////
typedef ManipPrecision setprecision;
extern DebugStream dout;  // global out put stream
extern ManipNewline newline; // global variable


/////////////////////// Debug Stream ///////////////////////
class DebugStream {
public:
	// Overload the << operator for int, double and string
	DebugStream& operator<<(const std::string& message);
	
	DebugStream& operator<<(int num);
	
	DebugStream& operator<<(double v);
	
	// Handle manipulators like std::endl without using OOD
	DebugStream& operator<<(DebugStream& (*manip)(DebugStream&));	
	
	// Handle manipulators like std:setprecision --> must use OOD
	DebugStream& operator<<(const Manipulator& manip);
	
	// Flush function to flush the output buffer
	void flush();
	
	// Setter
	void set_precision(unsigned int precision);
	
private:
	unsigned int _precision = 6;
};


/////////////////////// Abstract Manipulator ///////////////////////
class Manipulator {
public:
	virtual void apply(DebugStream& stream) const =0;
};

/////////////////////// Concrete Manipulator ///////////////////////
class ManipPrecision : public Manipulator {
public:
	ManipPrecision(unsigned int prec):_precision(prec){}
	void apply(DebugStream& stream) const override {
		stream.set_precision(this->_precision);
	}
private:
	unsigned int _precision = 6;
};

class ManipNewline : public Manipulator {
public:
	void apply(DebugStream& stream) const override {
		const char* newline = "\n";
		stream << newline;
		stream.flush();
	}
};




#endif