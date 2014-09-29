#include "Environment.h"

namespace RavenInternal {

	/***************************************************************************
	EnvNode
	***************************************************************************/

	EnvNode::EnvNode() : Prev(nullptr) { }
	
	EnvNode::~EnvNode() { }
	
	void EnvNode::Init() {
		dict.clear();
	}

	std::shared_ptr<Value> EnvNode::GetValue(std::string name) {
		auto it = dict.find(name);
		if (it == dict.end()) return std::shared_ptr<Value>(new Value());
		return it->second;
	}

	bool EnvNode::HasVar(std::string name) {
		auto it = dict.find(name);
		return it != dict.end();
	}

	void EnvNode::SetValue(std::string name, std::shared_ptr<Value>value) {
		dict[name] = value;
	}

	/***************************************************************************
	Environment
	***************************************************************************/

	Environment::Environment() {
		NewEnv();
	}

	Environment::~Environment() {
		PopEnv();
	}

	void Environment::NewEnv() {
		auto p = std::shared_ptr<EnvNode>(new EnvNode());
		p->Prev = node;
		node = p;
	}

	void Environment::PopEnv() { 
		node = node->Prev;
	}

	std::shared_ptr<Value> Environment::GetIdValue(std::shared_ptr<Token> tok) {
		auto name = tok->GetText();
		auto p = node;
		while (p != nullptr) {
			if (p->HasVar(name)) {
				return p->GetValue(name);
			}
			else {
				p = p->Prev;
			}
		}
		return std::shared_ptr<Value>(new Value());
	}

	void Environment::SetIdValue(std::shared_ptr<Token> tok, std::shared_ptr<Value> v) {
		auto name = tok->GetText();
		auto p = node;
		while (p != nullptr) {
			if (p->HasVar(name)) {
				return p->SetValue(name, v);
			}
			else {
				p = p->Prev;
			}
		}
	}

	bool Environment::FindId(std::shared_ptr<Token> tok) {
		auto name = tok->GetText();
		return node->HasVar(name);
	}

	bool Environment::RegistId(std::shared_ptr<Token> tok) {
		if (FindId(tok)) return false;
		auto name = tok->GetText();
		node->SetValue(name, std::shared_ptr<Value>(new Value()));
		return true;
	}

}