#include "Header.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void operator >> (istream& f, GraphMatrix& obj)
{
	ifstream fin;
	cout << "Enter a filepath you want to have your information from: " << endl;
	string file;
	getline(cin, file);
	fin.open(file);

	while (!fin)
	{
		cout << "Enter a filepath you want to have your information from: " << endl;
		cin.get();
		getline(cin, file);
		fin.open(file);
	}
	double clock_start = clock();
	int v, e, v1, v2;
	fin >> v >> e;
	obj.init(v, e);

	for (int i = 0; i < e; i++)
	{
		fin >> v1 >> v2;
		obj.add(v1, v2);
	}
	double clock_end = clock();

	cout << "Time of procedure of entering is: " << (clock_end - clock_start) / 1000 << endl;

	fin.close();
}

void operator << (ostream& f, GraphMatrix& obj)
{
	int* arr = nullptr;
	double clock_start = clock();
	arr = obj.proces();
	double clock_end = clock();
	cout << "Time of procedure of procesing is: " << (clock_end - clock_start) / 1000 << ' ' << endl;
	if (arr[0] == -1)
	{
		cout << "This is not a tree" << endl;
		return;
	}

	cout << "Enter a filepath you want to have results in: " << endl;
	string file;
	cin >> file;

	ofstream fout(file);
	while (!fout)
	{
		cout << "Enter a filepath you want to have your results in: " << endl;
		cin.get();
		getline(cin, file);
		fout.open(file);
	}

	for (int i = 0; i < 10; i++)
		cout << arr[i] << ' ';

	fout << arr[0] << endl;
	for (int i = 1; arr[i + 1] != -2; i++)
		if (arr[0] == arr[i])
			fout << i - 1 << ' ';
	delete[]arr;
}

void operator >> (istream&f, GraphStruct& obj)
{
	ifstream fin;
	cout << "Enter a filepath you want to have your information from: " << endl;
	string file;
	cin >> file;
	//getline(cin, file);
	fin.open(file);

	while (!fin)
	{
		cout << "Enter a filepath you want to have your information from: " << endl;
		cin.get();
		getline(cin, file);
		fin.open(file);
	}

	int v, e, v1, v2;
	fin >> v >> e;
	obj.init(v, e);

	double clock_start = clock();
	for (int i = 0; i < e; i++)
	{
		fin >> v1 >> v2;
		obj.add(v1, v2);
	}
	double clock_end = clock();

	cout << "Time of procedure of entering is: " << (clock_end - clock_start) / 1000 << endl;

	fin.close();
}

void operator << (ostream& f, GraphStruct& obj)
{
	int* arr = nullptr;
	double clock_start = clock();
	arr = obj.proces();
	double clock_end = clock();
	cout << "Time of procedure of procesing is: " << (clock_end - clock_start) / 1000 << endl;
	if (arr[0] == -1)
	{
		cout << "This is not a tree" << endl;
		return;
	}

	cout << "Enter a filepath you want to have results in: " << endl;
	string file;
	cin >> file;

	ofstream fout(file);
	while (!fout)
	{
		cout << "Enter a filepath you want to have your results in: " << endl;
		cin.get();
		getline(cin, file);
		fout.open(file);
	}

	fout << arr[0] << endl;
	for (int i = 1; arr[i + 1] != -2; i++)
		if (arr[0] == arr[i])
			fout << i - 1 << ' ';
	delete[]arr;
}
