/*************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Reader
*************************************************/
#pragma once

#include "std.h"

namespace RavenInternal {

	/*************************************************
	Reader
	*************************************************/

	class Reader {
	private:
		const static int BUF_SIZE = 1024;
		bool Eof;
		char buf[BUF_SIZE];
	public:
		Reader();
		virtual ~Reader();
		virtual bool HasMore();
		virtual std::string ReadLine();
	};

}