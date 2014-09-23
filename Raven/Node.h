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
	Node ���
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
	Expr ���ʽ
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
	Id ��ʶ��
	*************************************************/

	class Id : public Expr {
	public:
		Id();
		virtual ~Id();
		virtual std::shared_ptr<Value> Reduce();
	private:

	};

	/*************************************************
	Op �����
	*************************************************/

	class Op : public Expr {
	public:
		Op();
		virtual ~Op();
		virtual std::shared_ptr<Value> Reduce();
	private:

	};

	/*************************************************
	Arith ˫Ŀ�����
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
	Unary ��Ŀ�����
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
	Logical �߼������
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
	And �߼���
	*************************************************/

	class And : public Logical {
	public:
		And();
		virtual ~And();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Or �߼���
	*************************************************/

	class Or : public Logical {
	public:
		Or();
		virtual ~Or();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Not �߼���
	*************************************************/

	class Not : public Logical {
	public:
		Not();
		virtual ~Not();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Rel �Ƚ������
	*************************************************/

	class Rel : public Logical {
	public:
		Rel();
		virtual ~Rel();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Stmt һ�����
	*************************************************/

	class Stmt : public Node {
	public:
		Stmt();
		virtual ~Stmt();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	If ������֧
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
	Else ѡ���֧
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
	while ѭ�����
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
	Set ��ֵ���
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
	Seq �������
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
	Break ����
	*************************************************/

	class Break : public Stmt {
	public:
		Break();
		virtual ~Break();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Break break���
	*************************************************/

	class Break : public Stmt {
	public:
		Break();
		virtual ~Break();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

	/*************************************************
	Continue continue���
	*************************************************/

	class Continue : public Stmt {
	public:
		Continue();
		virtual ~Continue();
		virtual std::shared_ptr<Value> Reduce();
	private:
	};

}