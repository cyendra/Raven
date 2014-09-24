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
		void RegistId(std::shared_ptr<Token> tok);
	};

}