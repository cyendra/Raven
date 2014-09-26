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
#include "Environment.h"

namespace RavenInternal {

	/***************************************************************************
	Parser
	***************************************************************************/

	class Parser {
	public:
		Parser();
		~Parser();
		std::shared_ptr<Stmt> GetStmt();
		std::shared_ptr<Expr> GetExpr();
	private:
		Lexer lex; // 词法分析器，按理说应该可以动态指定词法分析器，这里设成了静态指定，以后可以改
		Environment env; // 符号表，可以动态搞，同样暂时设为静态

		std::shared_ptr<Token> Peek(int d = 0); // 看看第d个Token
		bool Look(Token::Tag type); // 判断下个Token是不是type类型
		void Match(Token::Tag type); // 吃掉类型为type的Token，吃不着则报错
		void Move(); // 无条件移动一步
		void Error(std::string msg); // 错误
		void Error(std::shared_ptr<Token> tok, std::string msg); // 带词法单元的错误

		std::shared_ptr<Stmt> stmt(); // 吃掉一条语句
		std::shared_ptr<Stmt> block(); // 吃掉一个代码块
		std::shared_ptr<Stmt> stmts(); // 吃掉好多个语句
		std::shared_ptr<Stmt> assign(); // 吃掉一个赋值语句
		std::shared_ptr<Stmt> decls(); // 吃掉变量定义语句
		
		std::shared_ptr<Expr> boolean();
		std::shared_ptr<Expr> join(); 
		std::shared_ptr<Expr> equality();
		std::shared_ptr<Expr> rel();
		std::shared_ptr<Expr> expr();
		std::shared_ptr<Expr> term();
		std::shared_ptr<Expr> unary();
		std::shared_ptr<Expr> factor();

	};

}