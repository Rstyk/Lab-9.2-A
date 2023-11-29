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

			students[0] = { "������", 10, 80, 90, 3, �� };
			students[1] = { "������", 60, 70, 80, 2, �� };
			students[2] = { "�������", 50, 60, 70, 1, в };

			Sort(students, N);

			Assert::IsTrue(students[0].prizv == "������");
			Assert::IsTrue(students[1].prizv == "������");
			Assert::IsTrue(students[2].prizv == "�������");

		}
	};
}
