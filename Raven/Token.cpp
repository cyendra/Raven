#include "Token.h"

namespace RavenInternal {

	/*************************************************
	Token
	*************************************************/

	Token::~Token() { }

	Token::Token() : _type(Tag::UNKOWN), _text("Null") { }

	Token::Token(Tag type) : _type(type), _text("Null") { }

	Token::Token(Tag type, std::string text) : _type(type), _text(text) { }

	Token::Token(std::string text) : _type(Tag::UNKOWN), _text(text) { }

	bool Token::IsType(Tag type) {
		return type == _type;
	}

	void Token::SetType(Tag type) {
		_type = type;
	}

	Token::Tag Token::GetType(){
		return _type;
	}

	void Token::SetText(std::string text) {
		_text = text;
	}

	std::string Token::GetText() {
		return _text;
	}

	int Token::GetInteger() {
		return 0;
	}

	double Token::GetReal() {
		return 0.0;
	}

	bool Token::GetBoolean() {
		return false;
	}

	std::string Token::GetString() {
		return "Null";
	}

	/*************************************************
	IntegerToken
	*************************************************/

	IntegerToken::~IntegerToken() { }

	IntegerToken::IntegerToken() : Token(Tag::INTEGER), _value(0) { }

	IntegerToken::IntegerToken(int value) : Token(Tag::INTEGER), _value(value) { }

	IntegerToken::IntegerToken(int value, std::string text) : Token(Tag::INTEGER, text), _value(value) { }

	IntegerToken::IntegerToken(std::string text) : Token(Tag::INTEGER, text) {
		std::stringstream buf(text);
		buf >> _value;
	}

	int IntegerToken::GetInteger() {
		return _value;
	}

	double IntegerToken::GetReal() {
		return static_cast<double>(_value);
	}

	bool IntegerToken::GetBoolean() {
		return _value != 0;
	}

	std::string IntegerToken::GetString() {
		std::stringstream buf;
		std::string str;
		buf << _value;
		buf >> str;
		return str;
	}

	/*************************************************
	RealToken
	*************************************************/

	RealToken::~RealToken() { }

	RealToken::RealToken() : Token(Tag::REAL), _value(0.0) { }

	RealToken::RealToken(double value) : Token(Tag::REAL), _value(value) { }

	RealToken::RealToken(double value, std::string text) : Token(Tag::REAL, text), _value(value) { }

	RealToken::RealToken(std::string text) : Token(Tag::REAL, text), _value(0.0) { }

	int RealToken::GetInteger() {
		return static_cast<int>(_value);
	}

	double RealToken::GetReal() {
		return _value;
	}

	bool RealToken::GetBoolean() {
		return _value != 0.0;
	}

	std::string RealToken::GetString(){
		std::stringstream buf;
		std::string str;
		buf << _value;
		buf >> str;
		return str;
	}

	/*************************************************
	BooleanToken
	*************************************************/

	BooleanToken::~BooleanToken() { }

	BooleanToken::BooleanToken() : Token(Tag::BOOLEAN), _value(0.0) { }

	BooleanToken::BooleanToken(bool value) : Token(Tag::BOOLEAN), _value(value) { }

	BooleanToken::BooleanToken(bool value, std::string text) : Token(Tag::BOOLEAN, text), _value(value) { }

	BooleanToken::BooleanToken(std::string text) : Token(Tag::BOOLEAN, text), _value(0.0) { }

	int BooleanToken::GetInteger() {
		return static_cast<int>(_value);
	}

	double BooleanToken::GetReal() {
		return static_cast<double>(_value);
	}

	bool BooleanToken::GetBoolean() {
		return _value;
	}

	std::string BooleanToken::GetString(){
		if (_value) return "true";
		else return "false";
	}

	/*************************************************
	StringToken
	*************************************************/

	StringToken::~StringToken() { }

	StringToken::StringToken() : Token(Tag::BOOLEAN), _value("") { }

	StringToken::StringToken(std::string value, std::string text) : Token(Tag::BOOLEAN, text), _value(value) { }

	StringToken::StringToken(std::string text) : Token(Tag::BOOLEAN, text) {
		int size = text.length();
		_value = text.substr(1, size - 2);
	}

	int StringToken::GetInteger() {
		int res = 0;
		std::stringstream buf(_value);
		buf >> res;
		return res;
	}

	double StringToken::GetReal() {
		double res = 0.0;
		std::stringstream buf(_value);
		buf >> res;
		return res;
	}

	bool StringToken::GetBoolean() {
		return _value != "";
	}

	std::string StringToken::GetString(){
		return _value;
	}

	/*************************************************
	WordToken
	*************************************************/

	WordToken::WordToken() : Token() { }

	WordToken::WordToken(Tag type, std::string text) : Token(type, text) { }

	WordToken::~WordToken() {}

	std::shared_ptr<Token> WordToken::GetWord(std::string word) {
		if (word == "var") {
			return VarWord();
		}
		else if (word == "if") {
			return IfWord();
		}
		else if (word == "else") {
			return ElseWord();
		}
		else if (word == "while") {
			return WhileWord();
		}
		else if (word == "do") {
			return DoWord();
		}
		else if (word == "begin") {
			return BeginWord();
		}
		else if (word == "end") {
			return EndWord();
		}
		else if (word == "break") {
			return BreakWord();
		}
		else if (word == "continue") {
			return ContinueWord();
		}
		else if (word == "and") {
			return AndWord();
		}
		else if (word == "or") {
			return OrWord();
		}
		else if (word == "not") {
			return NotWord();
		}
		else {
			return IdentifierWord(word);
		}
	}

	std::shared_ptr<Token> WordToken::GetWord(char word){
		switch (word) {
		case '+':
			return AddWord();
		case '-':
			return SubWord();
		case '*':
			return MulWord();
		case '/':
			return DivWord();
		case '%':
			return ModWord();
		case '=':
			return EqWord();
		case '>':
			return GtWord();
		case '<':
			return LtWord();
		case '.':
			return DotWord();
		case '(':
			return LpWord();
		case ')':
			return RpWord();
		case '{':
			return LcWord();
		case '}':
			return RcWord();
		default:
			return UnkownWord(word);
		}
	}

	std::shared_ptr<Token> WordToken::VarWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::VAR, "var"));
	}

	std::shared_ptr<Token> WordToken::IfWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::IF, "if"));
	}

	std::shared_ptr<Token> WordToken::ThenWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::THEN, "then"));
	}

	std::shared_ptr<Token> WordToken::ElseWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::ELSE, "else"));
	}

	std::shared_ptr<Token> WordToken::WhileWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::WHILE, "while"));
	}

	std::shared_ptr<Token> WordToken::DoWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::DO, "do"));
	}

	std::shared_ptr<Token> WordToken::BeginWord(){
		return std::shared_ptr<Token>(new WordToken(Tag::BEGIN, "begin"));
	}

	std::shared_ptr<Token> WordToken::EndWord(){ 
		return std::shared_ptr<Token>(new WordToken(Tag::END, "end"));
	}

	std::shared_ptr<Token> WordToken::BreakWord(){
		return std::shared_ptr<Token>(new WordToken(Tag::BREAK, "break"));
	}

	std::shared_ptr<Token> WordToken::ContinueWord(){
		return std::shared_ptr<Token>(new WordToken(Tag::CONTINUE,"continue"));
	}

	std::shared_ptr<Token> WordToken::AndWord(){ 
		return std::shared_ptr<Token>(new WordToken(Tag::AND,"and"));
	}

	std::shared_ptr<Token> WordToken::OrWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::OR, "or"));
	}

	std::shared_ptr<Token> WordToken::NotWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::NOT, "not"));
	}

	std::shared_ptr<Token> WordToken::AddWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::ADD, "+"));
	}

	std::shared_ptr<Token> WordToken::SubWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::SUB, "-"));
	}

	std::shared_ptr<Token> WordToken::MulWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::MUL, "*"));
	}

	std::shared_ptr<Token> WordToken::DivWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::DIV, "/"));
	}

	std::shared_ptr<Token> WordToken::ModWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::MOD, "%"));
	}

	std::shared_ptr<Token> WordToken::AssignWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::ASSIGN, ":="));
	}

	std::shared_ptr<Token> WordToken::EqWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::EQ, "="));
	}

	std::shared_ptr<Token> WordToken::GtWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::GT, ">"));
	}

	std::shared_ptr<Token> WordToken::LtWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::LT, "<"));
	}

	std::shared_ptr<Token> WordToken::GeWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::GE, ">="));
	}

	std::shared_ptr<Token> WordToken::LeWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::LE, "<="));
	}

	std::shared_ptr<Token> WordToken::NeWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::NE, "<>"));
	}

	std::shared_ptr<Token> WordToken::LpWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::LP, "("));
	}

	std::shared_ptr<Token> WordToken::RpWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::RP, ")"));
	}

	std::shared_ptr<Token> WordToken::LcWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::LC, "{"));
	}

	std::shared_ptr<Token> WordToken::RcWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::RC, "}"));
	}

	std::shared_ptr<Token> WordToken::IdentifierWord(std::string word) {
		return std::shared_ptr<Token>(new WordToken(Tag::IDENTIFIER, word));
	}

	std::shared_ptr<Token> WordToken::SemWord() { 
		return std::shared_ptr<Token>(new WordToken(Tag::SEM, ";"));
	}

	std::shared_ptr<Token> WordToken::EofWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::END_OF_FILE, "EOF"));
	}

	std::shared_ptr<Token> WordToken::DotWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::DOT, "."));
	}

	std::shared_ptr<Token> WordToken::CommaWord() {
		return std::shared_ptr<Token>(new WordToken(Tag::COMMA, ","));
	}

	std::shared_ptr<Token> WordToken::UnkownWord(char chr) { 
		std::string text;
		text.push_back(chr);
		return std::shared_ptr<Token>(new WordToken(Tag::UNKOWN, text)); 
	}

}
