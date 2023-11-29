#include "pch.h"
#include "CppUnitTest.h"
#include "../laba 9.2 A/laba 9.2 A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab92A
{
	TEST_CLASS(lab92A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int N = 3;
			Student students[N];

			students[0] = { "Іванов", 10, 80, 90, 3, КН };
			students[1] = { "Петров", 60, 70, 80, 2, ФЛ };
			students[2] = { "Сидоров", 50, 60, 70, 1, РІ };

			Sort(students, N);

			Assert::IsTrue(students[0].prizv == "Петров");
			Assert::IsTrue(students[1].prizv == "Іванов");
			Assert::IsTrue(students[2].prizv == "Сидоров");

		}
	};
}
