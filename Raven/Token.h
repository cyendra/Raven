/*************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Token
IntegerToken < Token		整型常量
RealToken < Token			实型常量
BooleanToken < Token		布尔型常量
StringToken < Token			字符串型常量
WordToken < Token			保留字工厂
*************************************************/

#pragma once

#include "std.h"

namespace RavenInternal {

	/*************************************************
	IntegerToken
	*************************************************/

	class Token {
	public:
		static 	enum Tag {
			VAR, IF, THEN, ELSE, WHILE, DO, BEGIN, END, BREAK, RETURN, CONTINUE, // 保留字
			TRUE, FALSE, AND, OR, NOT,	// 逻辑运算, True False 似乎可以删掉？
			ADD, SUB, MUL, DIV, MOD, MINUS, // 算数运算
			ASSIGN, EQ, GT, LT, LE, GE, NE, // 比较运算
			INTEGER, REAL, STRING, BOOLEAN, // 四大常量类型
			LP, RP, LC, RC, // ( ) { }
			IDENTIFIER, FUNCTION, // 变量和函数
			SEM, END_OF_FILE, // 分号和文件尾
			DOT, COMMA, // 为点调用预留
			UNKOWN // 未解之谜
		};
		Token();
		Token(Tag type);
		Token(Tag type, std::string text);
		Token(std::string text);
		virtual bool IsType(Tag type);
		virtual void SetType(Tag type);
		virtual Tag GetType();
		virtual void SetText(std::string text);
		virtual std::string GetText();
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
		virtual ~Token();
	private:
		Tag _type;
		std::string _text;
	};

	/*************************************************
	IntegerToken
	*************************************************/
	
	class IntegerToken : public Token {
	public:
		IntegerToken();
		IntegerToken(int value);
		IntegerToken(int value, std::string text);
		IntegerToken(std::string text);
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
		virtual ~IntegerToken();
	private:
		int _value;
	};
	
	/*************************************************
	RealToken
	*************************************************/

	class RealToken : public Token {
	public:
		RealToken();
		RealToken(double value);
		RealToken(double value, std::string text);
		RealToken(std::string text);
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
		virtual ~RealToken();
	private:
		double _value;
	};

	/*************************************************
	BooleanToken
	*************************************************/

	class BooleanToken : public Token {
	public:
		BooleanToken();
		BooleanToken(bool value);
		BooleanToken(bool value, std::string text);
		BooleanToken(std::string text);
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
		virtual ~BooleanToken();
	private:
		bool _value;
	};

	/*************************************************
	StringToken
	*************************************************/

	class StringToken : public Token {
	public:
		StringToken();
		StringToken(std::string value, std::string text);
		StringToken(std::string text);
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
		virtual ~StringToken();
	private:
		std::string _value;
	};

	/*************************************************
	WordToken
	*************************************************/

	class WordToken : public Token {
	public:
		WordToken();
		WordToken(Tag type, std::string text);
		virtual ~WordToken();
		static std::shared_ptr<Token> GetWord(std::string word);
		static std::shared_ptr<Token> GetWord(char word);
		static std::shared_ptr<Token> VarWord();
		static std::shared_ptr<Token> IfWord();
		static std::shared_ptr<Token> ThenWord();
		static std::shared_ptr<Token> ElseWord();
		static std::shared_ptr<Token> WhileWord();
		static std::shared_ptr<Token> DoWord();
		static std::shared_ptr<Token> BeginWord();
		static std::shared_ptr<Token> EndWord();
		static std::shared_ptr<Token> BreakWord();
		static std::shared_ptr<Token> ContinueWord();
		static std::shared_ptr<Token> AndWord();
		static std::shared_ptr<Token> OrWord();
		static std::shared_ptr<Token> NotWord();
		static std::shared_ptr<Token> AddWord();
		static std::shared_ptr<Token> SubWord();
		static std::shared_ptr<Token> MulWord();
		static std::shared_ptr<Token> DivWord();
		static std::shared_ptr<Token> ModWord();
		static std::shared_ptr<Token> MinusWord();
		static std::shared_ptr<Token> AssignWord();
		static std::shared_ptr<Token> EqWord();
		static std::shared_ptr<Token> GtWord();
		static std::shared_ptr<Token> LtWord();
		static std::shared_ptr<Token> GeWord();
		static std::shared_ptr<Token> LeWord();
		static std::shared_ptr<Token> NeWord();
		static std::shared_ptr<Token> LpWord();
		static std::shared_ptr<Token> RpWord();
		static std::shared_ptr<Token> LcWord();
		static std::shared_ptr<Token> RcWord();
		static std::shared_ptr<Token> IdentifierWord(std::string word);
		static std::shared_ptr<Token> SemWord();
		static std::shared_ptr<Token> EofWord();
		static std::shared_ptr<Token> DotWord();
		static std::shared_ptr<Token> CommaWord();
		static std::shared_ptr<Token> UnkownWord(char chr);
	};

}
