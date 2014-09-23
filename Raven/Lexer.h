/*************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Lexer
*************************************************/

#pragma once

#include "std.h"
#include "Token.h"
#include "Reader.h"
namespace RavenInternal {

	/*************************************************
	Lexer
	*************************************************/

	class Lexer {
	public:
		Lexer();
		Lexer(Reader* lpReader);
		Lexer(std::shared_ptr<Reader> lpReader);
		~Lexer();
		void Init();
		void Init(Reader* lpReader);
		void Init(std::shared_ptr<Reader> lpReader);
		std::shared_ptr<Token> Read();
		std::shared_ptr<Token> Peek(int i);
	private:
		int lineNumber;
		std::string buf;
		int pos;
		char peek;
		bool hasMore;
		std::shared_ptr<Reader> reader;
		std::deque<std::shared_ptr<Token>> queue;
		bool FillQueue(int i = 0);
		void ReadLine();
		void Readch();
		bool Readch(char c);
		std::shared_ptr<Token> Scan();
	};

}