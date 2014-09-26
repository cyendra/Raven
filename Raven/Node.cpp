#include "Node.h"

namespace RavenInternal {

	/***************************************************************************
	Node
	***************************************************************************/

	Node::Node() : _lexLine(0) { }

	Node::~Node() { }

	void Node::Error(std::string s) {
		std::cerr << "Error " << s << " near line: " << _lexLine << std::endl;
	}

	void Node::SetLexLine(int lexLine) {
		_lexLine = lexLine;
	}

	int Node::GetLexLine() {
		return _lexLine;
	}

	std::shared_ptr<Value> Node::Eval(Environment* env) {
		return std::shared_ptr<Value>(new Value());
	}

	/***************************************************************************
	Expr
	***************************************************************************/

	Expr::Expr(std::shared_ptr<Token> tok) : Node() {
		op = tok;
	}
	
	Expr::~Expr() { }

	std::shared_ptr<Value> Expr::Eval(Environment* env) {
		return Node::Eval(env);
	}

	/***************************************************************************
	Constant
	***************************************************************************/

	Constant::Constant(std::shared_ptr<Token> tok) : Expr(tok) { }

	Constant::~Constant() { }

	std::shared_ptr<Value> Constant::Eval(Environment* env) {
		switch (op->GetType()) {
		case Token::INTEGER:
			return std::shared_ptr<Value>(new IntegerValue(op->GetInteger));
		case Token::REAL:
			return std::shared_ptr<Value>(new RealValue(op->GetReal));
		case Token::TRUE:
			return std::shared_ptr<Value>(new BooleanValue(true));
		case Token::FALSE:
			return std::shared_ptr<Value>(new BooleanValue(true));
		case Token::STRING:
			return std::shared_ptr<Value>(new StringValue(op->GetString()));
		default:
			break;
		}
		return std::shared_ptr<Value>(new Value());
	}

	/***************************************************************************
	Id
	***************************************************************************/

	Id::Id(std::shared_ptr<Token> tok) : Expr(tok) { }

	Id::~Id() { }

	std::shared_ptr<Value> Id::Eval(Environment* env) {
		return env->GetIdValue(op);
	}

	std::shared_ptr<Token> Id::GetIdToken() {
		return op;
	}

	/***************************************************************************
	Op
	***************************************************************************/

	Op::Op(std::shared_ptr<Token> tok) : Expr(tok) { }

	Op::~Op() { }
	
	std::shared_ptr<Value> Op::Eval(Environment* env) {
		return Expr::Eval(env);
	}

	/***************************************************************************
	Arith
	***************************************************************************/

	Arith::Arith(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2) 
		: Op(tok), expr1(x1), expr2(x2) { }

	Arith::~Arith() { }

	std::shared_ptr<Value> Arith::Eval(Environment* env) {
		auto v1 = expr1->Eval(env);
		auto v2 = expr2->Eval(env);
		switch (op->GetType()) {
		case Token::ADD:
			return Value::Add(v1, v2);
		case Token::SUB:
			return Value::Sub(v1, v2);
		case Token::MUL:
			return Value::Mul(v1, v2);
		case Token::DIV:
			return Value::Div(v1, v2);
		case Token::MOD:
			return Value::Mod(v1, v2);
		default:
			break;
		}
		return Op::Eval(env);
	}

	/***************************************************************************
	Unary
	***************************************************************************/

	Unary::Unary(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x)
		: Op(tok), expr(x) { }

	Unary::~Unary() { }
	
	std::shared_ptr<Value> Unary::Eval(Environment* env) {
		auto v = expr->Eval(env);
		switch (op->GetType()) {
		case Token::SUB:// 肯定不能这么写啦，这是暂时的
			return Value::Sub(std::shared_ptr<IntegerValue>(new IntegerValue(0)), v);
		default:
			break;
		}
		return Op::Eval(env);
	}

	/***************************************************************************
	Logical
	***************************************************************************/

	Logical::Logical(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2)
		: Expr(tok), expr1(x1), expr2(x2) { }

	Logical::~Logical() { }

	std::shared_ptr<Value> Logical::Eval(Environment* env) {
		return Expr::Eval(env);
	}


	/***************************************************************************
	And
	***************************************************************************/

	And::And(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2)
		: Logical(tok, x1, x2) { }

	And::~And() { }

	std::shared_ptr<Value> And::Eval(Environment* env) {
		auto v1 = expr1->Eval(env);
		bool b1 = v1->GetBoolean();
		if (b1 == false) return std::shared_ptr<Value>(new BooleanValue(false));
		auto v2 = expr2->Eval(env);
		bool b2 = v2->GetBoolean();
		return std::shared_ptr<Value>(new BooleanValue(b1 && b2));
	}

	/***************************************************************************
	Or
	***************************************************************************/

	Or::Or(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2)
		: Logical(tok, x1, x2) { }

	Or::~Or() { }

	std::shared_ptr<Value> Or::Eval(Environment* env) {
		auto v1 = expr1->Eval(env);
		bool b1 = v1->GetBoolean();
		if (b1 == true) return std::shared_ptr<Value>(new BooleanValue(true));
		auto v2 = expr2->Eval(env);
		bool b2 = v2->GetBoolean();
		return std::shared_ptr<Value>(new BooleanValue(b1 || b2));
	}

	/***************************************************************************
	Not
	***************************************************************************/
	
	Not::Not(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x) 
		: Logical(tok, x, x) { }

	Not::~Not() { }

	std::shared_ptr<Value> Not::Eval(Environment* env) {
		auto v = expr1->Eval(env);
		bool b = v->GetBoolean();
		return std::shared_ptr<Value>(new BooleanValue(!b));
	}

	/***************************************************************************
	Rel
	***************************************************************************/

	Rel::Rel(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2) 
		: Logical(tok, x1, x2)  { }

	Rel::~Rel() { }

	std::shared_ptr<Value> Rel::Eval(Environment* env) {
		auto v1 = expr1->Eval(env);
		auto v2 = expr2->Eval(env);
		switch (op->GetType()) {
		case Token::EQ:
			return Value::Equal(v1, v2);
		case Token::NE:
			return Value::NotEqual(v1, v2);
		case Token::GT:
			return Value::GreatThan(v1, v2);
		case Token::LT:
			return Value::LessThan(v1, v2);
		case Token::GE:
			return Value::GreatEqual(v1, v2);
		case Token::LE:
			return Value::LessEqual(v1, v2);
		default:
			break;
		}
		return std::shared_ptr<Value>(new BooleanValue(false));
	}

	/***************************************************************************
	Stmt
	***************************************************************************/

	Stmt::Stmt() : Node() { }

	Stmt::~Stmt() { }

	std::shared_ptr<Value> Stmt::Eval(Environment* env) {
		return Node::Eval(env);
	}

	/***************************************************************************
	If
	***************************************************************************/

	If::If(std::shared_ptr<Expr> x, std::shared_ptr<Stmt> s)
		: Stmt(), expr(x), stmt(s) { }

	If::~If() { }
	
	std::shared_ptr<Value> If::Eval(Environment* env) {
		env->NewEnv();
		auto b = expr->Eval(env);
		auto rs = Stmt::Eval(env);
		if (b->GetBoolean()) {
			rs = stmt->Eval(env);
		}
		env->PopEnv();
		return rs;
	}


	/***************************************************************************
	Else
	***************************************************************************/
	
	Else::Else(std::shared_ptr<Expr> x, std::shared_ptr<Stmt> s1, std::shared_ptr<Stmt> s2)
		: Stmt(), expr(x), stmt1(s1), stmt2(s2) { }

	Else::~Else() { }

	std::shared_ptr<Value> Else::Eval(Environment* env) {
		env->NewEnv();
		auto b = expr->Eval(env);
		auto rs = Stmt::Eval(env);
		if (b->GetBoolean()) {
			rs = stmt1->Eval(env);
		}
		else {
			rs = stmt2->Eval(env);
		}
		env->PopEnv();
		return rs;
	}
	
	/***************************************************************************
	while
	***************************************************************************/

	While::While(std::shared_ptr<Expr> x, std::shared_ptr<Stmt> s)
		: Stmt(), expr(x), stmt(s) { }
	
	While::~While() { }
	
	std::shared_ptr<Value> While::Eval(Environment* env) {
		auto rs = Stmt::Eval(env);
		env->NewEnv();
		for (;;) {
			auto b = expr->Eval(env);
			if (b->GetBoolean() == false) break;
			rs = stmt->Eval(env);
			if (rs->IsCtrl(Value::BREAK) || rs->IsCtrl(Value::RETURN)) break;
		}
		if (rs->IsCtrl(Value::BREAK)) rs->SetCtrl(Value::NONE);
		env->PopEnv();
		return rs;
	}

	/***************************************************************************
	Assign
	***************************************************************************/

	Assign::Assign(std::shared_ptr<Id> i, std::shared_ptr<Expr> x)
		: Stmt(), id(i), expr(x) { }

	Assign::~Assign() { }
	
	std::shared_ptr<Value> Assign::Eval(Environment* env) {
		auto v = expr->Eval(env);
		env->SetIdValue(id->GetIdToken(), v);
		return v;
	}

	/***************************************************************************
	Seq
	***************************************************************************/

	Seq::Seq() : Stmt() { }

	Seq::~Seq() { }
	
	void Seq::PushStmt(std::shared_ptr<Stmt> stmt) {
		stmts.push_back(stmt);
	}

	std::shared_ptr<Value> Seq::Eval(Environment* env) {
		auto rs = std::shared_ptr<Value>(new Value());
		for each (auto stmt in stmts) {
			rs = stmt->Eval(env);
			if (rs->IsCtrl(Value::BREAK) || rs->IsCtrl(Value::RETURN) || rs->IsCtrl(Value::CONTINUE)) break;
		}
		return rs;
	}

	/***************************************************************************
	Break
	***************************************************************************/

	Break::Break() : Stmt() { }
	
	Break::~Break() { }
	
	std::shared_ptr<Value> Break::Eval(Environment* env) {
		return std::shared_ptr<Value>(new Value(Value::Ctrl::BREAK));
	}

	/***************************************************************************
	Continue
	***************************************************************************/

	Continue::Continue() : Stmt() { }

	Continue::~Continue() { }

	std::shared_ptr<Value> Continue::Eval(Environment* env) {
		return std::shared_ptr<Value>(new Value(Value::Ctrl::CONTINUE));
	}

	/***************************************************************************
	Return
	***************************************************************************/

	Return::Return(std::shared_ptr<Expr> x) : Stmt(), expr(x) { }

	Return::~Return() { }

	std::shared_ptr<Value> Return::Eval(Environment* env) {
		auto rs = expr->Eval(env);
		rs->SetCtrl(Value::Ctrl::RETURN);
		return rs;
	}

	/***************************************************************************
	Empty
	***************************************************************************/

	Empty::Empty() : Stmt() { }

	Empty::~Empty() { }

	std::shared_ptr<Value> Empty::Eval(Environment* env) {
		return Stmt::Eval(env);
	}

	/***************************************************************************
	Var
	***************************************************************************/

	Var::Var() : Stmt() { }
	
	Var::~Var() { }

	void Var::PushVar(std::shared_ptr<Token> word) {
		vars.push_back(word);
	}

	std::shared_ptr<Value> Var::Eval(Environment* env) {
		for each (auto var in vars) {
			env->RegistId(var);
		}
		return Stmt::Eval(env);
	}

}