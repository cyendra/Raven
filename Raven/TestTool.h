#pragma once
#include "std.h"
namespace Debug {
	namespace TestTool {
		using std::cout;
		using std::endl;
		using std::string;
		void TestSizeOfData() {
			int Int = 0;
			long long Longlong = 0;
			double Double = 0;
			std::string String = 0;
			printf("Size of int: %d\n", sizeof(Int));
			printf("Size of long long: %d\n", sizeof(Longlong));
			printf("Size of double: %d\n", sizeof(Double));
			printf("Size of string: %d\n", sizeof(String));
			String = "12345678";
			printf("Size of string: %d\n", sizeof(String));
			union Value
			{
				int Int;
				long long Longlong;
				double Double;
			};
			printf("Size of Value: %d\n", sizeof(Value));
		}

		void TestStringStreamBuf() {
			using std::stringstream;
			stringstream buf1("123");
			stringstream buf2("a123");
			stringstream buf3("");
			stringstream buf4("1-2f3b");
			int a = -1, b = -1, c = -1, d = -1;
			buf1 >> a;
			cout << a << endl;
			buf2 >> b;
			cout << b << endl;
			buf3 >> c;
			cout << c << endl;
			buf4 >> d;
			cout << d << endl;
		}

		void TestStringPushZero() {
			std::string s("123");
			s.push_back(0);
			s.push_back(0);
			s.push_back('4');
			cout << s.length() << endl;
			cout << s.size() << endl;
			cout << s << endl;
			cout << (int)s[3] << endl;
		}

	}

}