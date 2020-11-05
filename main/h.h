#pragma once

#include "Process.h"

#define LIMIT 5

template <class T>
class Node
{
private:
	T data;
	int priority;
public:
	Node() { this->left = nullptr; this->rigth = nullptr; this->priority = 1; }
	Node(T data, int priority) { this->left = nullptr; this->rigth = nullptr; this->priority = priority; this->data = data; }
	~Node() {};

	Node* left;
	Node* rigth;

	T GetData() { return this->data; }
	int GetPriority() { return this->priority; }

	void SetData(T data) { this->data = data; }
	void SetPriority(int priority) { this->priority = priority; }
};

template <class T>
class List
{
private:
	Node<T>* Head;
	Node<T>* Tail;
public:
	List() { this->Head = nullptr; this->Tail = nullptr; };
	~List() 
	{
		Node<T>* current = this->Tail;
		while (current->left != nullptr)
		{
			current = current->left;
			delete current->rigth;
		}
		delete this->Head;
	};

	void push(T data, int priority = 1)
	{
		if (this->Head == nullptr) //Сейчас в листе 0 элементов
		{
			this->Head = new Node<T>(data, priority);
			this->Tail = this->Head;
			return;
		}
		if (this->Head == this->Tail) //Сейчас в листе 1 элемент
		{
			if (priority < this->Head->GetPriority())
			{
				this->Tail = new Node<T>(data, priority);
				this->Head->rigth = this->Tail;
				this->Tail->left = this->Head;
			}
			else
			{
				this->Head = new Node<T>(data, priority);
				this->Head->rigth = this->Tail;
				this->Tail->left = this->Head;
			}
			return;
		}
		//В листе больше 1 элемента
		Node<T>* current = this->Head;
		while (priority < current->GetPriority() && current->rigth != nullptr)
			current = current->rigth;
		if (current == this->Head)
		{
			if (priority < this->Head->GetPriority())
			{
				Node<T>* helper = this->Head->rigth;
				this->Head->rigth = new Node<T>(data, priority);
				this->Head->rigth->left = this->Head;
				this->Head->rigth->rigth = helper;
				helper->left = this->Head->rigth;
			}
			else
			{
				Node<T>* helper = this->Head;
				this->Head = new Node<T>(data, priority);
				this->Head->rigth = helper;
				helper->left = this->Head;
			}
			return;
		}
		if (current == this->Tail)
		{
			if (priority < this->Tail->GetPriority())
			{
				Node<T>* helper = this->Tail;
				this->Tail = new Node<T>(data, priority);
				this->Tail->left = helper;
				helper->rigth = this->Tail;
			}
			else
			{
				Node<T>* helper = this->Tail->left;
				this->Tail->left = new Node<T>(data, priority);
				this->Tail->left->left = helper;
				this->Tail->left->rigth = this->Tail;
				helper->rigth = this->Tail->left;
			}
			return;
		}

		Node<T>* helper = current->left;
		current->left = new Node<T>(data, priority);
		current->left->left = helper;
		current->left->rigth = current;
		helper->rigth = current->left;
	}
	void print()
	{
		Node<T>* current = this->Tail;
		int i = 0;
		while (current->left != nullptr)
		{
			cout << ++i << ".\t====\t" << current->GetData() << "\t====\t" << current->GetPriority() << endl;
			current = current->left;
		}
		cout << ++i << ".\t====\t" << current->GetData() << "\t====\t" << current->GetPriority() << endl;
	}
	void print_priority(int priority)
	{
		int i = 0;
		Node<T>* current = this->Tail;
		while (current->left != nullptr && current->GetPriority() != priority) current = current->left;
		while (current->GetPriority() == priority)
		{
			cout << ++i << ".\t====\t" << current->GetData() << "\t====\t" << current->GetPriority() << endl;
			if (current->left != nullptr)current = current->left;
			else return;
		}
	}
	void change_priority()
	{
		this->print();
		cout << "\n\n==============\n\n";

		int alfa = 1, new_priority = 1;

		do
		{
			if (alfa <= 0 || alfa > this->size()) cout << "Введите число от 1 до " << this->size();
			cout << "\n\nКакому элементу вы хотите изменить приоритет(введите его номер в списке)\n";
			cin >> alfa;
		} while (alfa <= 0 || alfa > this->size());

		do
		{
			if (new_priority <= 0 || new_priority > LIMIT) cout << "Введите число от 1 до " << LIMIT;
			cout << "\n\nКакой приоритет присвоить этому числу\n";
			cin >> new_priority;
		} while (new_priority <= 0 || new_priority > LIMIT);

		Node<T>* current = this->Tail;
		for (int i = 0; i < alfa - 1; i++) 
			current = current->left;
		if (current->GetPriority() >= new_priority) alfa = 1;//to rigth
		else alfa = 0; // to left

		//deleting
		if (current == this->Head)
		{
			this->Head = this->Head->rigth;
			this->Head->left = nullptr;
		}
		else if (current == this->Tail)
		{
			this->Tail = this->Tail->left;
			this->Tail->rigth = nullptr;
		}
		else
		{
			current->left->rigth = current->rigth;
			current->rigth->left = current->left;
		}
		this->push(current->GetData(), new_priority);
		cout << "\n\n==============\n\n";
		this->print();
	}
	int size()
	{
		int counter = 0;
		Node<T>* current = this->Head;
		if (current == nullptr) return 0;
		if (this->Head == this->Tail) return 1;
		while (current->rigth != nullptr)
		{
			counter++;
			current = current->rigth;
		}
		return counter + 1;
	}
};