#include "Lexer.h"
#include "Debug.h"
namespace RavenInternal {

	/***************************************************************************
	Lexer
	***************************************************************************/
	
	Lexer::Lexer() {
		Init();
	}

	Lexer::Lexer(Reader* lpReader) {
		Init(lpReader);
	}

	Lexer::Lexer(std::shared_ptr<Reader> lpReader) {
		Init(lpReader);
	}

	Lexer::~Lexer() { }

	void Lexer::Init() {
		Init(new Reader());
	}

	void Lexer::Init(Reader* lpReader) {
		Init(std::shared_ptr<Reader>(lpReader));
	}

	void Lexer::Init(std::shared_ptr<Reader> lpReader) {
		lineNumber = 0;
		hasMore = true;
		reader = lpReader;
	}

	bool Lexer::FillQueue(int i) {
		while (i >= (int)queue.size()) {
			if (hasMore) {
				ReadLine();
			}
			else {
				return false;
			}
		}
		return true;
	}

	std::shared_ptr<Token> Lexer::Read() {
		if (FillQueue()) {
			auto tok = queue.front();
			queue.pop_front();
			return tok;
		}
		else {
			return WordToken::EofWord();
		}
	}

	std::shared_ptr<Token> Lexer::Peek(int i) {
		if (FillQueue(i)) {
			return queue.at(i);
		}
		else {
			return WordToken::EofWord();
		}
	}

	std::shared_ptr<Token> Lexer::Scan() {
		DEBUG(0, "Lexer::Scan\n");
		for (;; Readch()) {
			if (peek == ' ' || peek == '\t') continue;
			else if (peek == '\0') return Token::GetEOL();
			else break;
		}
		switch (peek) {
		case '>':
			if (Readch('=')) return WordToken::GeWord();
			else return WordToken::GtWord();
		case '<':
			if (Readch('=')) return WordToken::LeWord();
			else if (Readch('>')) return WordToken::NeWord();
			else return WordToken::LtWord();
		case ':':
			if (Readch('=')) return WordToken::AssignWord();
			break;
		default:
			break;
		}
		if (isdigit(peek)) {
			int v = 0;
			std::string text;
			do {
				v = 10 * v + peek - '0';
				text.push_back(peek);
				Readch();
			} while (isdigit(peek));
			if (peek != '.') return IntegerToken::GetToken(v, text);
			double x = static_cast<double>(v), d = 10;
			text.push_back(peek);
			for (;;) {
				Readch();
				if (!isdigit(peek)) break;
				x = x + (peek - '0') / d;
				d *= 10;
				text.push_back(peek);
			}
			return RealToken::GetToken(x, text);
		}
		if (isalpha(peek) || peek == '_') {
			std::string text;
			do {
				text.push_back(peek);
				Readch();
			} while (isalnum(peek) || peek == '_');
			return WordToken::GetWord(text);
		}
		auto tok = WordToken::GetWord(peek);
		peek = ' ';
		return tok;
	}

	void Lexer::ReadLine() {
		DEBUG(0, "Lexer::ReadLine\n");
		buf = reader->ReadLine();
		buf.push_back(0);
		if (!reader->HasMore()) {
			hasMore = false;
			return;
		}
		lineNumber += 1;
		pos = 0;
		for (peek = ' ';;) {
			auto tok = Scan();
			if (tok->IsType(Token::END_OF_LINE)) break;
			tok->SetLineNumber(lineNumber);
			queue.push_back(tok);
		}
	}

	void Lexer::Readch() {
		if (pos < (int)buf.length()) {
			peek = buf[pos++];
		}
		else {
			peek = 0;
		}
	}

	bool Lexer::Readch(char c) {
		Readch();
		if (peek == c) {
			peek = ' ';
			return true;
		}
		else {
			return false;
		}
	}

}