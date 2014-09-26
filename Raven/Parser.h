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
		Lexer lex; // �ʷ�������������˵Ӧ�ÿ��Զ�ָ̬���ʷ�����������������˾�ָ̬�����Ժ���Ը�
		Environment env; // ���ű����Զ�̬�㣬ͬ����ʱ��Ϊ��̬

		std::shared_ptr<Token> Peek(int d = 0); // ������d��Token
		bool Look(Token::Tag type); // �ж��¸�Token�ǲ���type����
		void Match(Token::Tag type); // �Ե�����Ϊtype��Token���Բ����򱨴�
		void Move(); // �������ƶ�һ��
		void Error(std::string msg); // ����
		void Error(std::shared_ptr<Token> tok, std::string msg); // ���ʷ���Ԫ�Ĵ���

		std::shared_ptr<Stmt> stmt(); // �Ե�һ�����
		std::shared_ptr<Stmt> block(); // �Ե�һ�������
		std::shared_ptr<Stmt> stmts(); // �Ե��ö�����
		std::shared_ptr<Stmt> assign(); // �Ե�һ����ֵ���
		std::shared_ptr<Stmt> decls(); // �Ե������������
		
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