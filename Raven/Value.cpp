#include "Value.h"

namespace RavenInternal {

	/***************************************************************************
	Value
	***************************************************************************/

	Value::Value() : _type(UNKOWN), _ctrl(NONE) { }

	Value::Value(Type type, Ctrl ctrl) : _type(type), _ctrl(ctrl) { }

	Value::Value(Type type) : _type(type), _ctrl(NONE) { }

	Value::Value(Ctrl ctrl) : _type(UNKOWN), _ctrl(ctrl) { }

	Value::~Value() { }

	void Value::SetType(Type type) {
		_type = type;
	}

	void Value::SetCtrl(Ctrl ctrl) {
		_ctrl = ctrl;
	}

	Value::Type Value::GetType() {
		return _type;
	}

	Value::Ctrl Value::GetCtrl() {
		return _ctrl;
	}

	bool Value::IsType(Type type) {
		return type == _type;
	}

	bool Value::IsCtrl(Ctrl ctrl) {
		return ctrl == _ctrl;
	}

	int Value::GetInteger() {
		return 0;
	}

	double Value::GetReal() {
		return 0.0;
	}

	bool Value::GetBoolean() {
		return false;
	}

	std::string Value::GetString() {
		return "";
	}

	std::shared_ptr<Value> Value::Add(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::STRING) {
			std::string v = tp1->GetString() + tp2->GetString();
			return std::shared_ptr<Value>(new StringValue(v));
		}
		else if (tp == Type::REAL) {
			double v = tp1->GetReal() + tp2->GetReal();
			return std::shared_ptr<Value>(new RealValue(v));
		}
		else if (tp == Type::INTEGER || tp == Type::BOOLEAN) {
			int v = tp1->GetInteger() + tp2->GetInteger();
			return std::shared_ptr<Value>(new IntegerValue(v));
		}
		else {
			return std::shared_ptr<Value>(new Value());
		}
	}

	std::shared_ptr<Value> Value::Sub(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::REAL) {
			double v = tp1->GetReal() - tp2->GetReal();
			return std::shared_ptr<Value>(new RealValue(v));
		}
		else if (tp == Type::INTEGER || tp == Type::BOOLEAN) {
			int v = tp1->GetInteger() - tp2->GetInteger();
			return std::shared_ptr<Value>(new IntegerValue(v));
		}
		else {
			return std::shared_ptr<Value>(new Value());
		}
	}

	std::shared_ptr<Value> Value::Mul(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::REAL) {
			double v = tp1->GetReal() * tp2->GetReal();
			return std::shared_ptr<Value>(new RealValue(v));
		}
		else if (tp == Type::INTEGER || tp == Type::BOOLEAN) {
			int v = tp1->GetInteger() * tp2->GetInteger();
			return std::shared_ptr<Value>(new IntegerValue(v));
		}
		else {
			return std::shared_ptr<Value>(new Value());
		}
	}

	std::shared_ptr<Value> Value::Div(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::REAL) {
			if (tp2->GetReal() == 0) return std::shared_ptr<Value>(new Value());
			double v = tp1->GetReal() / tp2->GetReal();
			return std::shared_ptr<Value>(new RealValue(v));
		}
		else if (tp == Type::INTEGER || tp == Type::BOOLEAN) {
			if (tp2->GetInteger() == 0) return std::shared_ptr<Value>(new Value());
			int v = tp1->GetInteger() / tp2->GetInteger();
			return std::shared_ptr<Value>(new IntegerValue(v));
		}
		else {
			return std::shared_ptr<Value>(new Value());
		}
	}

	std::shared_ptr<Value> Value::Mod(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::INTEGER || tp == Type::BOOLEAN) {
			if (tp2->GetInteger() == 0) return std::shared_ptr<Value>(new Value());
			int v = tp1->GetInteger() % tp2->GetInteger();
			return std::shared_ptr<Value>(new IntegerValue(v));
		}
		else {
			return std::shared_ptr<Value>(new Value());
		}
	}

	std::shared_ptr<Value> Value::Equal(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::STRING) {
			bool b = tp1->GetString() == tp2->GetString();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::REAL) {
			bool b = tp1->GetReal() == tp2->GetReal();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::INTEGER) {
			bool b = tp1->GetInteger() == tp2->GetInteger();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::BOOLEAN) {
			bool b = tp1->GetBoolean() == tp2->GetBoolean();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else {
			return std::shared_ptr<Value>(new BooleanValue(false));
		}
	}

	std::shared_ptr<Value> Value::NotEqual(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::STRING) {
			bool b = tp1->GetString() != tp2->GetString();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::REAL) {
			bool b = tp1->GetReal() != tp2->GetReal();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::INTEGER) {
			bool b = tp1->GetInteger() != tp2->GetInteger();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::BOOLEAN) {
			bool b = tp1->GetBoolean() != tp2->GetBoolean();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else {
			return std::shared_ptr<Value>(new BooleanValue(false));
		}
	}

	std::shared_ptr<Value> Value::GreatThan(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::STRING) {
			bool b = tp1->GetString() > tp2->GetString();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::REAL) {
			bool b = tp1->GetReal() > tp2->GetReal();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::INTEGER) {
			bool b = tp1->GetInteger() > tp2->GetInteger();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::BOOLEAN) {
			bool b = tp1->GetBoolean() > tp2->GetBoolean();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else {
			return std::shared_ptr<Value>(new BooleanValue(false));
		}
	}

	std::shared_ptr<Value> Value::LessThan(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::STRING) {
			bool b = tp1->GetString() < tp2->GetString();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::REAL) {
			bool b = tp1->GetReal() < tp2->GetReal();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::INTEGER) {
			bool b = tp1->GetInteger() < tp2->GetInteger();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::BOOLEAN) {
			bool b = tp1->GetBoolean() < tp2->GetBoolean();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else {
			return std::shared_ptr<Value>(new BooleanValue(false));
		}
	}

	std::shared_ptr<Value> Value::GreatEqual(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::STRING) {
			bool b = tp1->GetString() >= tp2->GetString();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::REAL) {
			bool b = tp1->GetReal() >= tp2->GetReal();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::INTEGER) {
			bool b = tp1->GetInteger() >= tp2->GetInteger();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::BOOLEAN) {
			bool b = tp1->GetBoolean() >= tp2->GetBoolean();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else {
			return std::shared_ptr<Value>(new BooleanValue(false));
		}
	}

	std::shared_ptr<Value> Value::LessEqual(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		auto tp = Cast(tp1, tp2);
		if (tp == Type::STRING) {
			bool b = tp1->GetString() <= tp2->GetString();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::REAL) {
			bool b = tp1->GetReal() <= tp2->GetReal();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::INTEGER) {
			bool b = tp1->GetInteger() <= tp2->GetInteger();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else if (tp == Type::BOOLEAN) {
			bool b = tp1->GetBoolean() <= tp2->GetBoolean();
			return std::shared_ptr<Value>(new BooleanValue(b));
		}
		else {
			return std::shared_ptr<Value>(new BooleanValue(false));
		}
	}

	Value::Type Value::Cast(std::shared_ptr<Value> tp1, std::shared_ptr<Value> tp2) {
		if (tp1->IsType(Type::UNKOWN) || tp2->IsType(Type::UNKOWN)) return Type::UNKOWN;
		if (tp1->IsType(Type::STRING) || tp2->IsType(Type::STRING)) return Type::STRING;
		if (tp1->IsType(Type::REAL) || tp2->IsType(Type::REAL)) return Type::REAL;
		if (tp1->IsType(Type::INTEGER) || tp2->IsType(Type::INTEGER)) return Type::INTEGER;
		if (tp1->IsType(Type::BOOLEAN) || tp2->IsType(Type::BOOLEAN)) return Type::BOOLEAN;
		return Type::UNKOWN;
	}

	/***************************************************************************
	IntegerValue
	***************************************************************************/

	IntegerValue::IntegerValue() : Value(Type::INTEGER) { }

	IntegerValue::IntegerValue(int v) : Value(Type::INTEGER), _value(v) { }
	
	IntegerValue::~IntegerValue() { }

	int IntegerValue::GetInteger() {
		return _value;
	}

	double IntegerValue::GetReal() {
		return static_cast<double>(_value);
	}

	bool IntegerValue::GetBoolean() {
		return _value != 0;
	}

	std::string IntegerValue::GetString() {
		std::stringstream buf;
		std::string str;
		buf << _value;
		buf >> str;
		return str;
	}

	/***************************************************************************
	RealValue
	***************************************************************************/

	RealValue::RealValue() : Value(Type::REAL) { }

	RealValue::RealValue(double v) : Value(Type::REAL), _value(v) { }

	RealValue::~RealValue() { }

	int RealValue::GetInteger() {
		return static_cast<int>(_value);
	}

	double RealValue::GetReal() {
		return _value;
	}

	bool RealValue::GetBoolean() {
		return _value != 0.0;
	}

	std::string RealValue::GetString(){
		std::stringstream buf;
		std::string str;
		buf << _value;
		buf >> str;
		return str;
	}

	/***************************************************************************
	BooleanValue
	***************************************************************************/

	BooleanValue::BooleanValue() : Value(Type::BOOLEAN) { }

	BooleanValue::BooleanValue(bool v) : Value(Type::BOOLEAN), _value(v) { }

	BooleanValue::~BooleanValue() { }

	int BooleanValue::GetInteger() {
		return static_cast<int>(_value);
	}
	
	double BooleanValue::GetReal() {
		return static_cast<double>(_value);
	}

	bool BooleanValue::GetBoolean() {
		return _value;
	}

	std::string BooleanValue::GetString(){
		if (_value) return "true";
		else return "false";
	}

	/***************************************************************************
	StringValue
	***************************************************************************/

	StringValue::StringValue() : Value(Type::BOOLEAN) { }

	StringValue::StringValue(std::string v) : Value(Type::STRING), _value(v) { }

	StringValue::~StringValue() { }

	int StringValue::GetInteger() {
		int res = 0;
		std::stringstream buf(_value);
		buf >> res;
		return res;
	}

	double StringValue::GetReal() {
		double res = 0.0;
		std::stringstream buf(_value);
		buf >> res;
		return res;
	}

	bool StringValue::GetBoolean() {
		return _value != "";
	}

	std::string StringValue::GetString(){
		return _value;
	}

}