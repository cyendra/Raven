/***************************************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Node
Expr	< Node			表达式
Constant< Expr			字面常量
Id		< Expr			标识符
Op		< Expr			运算符
Arith	< Op			双目运算符
Unary	< Op			单目运算符
Logical < Expr			逻辑运算符
And		< Logical		逻辑与
Or		< Logical		逻辑或
Not		< Logical		逻辑非
Rel		< Logical		比较运算符
Stmt	< Node			一条语句
If		< Stmt			条件分支
Else	< Stmt			选择分支
while	< Stmt			循环语句
Assign	< Stmt			赋值语句
Seq		< Stmt			语句序列
Break	< Stmt			跳出语句
Continue< Stmt			继续语句
Return	< Stmt			返回语句
Empty	< Stmt			空语句
Var		< Stmt			变量定义语句
***************************************************************************/

#pragma once

#include "std.h"
#include "Value.h"
#include "Token.h"
#include "Environment.h"

namespace RavenInternal {

	/***************************************************************************
	Node 结点
	表达式Expr与语句Stmt都是结点的派生类
	任何结点都可以执行Eval操作：
		对于表达式，返回表达式的值
		对于语句，返回语句的值
		默认返回空值
	变量_lexLine表示当前结点在源文件中的行号，提供Get与Assign方法来访问
	Error表示当前结点运行时出错，它接受一个字符串，输出错误信息
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
	Expr 表达式
	所有表达式的基类
	接受一个Token表示表达式的类型
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
	Constant 常量
	常量结点是一个叶子结点
	所以还要根据token的类型搞他自己的值
	执行Eval操作会得到该常量的值
	***************************************************************************/

	class Constant : public Expr {
	public:
		Constant(std::shared_ptr<Token> tok);
		virtual ~Constant();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	private:
	};

	/***************************************************************************
	Id 标识符
	标识符结点是一个叶子结点
	执行Eval操作会得到该标识符的值
	如果符号表env中没有该标识符的话会报错
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
	Op 运算符
	双目运算符与单目运算符都是Op类的派生类
	***************************************************************************/

	class Op : public Expr {
	public:
		Op(std::shared_ptr<Token> tok);
		virtual ~Op();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Arith 双目运算符
	双目运算符除了表示运算符的Token外还要接受两个表达式expr1,expr2
	expr1是运算符左侧的表达式，expr2是右侧的表达式
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
	Unary 单目运算符
	单目运算符除了表示运算符的Token外还要接受一个表达式expr
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
	Logical 逻辑运算符
	与或非三个逻辑运算符和比较运算符的基类
	接受运算符Token，和左右两个表达式
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
	And 逻辑与
	***************************************************************************/

	class And : public Logical {
	public:
		And(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2);
		virtual ~And();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Or 逻辑或
	***************************************************************************/

	class Or : public Logical {
	public:
		Or(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2);
		virtual ~Or();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Not 逻辑非
	逻辑非虽然是单目运算符，但是基类要有左右两个表达式
	于是用一个表达式当两个用
	***************************************************************************/

	class Not : public Logical {
	public:
		Not(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x);
		virtual ~Not();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Rel 比较运算符
	> < >= <= == 看着算
	***************************************************************************/

	class Rel : public Logical {
	public:
		Rel(std::shared_ptr<Token> tok, std::shared_ptr<Expr> x1, std::shared_ptr<Expr> x2);
		virtual ~Rel();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Stmt 一条语句
	每条语句都有返回值，实在不行new个Value返回也行
	***************************************************************************/

	class Stmt : public Node {
	public:
		Stmt();
		virtual ~Stmt();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	If 条件分支
	这个语句是指只有if语句没有else的情况
	因此他只接受一个语句，当表达式为真时执行
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
	Else 选择分支
	if + else 
	关于悬空else的问题，我们默认else属于最近的if，大概没问题
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
	while 循环语句
	就是while循环啦
	当返回值为的Ctrl为BREAK时中断，为CONTINUE时继续跑
	记得返回值要吃掉BREAK
	每次开始循环时判断一下表达式的真假，为真时才循环
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
	Assign 赋值语句
	不可以对未定义的变量赋值，这个是常识啦
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
	Seq 语句序列
	这个其实被我搞成了Block的定义，我认为很妥当
	接受一个序列的语句，然后顺序执行，把最后一个语句的返回值作为返回值
	PushStmt按顺序将语句按顺序添加进去
	注意Eval时遇到返回值的Ctrl为RETURN或BREAK或CONTINUE时要向上返回
	直到While语句接受到这条控制信息
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
	Break 跳出
	这个break也算个语句啊
	返回的Value的Ctrl是BREAK
	***************************************************************************/

	class Break : public Stmt {
	public:
		Break();
		virtual ~Break();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Continue continue语句
	配合Break语句食用更佳
	***************************************************************************/

	class Continue : public Stmt {
	public:
		Continue();
		virtual ~Continue();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Return Return语句
	接受一个表达式，然后将表达式的Value的Ctrl设为RETRUN然后不管啦
	注意要有默认返回值
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
	Empty 空语句
	这是我自创的，空语句也是终结符
	其实就是一个分号，连Token都不用存，随便返回一个值就好了
	***************************************************************************/

	class Empty : public Stmt {
	public:
		Empty();
		virtual ~Empty();
		virtual std::shared_ptr<Value> Eval(Environment* env);
	protected:
	};

	/***************************************************************************
	Var 变量定义语句
	搞这个语句我也很忐忑，到底应该怎么设计变量定义语句呢?
	可以一次给多个变量定义吗？可以赋初值吗？
	没想好
	暂定为不许赋初值好了
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