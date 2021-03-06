﻿//Задачи для выполнения на ЭВМ имеют различные приоритеты,
//задаваемые цифрами от 1 до 5 (5–высший приоритет).
//Для каждого приоритета образуется отдельная очередь.
//Приоритет задач может меняться.
//При повышении приоритета задание помещается в конец другой очереди,
//а при понижении – в начало.Составить программу, обеспечивающую:
//	a) выдачу общей очереди; 
//	б) выдачу очереди заданного приоритета; 
//	в) перестройку очередей при изменении приоритета.

#include "h.h"
#include "Process.h"
#include <functional>

void from_file(List<Process>& list)
{
	fstream f;
	int priority = 0;
	Process pr;
	f.open("file.txt");
	if (!f.is_open()) return;
	while (!f.eof())
	{
		f >> pr >> priority;
		list.push(pr, priority);
	}
	f.close();
}

void from_hand(List<Process>& list)
{
	int priority = 3;
	int runtime = 0;
	string name = "Std_name";

	function<int(string)> f = [](string a)
	{
		int n = 1;
		do
		{
			if (n <= 0) cout << "Введите значение больше 0";
			cout << "\n\n" << a << "\n\n";
			cin >> n;
		} while (n <= 0);
		return n;
	};

	int n = f("Введите число процессов");

	for (int i = 0; i < n; i++)
	{
		cout << "Введите название процесса\n";
		cin >> name;
		runtime = f("Введите время выполнения процесса");
		do
		{
			if (priority <= 0 || priority > LIMIT) cout << "Введите значение больше 0 и меньше " << LIMIT;
			cout << "\n\n" << "Введите приоритет для этого процесса" << "\n\n";
			cin >> priority;
		} while (priority <= 0 || priority > LIMIT);
		list.push(Process(name, runtime), priority);
		system("cls");
	}

}

int main()
{
	setlocale(LC_ALL, "rus");
	List<Process> list;

	/*from_hand(list);*/

	list.push(Process("a", 5), 2);
	list.push(Process("b", 4), 4);
	list.push(Process("d", 11), 2);
	list.push(Process("e", 2), 5);
	list.push(Process("f", 40), 5);
	list.push(Process("g", 123), 3);
	list.push(Process("h", 61), 4);
	list.push(Process("i", 8), 5);
	list.push(Process("j", 9), 4);
	list.push(Process("k", 10), 1);
	list.push(Process("t", 21), 2);

	from_file(list);

	int choose = 0;
	int p = 1;

	while (1)
	{
		system("cls");

		do
		{
			if (choose < 0 || choose > 4) 
			{
				system("cls");
				cout << "Введите корректное значение";
			}
			cout << "\n\nВыберите действие\n\n";
			cout << "0 - выйти\n";
			cout << "1 - вывести все процессы\n";
			cout << "2 - вывести процессы данного приоритета\n";
			cout << "3 - изменить приоритет 1 из процессов\n";
			cout << "4 - выйти с сохранением в файл\n";
			cin >> choose;
		} while (choose < 0 || choose > 4);

		switch (choose)
		{
		case 0:
			return 0;
			break;
		case 1:
			list.print();
			break;
		case 2:
			do
			{
				if (p <= 0 || p > LIMIT) cout << "Введите число от 1 до " << LIMIT;
				cout << "\n\nПроцессы с каким приоритетом вывести\n";
				cin >> p;
			} while (p <= 0 || p > LIMIT);
			list.print_priority(p);
			break;
		case 3:
			list.change_priority();
			break;
		case 4:
			list.in_file();
			return 0;
			break;
		}
		system("pause");
	}
	return 0;
}