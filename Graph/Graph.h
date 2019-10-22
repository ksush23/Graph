#pragma once
#include <fstream>
#include <iostream>

using namespace std;

class Graph
{
protected:
	int n, m;
public:
	Graph() : n(0), m(0) {}
	virtual ~Graph() = 0;
	virtual bool init(int, int) = 0;
	virtual bool add(int v1, int v2) = 0;
	virtual int* proces() = 0;
};
class GraphMatrix : public Graph
{
protected:
	int **E;
	bool is_tree();
	int* bfs(int, int&);
	int bfs(int);
public:
	GraphMatrix();
	~GraphMatrix();
	bool init(int, int);
	bool add(int v1, int v2);
	int* proces();
	void output();
};
class GraphStruct : public Graph
{
protected:
	int* A;
	int** B;
	bool is_tree();
	int* bfs(int, int&);
	int bfs(int u);
public:
	GraphStruct();
	~GraphStruct();
	bool init(int, int);
	bool add(int v1, int v2);
	int* proces();
	void output();
};