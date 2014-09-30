#include "Raven.h"

namespace RavenInternal {
	
	void Interpreter::Compile() {

	
	}

	void Interpreter::Run() {
		RavenInternal::Parser parser;
		for (;;) {
			auto stmt = parser.GetStmt();
			auto res = stmt->Eval(parser.GetEnv());
			std::cout << ">>> " << res->GetString() << std::endl;
		}
	}
}
Raven::Raven()
{
}


Raven::~Raven()
{
}

std::shared_ptr<RavenInternal::Interpreter> Raven::Interpreter() {
	return std::shared_ptr<RavenInternal::Interpreter>(new RavenInternal::Interpreter());
}
