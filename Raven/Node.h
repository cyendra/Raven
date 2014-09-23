/*************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Node
*************************************************/

#pragma once

#include "std.h"
#include "Value.h"
#include "Token.h"

namespace RavenInternal {

	/*************************************************
	Node 结点
	*************************************************/

	class Node {
	public:
		Node();
		virtual ~Node();
		virtual void Error(std::string s);
		virtual void SetLexLine(int lexLine);
		virtual int GetLexLine();
		virtual void SetValue(std::shared_ptr<Value> value);
		virtual std::shared_ptr<Value> Reduce();
	private:
		int _lexLine;
		std::shared_ptr<Value> _value;
	};

	/*************************************************
	Expr 表达式
	*************************************************/

	class Expr : public Node {
	public:
		Expr();
		virtual ~Expr();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Token> op;
	};

	/*************************************************
	Id 标识符
	*************************************************/

	class Id : public Expr {
	public:
		Id();
		virtual ~Id();
		virtual std::shared_ptr<Value> Reduce();
	private:

	};

	/*************************************************
	Op 运算符
	*************************************************/

	class Op : public Expr {
	public:
		Op();
		virtual ~Op();
		virtual std::shared_ptr<Value> Reduce();
	private:

	};

	/*************************************************
	Arith 双目运算符
	*************************************************/

	class Arith : public Op {
	public:
		Arith();
		virtual ~Arith();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Expr> expr1, expr2;
	};

	/*************************************************
	Unary 单目运算符
	*************************************************/

	class Unary : public Op {
	public:
		Unary();
		virtual ~Unary();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Expr> expr;
	};

	/*************************************************
	Logical 逻辑运算符
	*************************************************/

	class Logical : public Expr {
	public:
		Logical();
		virtual ~Logical();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Expr> expr1, expr2;
	};

	/*************************************************
	And 逻辑与
	*************************************************/

	class And : public Logical {
	public:
		And();
		virtual ~And();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Or 逻辑或
	*************************************************/

	class Or : public Logical {
	public:
		Or();
		virtual ~Or();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Not 逻辑非
	*************************************************/

	class Not : public Logical {
	public:
		Not();
		virtual ~Not();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Rel 比较运算符
	*************************************************/

	class Rel : public Logical {
	public:
		Rel();
		virtual ~Rel();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Stmt 一条语句
	*************************************************/

	class Stmt : public Node {
	public:
		Stmt();
		virtual ~Stmt();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	If 条件分支
	*************************************************/

	class If : public Stmt {
	public:
		If();
		virtual ~If();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Expr> expr;
		std::shared_ptr<Stmt> stmt;
	};

	/*************************************************
	Else 选择分支
	*************************************************/

	class Else : public Stmt {
	public:
		Else();
		virtual ~Else();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Expr> expr;
		std::shared_ptr<Stmt> stmt1, stmt2;
	};

	/*************************************************
	while 循环语句
	*************************************************/

	class While : public Stmt {
	public:
		While();
		virtual ~While();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Expr> expr;
		std::shared_ptr<Stmt> stmt;
	};

	/*************************************************
	Set 赋值语句
	*************************************************/

	class Set : public Stmt {
	public:
		Set();
		virtual ~Set();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Id> id;
		std::shared_ptr<Expr> expr;
	};

	/*************************************************
	Seq 语句序列
	*************************************************/

	class Seq : public Stmt {
	public:
		Seq();
		virtual ~Seq();
		virtual std::shared_ptr<Value> Reduce();
	private:
		std::shared_ptr<Stmt> stmt1, stmt2;
	};

	/*************************************************
	Break 跳出
	*************************************************/

	class Break : public Stmt {
	public:
		Break();
		virtual ~Break();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Break break语句
	*************************************************/

	class Break : public Stmt {
	public:
		Break();
		virtual ~Break();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Continue continue语句
	*************************************************/

	class Continue : public Stmt {
	public:
		Continue();
		virtual ~Continue();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

}