#include "Environment.h"

namespace RavenInternal {

	/***************************************************************************
	EnvNode
	***************************************************************************/

	EnvNode::EnvNode() { }
	EnvNode::~EnvNode() { }

	/***************************************************************************
	Environment
	***************************************************************************/

	Environment::Environment() { }

	Environment::~Environment() { }

	void Environment::NewEnv() { }

	void Environment::PopEnv() { }

	std::shared_ptr<Value> Environment::GetIdValue(std::shared_ptr<Token> tok) {

	}

	void Environment::SetIdValue(std::shared_ptr<Token> tok, std::shared_ptr<Value> v) {

	}

	void Environment::RegistId(std::shared_ptr<Token> tok) {

	}

}