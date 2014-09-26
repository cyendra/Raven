/***************************************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Node
Expr	< Node			���ʽ
Constant< Expr			���泣��
Id		< Expr			��ʶ��
Op		< Expr			�����
Arith	< Op			˫Ŀ�����
Unary	< Op			��Ŀ�����
Logical < Expr			�߼������
And		< Logical		�߼���
Or		< Logical		�߼���
Not		< Logical		�߼���
Rel		< Logical		�Ƚ������
Stmt	< Node			һ�����
If		< Stmt			������֧
Else	< Stmt			ѡ���֧
while	< Stmt			ѭ�����
Assign	< Stmt			��ֵ���
Seq		< Stmt			�������
Break	< Stmt			�������
Continue< Stmt			�������
Return	< Stmt			�������
Empty	< Stmt			�����
Var		< Stmt			�����������
***************************************************************************/

#pragma once

#include "std.h"
#include "Value.h"
#include "Token.h"
#include "Environment.h"

namespace RavenInternal {

	/***************************************************************************
	Node ���
	���ʽExpr�����Stmt���ǽ���������
	�κν�㶼����ִ��Eval������
		���ڱ��ʽ�����ر��ʽ��ֵ
		������䣬��������ֵ
		Ĭ�Ϸ��ؿ�ֵ
	����_lexLine��ʾ��ǰ�����Դ�ļ��е��кţ��ṩGet��Assign����������
	Error��ʾ��ǰ�������ʱ����������һ���ַ��������������Ϣ
	***************************************************************************/

	class Node {
	public:
		Node();
		virtual ~Node();
		virtual void Error(std::string s);
		virtual void SetLexLine(int lexLine);
		virtual int GetLexLine();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		int _lexLine;
	};

	/***************************************************************************
	Expr ���ʽ
	���б��ʽ�Ļ���
	����һ��Token��ʾ���ʽ������
	***************************************************************************/

	class Expr : public Node {
	public:
		Expr(std::shared_ptr<Token> tok);
		virtual ~Expr();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Token> op;
	};

	/***************************************************************************
	Constant ����
	���������һ��Ҷ�ӽ��
	���Ի�Ҫ����token�����͸����Լ���ֵ
	ִ��Eval������õ��ó�����ֵ
	***************************************************************************/

	class Constant : public Expr {
	public:
		Constant(std::shared_ptr<Token> tok);
		virtual ~Constant();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	private:
	};

	/***************************************************************************
	Id ��ʶ��
	��ʶ�������һ��Ҷ�ӽ��
	ִ��Eval������õ��ñ�ʶ����ֵ
	������ű�env��û�иñ�ʶ���Ļ��ᱨ��
	***************************************************************************/

	class Id : public Expr {
	public:
		Id(std::shared_ptr<Token> tok);
		virtual ~Id();
		virtual std::shared_ptr<Value> Eval(Environment* env);
		virtual std::shared_ptr<Token> Id::GetIdToken();
	protected:
	};

	/***************************************************************************
	Op �����
	˫Ŀ������뵥Ŀ���������Op���������
	***************************************************************************/

	class Op : public Expr {
	public:
		Op(std::shared_ptr<Token> tok);
		virtual ~Op();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Arith ˫Ŀ�����
	˫Ŀ��������˱�ʾ�������Token�⻹Ҫ�����������ʽexpr1,expr2
	expr1����������ı��ʽ��expr2���Ҳ�ı��ʽ
	***************************************************************************/

	class Arith : public Op {
	public:
		Arith(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2);
		virtual ~Arith();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Expr> expr1, expr2;
	};

	/***************************************************************************
	Unary ��Ŀ�����
	��Ŀ��������˱�ʾ�������Token�⻹Ҫ����һ�����ʽexpr
	***************************************************************************/

	class Unary : public Op {
	public:
		Unary(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x);
		virtual ~Unary();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Expr> expr;
	};

	/***************************************************************************
	Logical �߼������
	���������߼�������ͱȽ�������Ļ���
	���������Token���������������ʽ
	***************************************************************************/

	class Logical : public Expr {
	public:
		Logical(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2);
		virtual ~Logical();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Expr> expr1, expr2;
	};

	/***************************************************************************
	And �߼���
	***************************************************************************/

	class And : public Logical {
	public:
		And(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2);
		virtual ~And();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Or �߼���
	***************************************************************************/

	class Or : public Logical {
	public:
		Or(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2);
		virtual ~Or();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Not �߼���
	�߼�����Ȼ�ǵ�Ŀ����������ǻ���Ҫ�������������ʽ
	������һ�����ʽ��������
	***************************************************************************/

	class Not : public Logical {
	public:
		Not(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x);
		virtual ~Not();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Rel �Ƚ������
	> < >= <= == ������
	***************************************************************************/

	class Rel : public Logical {
	public:
		Rel(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2);
		virtual ~Rel();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Stmt һ�����
	ÿ����䶼�з���ֵ��ʵ�ڲ���new��Value����Ҳ��
	***************************************************************************/

	class Stmt : public Node {
	public:
		Stmt();
		virtual ~Stmt();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	If ������֧
	��������ָֻ��if���û��else�����
	�����ֻ����һ����䣬�����ʽΪ��ʱִ��
	***************************************************************************/

	class If : public Stmt {
	public:
		If(std::shared_ptr<Expr> x, std::shared_ptr<Stmt> s);
		virtual ~If();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Expr> expr;
		std::shared_ptr<Stmt> stmt;
	};

	/***************************************************************************
	Else ѡ���֧
	if + else 
	��������else�����⣬����Ĭ��else���������if�����û����
	***************************************************************************/

	class Else : public Stmt {
	public:
		Else(std::shared_ptr<Expr> x, std::shared_ptr<Stmt> s1, std::shared_ptr<Stmt> s2);
		virtual ~Else();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Expr> expr;
		std::shared_ptr<Stmt> stmt1, stmt2;
	};

	/***************************************************************************
	while ѭ�����
	����whileѭ����
	������ֵΪ��CtrlΪBREAKʱ�жϣ�ΪCONTINUEʱ������
	�ǵ÷���ֵҪ�Ե�BREAK
	ÿ�ο�ʼѭ��ʱ�ж�һ�±��ʽ����٣�Ϊ��ʱ��ѭ��
	***************************************************************************/

	class While : public Stmt {
	public:
		While(std::shared_ptr<Expr> x, std::shared_ptr<Stmt> s);
		virtual ~While();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Expr> expr;
		std::shared_ptr<Stmt> stmt;
	};

	/***************************************************************************
	Assign ��ֵ���
	�����Զ�δ����ı�����ֵ������ǳ�ʶ��
	***************************************************************************/

	class Assign : public Stmt {
	public:
		Assign(std::shared_ptr<Id> i, std::shared_ptr<Expr> x);
		virtual ~Assign();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Id> id;
		std::shared_ptr<Expr> expr;
	};

	/***************************************************************************
	Seq �������
	�����ʵ���Ҹ����Block�Ķ��壬����Ϊ���׵�
	����һ�����е���䣬Ȼ��˳��ִ�У������һ�����ķ���ֵ��Ϊ����ֵ
	PushStmt��˳����䰴˳����ӽ�ȥ
	ע��Evalʱ��������ֵ��CtrlΪRETURN��BREAK��CONTINUEʱҪ���Ϸ���
	ֱ��While�����ܵ�����������Ϣ
	***************************************************************************/

	class Seq : public Stmt {
	public:
		Seq();
		virtual ~Seq();
		virtual void PushStmt(std::shared_ptr<Stmt> stmt);
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::vector<std::shared_ptr<Stmt>> stmts;
	};

	/***************************************************************************
	Break ����
	���breakҲ�����䰡
	���ص�Value��Ctrl��BREAK
	***************************************************************************/

	class Break : public Stmt {
	public:
		Break();
		virtual ~Break();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Continue continue���
	���Break���ʳ�ø���
	***************************************************************************/

	class Continue : public Stmt {
	public:
		Continue();
		virtual ~Continue();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Return Return���
	����һ�����ʽ��Ȼ�󽫱��ʽ��Value��Ctrl��ΪRETRUNȻ�󲻹���
	ע��Ҫ��Ĭ�Ϸ���ֵ
	***************************************************************************/

	class Return : public Stmt {
	public:
		Return(std::shared_ptr<Expr> x);
		virtual ~Return();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::shared_ptr<Expr> expr;
	};

	/***************************************************************************
	Empty �����
	�������Դ��ģ������Ҳ���ս��
	��ʵ����һ���ֺţ���Token�����ô棬��㷵��һ��ֵ�ͺ���
	***************************************************************************/

	class Empty : public Stmt {
	public:
		Empty();
		virtual ~Empty();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Var �����������
	����������Ҳ������������Ӧ����ô��Ʊ������������?
	����һ�θ�������������𣿿��Ը���ֵ��
	û���
	�ݶ�Ϊ������ֵ����
	***************************************************************************/

	class Var : public Stmt {
	public:
		Var();
		virtual ~Var();
		virtual void PushVar(std::shared_ptr<Token> word);
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
		std::vector<std::shared_ptr<Token>> vars;
	};

}