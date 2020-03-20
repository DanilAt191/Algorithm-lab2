#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <Windows.h>
#define garbage_collector() cin.ignore(cin.rdbuf()->in_avail())

using namespace std;

struct Date {
	short day;
	short month;
	short year;
	bool isCorrect();
};

bool Date::isCorrect()
{
	bool result = false;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		if ((day <= 31) && (day > 0))
			result = true;
		break;
	}

	case 4:
	case 6:
	case 9:
	case 11:
	{
		if ((day <= 30) && (day > 0))
			result = true;
		break;
	}

	case 2:
	{
		if (year % 4 != 0)
		{
			if ((day <= 28) && (day > 0))
				result = true;
		}
		else
			if (year % 400 == 0)
			{
				if ((day <= 29) && (day > 0))
					result = true;
			}
			else
				if ((year % 100 == 0) && (year % 400 != 0))
				{
					if ((day == 28) && (day > 0))
						result = true;
				}
				else
					if ((year % 4 == 0) && (year % 100 != 0))
						if ((day <= 29) && (day > 0))
							result = true;
		break;
	}

	default:
		result = false;
	}

	return result;
}

struct Patient
{
	char FirstName[15],
		SecondName[15],
		LastName[15],
		Sex[7],
		Nationality[56],
		Address[255],
		Hospital[4],
		MedCard[10],
		Diagnosis[255],
		Number[56],
		Branch[25],
		Blood[4];

	int Age,
		Height,
		Weight;

	Date Birthday;
};

Patient* InitArray(int Dimension);
Patient InitPerson();
void DisplayArray(Patient* Massive, int Dimaension);
void DisplayChoise(Patient*, int, char*, int, int);
void DisplayPerson(Patient);
void SortFirstName(Patient*, int);
int& CheckCorectDigitValue(int&);

void main(int argc, char* argv)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL,"");

	int Dimension;
	char SexTag[7];
	int LowAge, UpperAge;
	bool begin = true;
tryagain:
	Patient* MassiveStruct = nullptr;
	do
	{
		cout << "\nВведите кол-во пациентов:  ";
		do {
			cin >> Dimension;
			if (cin.fail())
			{
				cout << "[!]Ошибка ввода! Попробуйте еще раз" << endl;
				cin.clear();
				cin.ignore(32222, '\n');
			}
			else
				break;
		} while (true);
		MassiveStruct = InitArray(Dimension);
		if (MassiveStruct == nullptr)
		{
			cout << "\n[!]Dynamic array don't exist!\n";

			do {
				cout << "[!]Введите '+' для того чтобы повторить попытку или нажмите '-' чтобы выйти из програмы... ";
				char symbol;
				symbol = getchar();
				(symbol == '+') ? begin == true : begin == false;
				if (symbol == '+')
					goto tryagain;
				exit(777);

			} while (!begin);
		}


	} while (begin != true);

	cout << "\nВся информация: " << endl;
	DisplayArray(MassiveStruct, Dimension);

	cout << "\nУточните пол: ";
	do {
		cin >> SexTag;
	} while (isdigit((char)SexTag[1]));
	cout << "\nВведите границу возраста: ";
	do
	{
		cin >> LowAge >> UpperAge;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32222, '\n');
		}
		else
			break;
	} while (true);

	cout << "\nОтсортированный список выбранных людей: " << endl;
	SortFirstName(MassiveStruct, Dimension);
	DisplayArray(MassiveStruct, Dimension);

	delete MassiveStruct;
}
Patient InitPerson()
{
	Patient Man;

	cout << "\nВведите фамилию: ";
	garbage_collector();
	cin.getline(Man.SecondName, 255);

	cout << "Введите имя: ";
	garbage_collector();
	cin.getline(Man.FirstName, 255);

	cout << "Введите отчество: ";
	garbage_collector();
	cin.getline(Man.LastName, 255);

	cout << "Введите возраст: ";
	garbage_collector();
	cin >> Man.Age;

	cout << "Введите пол: ";
	garbage_collector();
	cin.getline(Man.Sex, 255);

	cout << "Введите национальность: ";
	garbage_collector();
	cin.getline(Man.Nationality, 255);

	cout << "Введите рост: ";
	garbage_collector();
	cin >> Man.Height;

	cout << "Введите вес: ";
	garbage_collector();
	cin >> Man.Weight;

	do {
		cout << "Введите дату рождения: ";
		garbage_collector();
		cin >> Man.Birthday.year >> Man.Birthday.month >> Man.Birthday.day;
	} while (!Man.Birthday.isCorrect());

	cout << "Введите номер телефона: ";
	garbage_collector();
	cin.getline(Man.Number, 56);

	cout << "Введите адрес: ";
	garbage_collector();
	cin.getline(Man.Address, 255);

	cout << "Введите номер больницы: ";
	garbage_collector();
	cin.getline(Man.Hospital, 4);

	cout << "Введите отделение: ";
	garbage_collector();
	cin.getline(Man.Branch, 25);

	cout << "Введите номер мед карты: ";
	garbage_collector();
	cin.getline(Man.MedCard, 10);

	cout << "Введите группу крови: ";
	garbage_collector();
	cin >> Man.Blood;

	cout << "Введите диагноз: ";
	garbage_collector();
	cin.getline(Man.Diagnosis, 256);

	return Man;
}

Patient* InitArray(int Dimension)
{
	Patient* Massive = new Patient[Dimension];
	if (Massive == nullptr)
		return nullptr;
	for (size_t i = 0; i < Dimension; i++)
	{
		printf("\nВведите информацию %d-го человека: ", i + 1);
		Massive[i] = InitPerson();
	}
	return Massive;
}

void DisplayArray(Patient* Massive, int Dimension)
{
	for (size_t i = 0; i < Dimension; i++) { DisplayPerson(Massive[i]); }
}

void DisplayChoise(Patient* Massive, int Dimension, char* SexTag, int LowAge, int UpperAge)
{
	for (size_t i = 0; i < Dimension; i++)
	{
		if (
			strcmp(Massive[i].Sex, SexTag) == 0 &&
			Massive[i].Age <= UpperAge &&
			Massive[i].Age >= LowAge
			)
		{
			DisplayPerson(Massive[i]);
		}
	}
}

void DisplayPerson(Patient Man)
{
	cout << "ФИО: " << Man.FirstName << " " << Man.SecondName << " " << Man.LastName << endl;
	cout << "Возраст: " << Man.Age << endl;
	cout << "Пол: " << Man.Sex << endl;
	cout << "Рост: " << Man.Height << endl;
	cout << "Вес: " << Man.Weight << endl;
	cout << "Дата рождения: " << Man.Birthday.year << "." << Man.Birthday.month << "." << Man.Birthday.day << endl;
	cout << "Телефон: " << Man.Number << endl;
	cout << "Адрес: " << Man.Address << endl;
	cout << "Номер больницы: " << Man.Hospital << endl;
	cout << "Отделение: " << Man.Branch << endl;
	cout << "Номер мед карты: " << Man.MedCard << endl;
	cout << "Группа крови: " << Man.Blood << endl;
	cout << "Диагноз: " << Man.Diagnosis << "\n\n";
}
void SortFirstName(Patient* Massive, int Dimension)
{
	Patient Temp;
	for (size_t i = 0; i <= Dimension; i++)
	{
		for (size_t q = Dimension - 1; q > i; q--)
		{
			if (strcmp(Massive[q].FirstName, Massive[q - 1].FirstName) < 0)

				Temp = Massive[q];
			Massive[q] = Massive[q - 1];
			Massive[q - 1] = Temp;

		}
	}
}

int& CheckCorectDigitValue(int& value)
{
	bool flag = false;
	do {
		if (flag) {
			cout << "[!]Попробуйте еще раз";
		}flag = false;
		cin >> value;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32222, '\n');
		}
		else
		{
			return value;
		}
	} while (true);
}
