#include "Reader.h"
#include "Debug.h"
namespace RavenInternal {

	/***************************************************************************
	Reader
	***************************************************************************/

	Reader::Reader() {
		Eof = false;
	}

	Reader::~Reader() { }

	bool Reader::HasMore() {
		return !Eof;
	}
	
	std::string Reader::ReadLine() {
		auto rs = gets_s(buf, 1024);
		if (rs == NULL) {
			Eof = true;
			return "";
		}
		return std::string(buf);
	}

}