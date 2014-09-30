/***************************************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Token
IntegerToken < Token		整型常量
RealToken < Token			实型常量
BooleanToken < Token		布尔型常量		!貌似这个东西根本解析不出来，已废弃
StringToken < Token			字符串型常量
WordToken < Token			保留字工厂		!定义布尔型常量为保留字
***************************************************************************/

#pragma once

#include "std.h"

namespace RavenInternal {

	/***************************************************************************
	IntegerToken
	***************************************************************************/

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
			SEM, END_OF_FILE, END_OF_LINE, // 分号和文件尾
			DOT, COMMA, // 为点调用预留
			UNKOWN // 未解之谜
		};
		Token();
		Token(Tag type);
		Token(Tag type, std::string text);
		Token(std::string text);
		virtual void SetLineNumber(int line);
		virtual int GetLineNumber();
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
		static std::shared_ptr<Token> GetEOL();
	private:
		Tag _type;
		std::string _text;
		int _lineNumber;
	};

	/***************************************************************************
	IntegerToken
	***************************************************************************/
	
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
		static std::shared_ptr<Token> GetToken(int value, std::string text);
	private:
		int _value;
	};
	
	/***************************************************************************
	RealToken
	***************************************************************************/

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
		static std::shared_ptr<Token> GetToken(double value, std::string text);
	private:
		double _value;
	};

	/***************************************************************************
	BooleanToken
	***************************************************************************/

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
		static std::shared_ptr<Token> GetToken(bool value, std::string text);
	private:
		bool _value;
	};

	/***************************************************************************
	StringToken
	***************************************************************************/

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
		static std::shared_ptr<Token> GetToken(std::string text);
	private:
		std::string _value;
	};

	/***************************************************************************
	WordToken
	***************************************************************************/

	class WordToken : public Token {
	public:
		WordToken();
		WordToken(Tag type, std::string text);
		virtual ~WordToken();

		// 以字符串形式取得关键字
		static std::shared_ptr<Token> GetWord(std::string word);
		
		// 符号取得
		static std::shared_ptr<Token> GetWord(char word);

#pragma region 关键字
		static std::shared_ptr<Token> TrueWord(); // true
		static std::shared_ptr<Token> FalseWord(); // false
		static std::shared_ptr<Token> VarWord(); // var
		static std::shared_ptr<Token> IfWord(); // if
		static std::shared_ptr<Token> ThenWord(); // then
		static std::shared_ptr<Token> ElseWord(); // else
		static std::shared_ptr<Token> WhileWord(); // while
		static std::shared_ptr<Token> DoWord(); // do
		static std::shared_ptr<Token> BeginWord(); // begin
		static std::shared_ptr<Token> EndWord(); // end
		static std::shared_ptr<Token> BreakWord(); // break
		static std::shared_ptr<Token> ContinueWord(); // continue
		static std::shared_ptr<Token> ReturnWord(); // return  
#pragma endregion

#pragma region 逻辑运算符与算数运算符
		static std::shared_ptr<Token> AndWord();
		static std::shared_ptr<Token> OrWord();
		static std::shared_ptr<Token> NotWord();
		static std::shared_ptr<Token> AddWord();
		static std::shared_ptr<Token> SubWord();
		static std::shared_ptr<Token> MulWord();
		static std::shared_ptr<Token> DivWord();
		static std::shared_ptr<Token> ModWord();
		static std::shared_ptr<Token> MinusWord();
#pragma endregion

#pragma region 赋值与比较运算
		static std::shared_ptr<Token> AssignWord();
		static std::shared_ptr<Token> EqWord();
		static std::shared_ptr<Token> GtWord();
		static std::shared_ptr<Token> LtWord();
		static std::shared_ptr<Token> GeWord();
		static std::shared_ptr<Token> LeWord();
		static std::shared_ptr<Token> NeWord();
#pragma endregion


#pragma region 特殊符号们
		static std::shared_ptr<Token> LpWord();
		static std::shared_ptr<Token> RpWord();
		static std::shared_ptr<Token> LcWord();
		static std::shared_ptr<Token> RcWord();
		static std::shared_ptr<Token> SemWord();
		static std::shared_ptr<Token> DotWord();
		static std::shared_ptr<Token> CommaWord();
#pragma endregion

#pragma region 不明觉厉类
		static std::shared_ptr<Token> IdentifierWord(std::string word);
		static std::shared_ptr<Token> EofWord();
		static std::shared_ptr<Token> UnkownWord(char chr);
#pragma endregion

	};

}
