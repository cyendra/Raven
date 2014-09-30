#include "Raven.h"
int main() {
	auto interpreter = Raven::Interpreter();
	interpreter->Run();
	system("pause");
	return 0;
}