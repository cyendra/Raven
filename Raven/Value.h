/***************************************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Value
IntegerValue
RealValue
BooleanValue
StringValue
***************************************************************************/
#pragma once

#include "std.h"

namespace RavenInternal {

	/***************************************************************************
	Value
	***************************************************************************/

	class Value {
	public:
		enum Type {
			INTEGER, REAL, BOOLEAN, STRING, FUNCTION, UNKOWN, // 值的类型
		};
		enum Ctrl{
			BREAK, RETURN, CONTINUE, NONE // 控制类型
		};
		Value();
		Value(Type type, Ctrl ctrl);
		Value(Type type);
		Value(Ctrl ctrl);
		virtual ~Value();
		virtual void SetType(Type type);
		virtual void SetCtrl(Ctrl ctrl);
		virtual Type GetType();
		virtual Ctrl GetCtrl();
		virtual bool IsType(Type type);
		virtual bool IsCtrl(Ctrl ctrl);
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
		static std::shared_ptr<Value> Add(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> Sub(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> Mul(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> Div(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> Mod(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> Equal(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> NotEqual(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> GreatThan(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> LessThan(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> GreatEqual(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static std::shared_ptr<Value> LessEqual(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
		static Type Cast(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2);
	private:
		Type _type;
		Ctrl _ctrl;
	};

	/***************************************************************************
	IntegerValue
	***************************************************************************/

	class IntegerValue : public Value {
	public:
		IntegerValue();
		IntegerValue(int v);
		virtual ~IntegerValue();
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
	private:
		int _value;
	};

	/***************************************************************************
	RealValue
	***************************************************************************/

	class RealValue : public Value {
	public:
		RealValue();
		RealValue(double v);
		virtual ~RealValue();
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
	private:
		double _value;
	};

	/***************************************************************************
	BooleanValue
	***************************************************************************/

	class BooleanValue : public Value {
	public:
		BooleanValue();
		BooleanValue(bool v);
		virtual ~BooleanValue();
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
	private:
		bool _value;
	};

	/***************************************************************************
	StringValue
	***************************************************************************/

	class StringValue : public Value {
	public:
		StringValue();
		StringValue(std::string v);
		virtual ~StringValue();
		virtual int GetInteger();
		virtual double GetReal();
		virtual bool GetBoolean();
		virtual std::string GetString();
	private:
		std::string _value;
	};

}