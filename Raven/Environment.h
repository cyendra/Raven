/***************************************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Environment
***************************************************************************/

#pragma once

#include "std.h"
#include "Value.h"
#include "Token.h"

namespace RavenInternal {

	/***************************************************************************
	EnvNode
	***************************************************************************/

	class EnvNode {
	public:
		EnvNode();
		~EnvNode();
		std::shared_ptr<Value> GetValue(std::string name);
		bool HasVar(std::string name);
		void SetValue(std::string, std::shared_ptr<Value>value);
		void Init();
		std::shared_ptr<EnvNode> Prev;
	private:
		std::map<std::string, std::shared_ptr<Value>> dict;
	};

	/***************************************************************************
	Environment
	***************************************************************************/

	class Environment {
	public:
		Environment();
		~Environment();
		void NewEnv();
		void PopEnv();
		std::shared_ptr<Value> GetIdValue(std::shared_ptr<Token> tok);
		void SetIdValue(std::shared_ptr<Token> tok, std::shared_ptr<Value> v);
		bool FindId(std::shared_ptr<Token> tok);
		void RegistId(std::shared_ptr<Token> tok);
	private:
		std::shared_ptr<EnvNode> node;
	};

}