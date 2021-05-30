#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef int Info;
struct Elem
{
	Elem* link;
	string info;
};

void enqueue(Elem*& first, Elem*& last, string value);
string dequeue(Elem*& first, Elem*& last);
void readTXT(Elem*& first, Elem*& last, Elem*& start, Elem*& end);
void connect(Elem* first, Elem* start, Elem*& start_new, Elem*& end_new);
void print(Elem* L);

int main()
{
	Elem* first = NULL,
		* last = NULL;
	Elem* start = NULL,
		* end = NULL;
	Elem* new_start = NULL,
		* new_end = NULL;
	readTXT(first, last, start, end);
	cout << "First string: ";
	print(first);
	cout << endl;
	cout << "Second string: ";
	print(start);
	cout << endl;
	connect(first, start, new_start, new_end);
	cout << "Connected queue: ";
	while (new_start != NULL)
		cout << dequeue(new_start, new_end) << " ";
	cout << endl;

	return 0;
}
void enqueue(Elem*& first, Elem*& last, string value)
{
	Elem* tmp = new Elem;
	tmp->info = value;
	tmp->link = NULL;
	if (last != NULL)
		last->link = tmp;
	last = tmp;
	if (first == NULL)
		first = tmp;
}

string dequeue(Elem*& first, Elem*& last)
{
	Elem* tmp = first->link;
	string value = first->info;
	delete first;
	first = tmp;
	if (first == NULL)
		last = NULL;
	return value;
}

void readTXT(Elem*& first, Elem*& last, Elem*& start, Elem*& end)
{
	ifstream f("symbols.txt"); // відкриття потоку зчитування файла
	string symbol;
	string str;
	int i = 1;
	while (!f.eof()) { // всі інші цифри
		getline(f, str);
		char* s = new char[str.size() + 1];
		strcpy(s, str.c_str());
		char* p = strtok(s, " ,=-.");
		while (p != NULL) {
			symbol = p;
			if (i == 1) {
				enqueue(first, last, symbol);
			}
			else if (i == 2) {
				enqueue(start, end, symbol);
			}
			p = strtok(NULL, " ,=-.");
		}
		i++;
	}
}

void print(Elem* L)
{
	while (L != NULL)
	{
		cout << L->info << " ";
		L = L->link;
	}
	cout << endl;
}

void connect(Elem* first, Elem* start, Elem*& start_new, Elem*& end_new) {
	while (first != NULL) {
		enqueue(start_new, end_new, first->info);
		first = first->link;
	}
	while (start != NULL) {
		enqueue(start_new, end_new, start->info);
		start = start->link;
	}
}