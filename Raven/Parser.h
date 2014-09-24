/***************************************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Parser
***************************************************************************/

#pragma once

#include "std.h"
#include "Token.h"
#include "Lexer.h"
#include "Node.h"

namespace RavenInternal {

	/***************************************************************************
	Parser
	***************************************************************************/

	class Parser {
	public:
		Parser();
		virtual ~Parser();
		std::shared_ptr<Stmt> GetStmt();
		std::shared_ptr<Expr> GetExpr();
	private:
		Lexer lex;
		std::shared_ptr<Token> look;
		bool Match(Token::Tag type);
		void Move();
		std::shared_ptr<Stmt> stmt();
	};

}