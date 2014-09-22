#pragma once
#include <string>
#include <cstdio>
namespace Debug {
	namespace TestTool {
		void SizeOfData() {
			int Int;
			long long Longlong;
			double Double;
			std::string String;
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
	}

}