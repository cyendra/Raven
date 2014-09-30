#pragma once
#include "std.h"
#include "Parser.h"
namespace RavenInternal {
	class Interpreter {
	public:
		void Compile();
		void Run();
	private:
	};
}
class Raven {
public:
	Raven();
	~Raven();
	static std::shared_ptr<RavenInternal::Interpreter> Interpreter();
};

