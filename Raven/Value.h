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
			INTEGER, REAL, BOOLEAN, STRING, FUNCTION, NULL, // ֵ������
		};
		enum Ctrl{
			BREAK, RETURN, CONTINUE // ��������
		};
		Value();
		virtual ~Value();
	private:
		Tag _type;
		Ctrl _ctrl;
	};

}