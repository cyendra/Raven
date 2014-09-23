#include "TestTool.h"
#include "Lexer.h"
#include "Token.h"

using namespace Debug::TestTool;

int main() {
	
	RavenInternal::Lexer lex;
	for (;;) {
		auto tok = lex.Read();
		if (tok->IsType(RavenInternal::Token::END_OF_FILE)) break;
		auto str = tok->GetText();
		std::cout << str << std::endl;
	}

	system("pause");
	return 0;
}