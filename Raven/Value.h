/*************************************************
Raven Lang 0.1
Developer: cyendra
Classes:
Value
*************************************************/
#pragma once

namespace RavenInternal {

	/*************************************************
	Value
	*************************************************/

	class Value {
	public:
		enum Tag {
			INTEGER, REAL, BOOLEAN, STRING, FUNCTION, NULL, // 值的类型
		};
		enum Ctrl{
			BREAK, RETURN, CONTINUE // 控制类型
		};
		Value();
		virtual ~Value();
	private:
		Tag _type;
		Ctrl _ctrl;
	};

}