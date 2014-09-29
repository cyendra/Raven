#include "TestTool.h"
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"

using namespace Debug::TestTool;

int main() {
	
	RavenInternal::Parser parser;
	for (;;) {
		auto stmt = parser.GetStmt();
		auto res = stmt->Eval(parser.GetEnv());
		std::cout << ">>> "<< res->GetString() << std::endl;
	}

	system("pause");
	return 0;
}