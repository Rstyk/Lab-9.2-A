#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Spec { �� = 1, в, ��, �� };
string specStr[] = { "��", "в", "��", "��" };
struct Student
{
	string prizv;
	unsigned physics;
	unsigned math;
	unsigned inform;
	unsigned kurs;
	Spec spec;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const int avgGrade);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N;
	cout << "������ ������� �������� N: "; cin >> N;
	Student* p = new Student[N];
	double proc;
	int ispec;
	Spec spec;
	string prizv;
	int physics;
	int matem;
	int inform;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl;
		cout << " [4] - ������� ����� ���������� �� ������� �� ��������" << endl << endl;
		cout << " [5] - �������� ������������� �� ���� �����"
			<< endl << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;

		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			cout << "������ ����� ������:" << endl;
			cout << " ������������ (0 - ��, 1 - в, 2 - ��, 3 - ��): ";
			cin >> ispec;
			spec = (Spec)ispec;
			cin.get();
			cin.sync();
			cout << " �������: "; getline(cin, prizv);
			cout << endl;
			int avgGrade;
			cout << "������� ���: "; cin >> avgGrade;
			cout << endl;

			if ((found = BinSearch(p, N, prizv, spec, avgGrade)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;

			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();
		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ����: "; cin >> p[i].kurs;
		cout << " ������������ (0 - ��, 1 - в, 2 - ��, 3 - ��): ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		cout << " ������ � ������: "; cin >> p[i].physics;
		cout << " ������ � ����������: "; cin >> p[i].math;
		cout << " ������ � �����������: "; cin >> p[i].inform;
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| � |   �������   | ���� | ����. | ���. | ���. | ���. | ������� ��� |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(13) << right << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(6) << right << specStr[p[i].spec]
			<< "| " << setw(4) << right << p[i].physics << " "
			<< "| " << setw(4) << right << p[i].math << " "
			<< "| " << setw(4) << right << p[i].inform << " "
			<< "| " << setw(14) << right << (p[i].physics + p[i].math + p[i].inform) / 3 << "|";
		cout << endl;
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if (((p[i1].math + p[i1].physics + p[i1].inform) / 3. < (p[i1 + 1].math + p[i1 + 1].physics + p[i1 + 1].inform) / 3.)
				||
				((p[i1].math + p[i1].physics + p[i1].inform) / 3. == (p[i1 + 1].math + p[i1 + 1].physics + p[i1 + 1].inform) / 3. &&
					p[i1].spec < p[i1 + 1].spec)
				||
				((p[i1].math + p[i1].physics + p[i1].inform) / 3. == (p[i1 + 1].math + p[i1 + 1].physics + p[i1 + 1].inform) / 3. &&
					p[i1].spec == p[i1 + 1].spec &&
					p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const int avgGrade) {
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		int studentAvgGrade = (p[m].math + p[m].physics + p[m].inform) / 3.0;

		if (p[m].prizv.compare(0, prizv.length(), prizv) == 0 && p[m].spec == spec && studentAvgGrade == avgGrade)
			return m;

		if (p[m].prizv.compare(0, prizv.length(), prizv) < 0 || (p[m].prizv.compare(0, prizv.length(), prizv) == 0 && p[m].spec < spec) || (p[m].prizv.compare(0, prizv.length(), prizv) == 0 && p[m].spec == spec && studentAvgGrade < avgGrade))
			L = m + 1;
		else
			R = m - 1;
	} while (L <= R);

	return -1;
}

int* IndexSort(Student* p, const int N) {
	int* I = new int[N];
	for (int i = 0; i < N; i++)
		I[i] = i;

	int i, j, value;
	for (i = 1; i < N; i++) {
		value = I[i];
		for (j = i - 1; j >= 0 &&
			(((p[I[j]].math + p[I[j]].physics + p[I[j]].inform) / 3. < (p[value].math + p[value].physics + p[value].inform) / 3.) ||
				(((p[I[j]].math + p[I[j]].physics + p[I[j]].inform) / 3. == (p[value].math + p[value].physics + p[value].inform) / 3.) &&
					(p[I[j]].spec < p[value].spec)) ||
				(((p[I[j]].math + p[I[j]].physics + p[I[j]].inform) / 3. == (p[value].math + p[value].physics + p[value].inform) / 3.) &&
					(p[I[j]].spec == p[value].spec) && (p[I[j]].prizv > p[value].prizv))); j--) {
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| � |   �������   | ���� | ����. | ���. | ���. | ���. |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(13) << right << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(6) << right << specStr[p[i].spec]
			<< "| " << setw(4) << right << p[I[i]].physics << " "
			<< "| " << setw(4) << right << p[I[i]].math << " "
			<< "| " << setw(4) << right << p[I[i]].inform << " " << "|";
		cout << endl;
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}



