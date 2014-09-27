#include "Parser.h"

namespace RavenInternal {

	/***************************************************************************
	Parser
	***************************************************************************/

	Parser::Parser() { }

	Parser::~Parser() { }

	std::shared_ptr<Stmt> Parser::GetStmt() {
		return stmt();
	}

	std::shared_ptr<Expr> Parser::GetExpr() {
		return boolean();
	}

	// 预读 d 个Token
	std::shared_ptr<Token> Parser::Peek(int d) {
		return lex.Peek(d);
	}
	
	// 判断下个Token是不是type类型
	bool Parser::Look(Token::Tag type) {
		return Peek()->IsType(type);
	}

	// 吃掉类型为type的Token，吃不着则报错
	void Parser::Match(Token::Tag type) {
		auto tok = lex.Read();
		if (tok->IsType(type) == false) {
			Error(tok, "syntax error");
		}
	}
	
	// 无条件移动一步
	void Parser::Move() {
		lex.Read();
	}

	// 错误
	void Parser::Error(std::string msg) {
		std::cerr << "Error " << msg << std::endl;
		exit(1);
	}
	
	// 带词法单元的错误
	void Parser::Error(std::shared_ptr<Token> tok, std::string msg) {
		std::cerr << "Error near line " << tok->GetLineNumber() << " " << msg << std::endl;
		exit(1);
	}

	// 吃掉一条语句
	std::shared_ptr<Stmt> Parser::stmt() {
		auto look = Peek();
		std::shared_ptr<Expr> x;
		std::shared_ptr<Stmt> x, s1, s2;
		switch (look->GetType()) {
		case Token::SEM:
			Match(Token::SEM);
			return std::shared_ptr<Empty>(new Empty());
		case Token::IF:
			Match(Token::IF);
			x = boolean();
			Match(Token::THEN);
			s1 = stmt();
			if (Peek()->IsType(Token::ELSE) == false) {
				Match(Token::SEM);
				return std::shared_ptr<If>(new If(x, s1));
			}
			Match(Token::ELSE);
			s2 = stmt();
			return std::shared_ptr<Else>(new Else(x, s1, s2));
		case Token::WHILE:
			Match(Token::WHILE);
			x = boolean();
			Match(Token::DO);
			s1 = stmt();
			return std::shared_ptr<While>(new While(x, s1));
		case Token::BREAK:
			Match(Token::BREAK);
		case Token::BEGIN:
			Match(Token::BEGIN);
		default:
			break;
		}

	}
	
	// 吃掉一个代码块
	std::shared_ptr<Stmt> Parser::block() {
	
	}

	// 吃掉好多个语句
	std::shared_ptr<Stmt> Parser::stmts() {
	
	}
	
	// 吃掉一个赋值语句
	std::shared_ptr<Stmt> Parser::assign() {
	
	}
	
	// 吃掉变量定义语句
	std::shared_ptr<Stmt> Parser::decls() {

	}

	std::shared_ptr<Expr> Parser::boolean() {
		auto x = join();
		while (Look(Token::OR)) {
			auto tok = Peek();
			Move();
			x = std::shared_ptr<Expr>(new Or(tok, x, join()));
		}
		return x;
	}

	std::shared_ptr<Expr> Parser::join() {
		auto x = equality();
		while (Look(Token::AND)) {
			auto tok = Peek();
			Move();
			x = std::shared_ptr<Expr>(new And(tok, x, equality()));
		}
		return x;
	}

	std::shared_ptr<Expr> Parser::equality() {
		auto x = rel();
		while (Look(Token::EQ) || Look(Token::NE)) {
			auto tok = Peek();
			Move();
			x = std::shared_ptr<Expr>(new Rel(tok, x, rel()));
		}
		return x;
	}

	std::shared_ptr<Expr> Parser::rel() {
		auto x = expr();
		if (Look(Token::LT) || Look(Token::LE) || Look(Token::GT) || Look(Token::GE)) {
			auto tok = Peek();
			Move();
			return std::shared_ptr<Expr>(new Rel(tok, x, expr()));
		}
		return x;
	}

	std::shared_ptr<Expr> Parser::expr() {
		auto x = term();
		while (Look(Token::ADD) || Look(Token::SUB)) {
			auto tok = Peek();
			Move();
			x = std::shared_ptr<Expr>(new Arith(tok, x, term()));
		}
		return x;
	}

	std::shared_ptr<Expr> Parser::term() {
		auto x = unary();
		while (Look(Token::MUL) || Look(Token::DIV)) {
			auto tok = Peek();
			Move();
			x = std::shared_ptr<Expr>(new Arith(tok, x, unary()));
		}
		return x;
	}

	std::shared_ptr<Expr> Parser::unary() {
		if (Look(Token::SUB)) {
			Move();
			return std::shared_ptr<Expr>(new Unary(WordToken::MinusWord(), unary()));
		}
		else if (Look(Token::NOT)) {
			auto tok = Peek();
			Move();
			return std::shared_ptr<Expr>(new Not(tok, unary()));
		}
		else return factor();
	}

	std::shared_ptr<Expr> Parser::factor() {
		if (Look(Token::LP)) {
			Move();
			auto x = boolean();
			Match(Token::RP);
			return x;
		}
		else if (Look(Token::INTEGER) || Look(Token::REAL) || (Look(Token::TRUE) || Look(Token::FALSE) || Look(Token::STRING))) {
			auto tok = Peek();
			Move();
			return std::shared_ptr<Expr>(new Constant(tok));
		}
		else if (Look(Token::IDENTIFIER)) {
			auto tok = Peek();
			Move();
			return std::shared_ptr<Expr>(new Id(tok));
		}
		else {
			auto tok = Peek();
			Error(tok, "syntax error");
		}
	}

}