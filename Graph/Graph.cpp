#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>
#include"Graph.h"

using namespace std;

Graph::~Graph(){}

GraphMatrix::GraphMatrix() : E(nullptr)
{
}

GraphMatrix::~GraphMatrix()
{
	if (E != nullptr)
	{
		for (int i = 0; i < n; i++)
			delete[]E[i];
		delete[]E;
	}
}

bool GraphMatrix::init(int  n0, int m0)
{
	n = n0;
	m = m0;
	E = new int*[n];
	for (int i = 0; i < n; i++)
	{
		E[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			E[i][j] = 0;
	return 1;
}

bool GraphMatrix::add(int v1, int v2)
{
	E[v1][v2] = 1;
	E[v2][v1] = 1;
	return 1;
}

int* GraphMatrix::proces()
{
	int* max_dist = new int[n + 2];
	if (is_tree())
	{
		int max = 0;
		for (int i = 0; i < n; i++)
		{
			max = bfs(i);
			max_dist[i + 1] = max;
		}
		max = 0;
		for (int i = 0; i < n; i++)
			if (max_dist[i] > max)
				max = max_dist[i];
		max_dist[0] = max;
		max_dist[n + 1] = -2;
	}
	else
	{
		max_dist[0] = -1;
		return max_dist;
	}
	return max_dist;
}

void GraphMatrix::output()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << E[i][j] << ' ';
		}
		cout << endl;
	}
}

bool GraphMatrix::is_tree()
{
	if (n - 1 != m)
		return 0;

	int* arr = nullptr;
	for (int i = 0; i < n; i++)
	{
		int k = 0;
		arr = bfs(i, k);
		int num = 0;
		bool* a = new bool[n];
		for (int i = 0; i <= m; i++)
			a[i] = 0;
		for (int i = 0; i <= m; i++)
		{
			if (arr[i] == -1)
				return 0;
			a[arr[i]] = 1;
		}
		for (int i = 0; i <= m; i++)
			if (a[i] == 0)
				return 0;
		delete[]a;
	}
	return 1;
}

int* GraphMatrix::bfs(int u, int& k)
{
	int* visited = new int[n];
	int* arr = new int[m];
	for (int i = 0; i < n; i++)
		arr[i] = -1;
	for (int i = 0; i < n; i++)
		visited[i] = 0;
	visited[u] = 1;
	queue<int> q;
	q.push(u);
	arr[k] = u;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (!visited[i] && E[u][i])
			{
				k++;
				arr[k] = i;
				visited[i] = 1;
				q.push(i);
			}
		}
	}
	delete[]visited;
	return arr;
}

int GraphMatrix::bfs(int u)
{
	int max = 0;
	int* distances = new int[n];
	for (int i = 0; i < n; i++)
		distances[i] = -1;
	queue<int> q;
	q.push(u);
	distances[u] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (distances[i] == -1 && E[u][i])
			{
				distances[i] = distances[u] + 1;
				q.push(i);
			}
		}
	}
	for (int j = 1; j < n + 1; j++)
		if (distances[j] > max)
			max = distances[j];
	delete[]distances;
	return max;
}

GraphStruct::GraphStruct() : A(nullptr), B(nullptr)
{
}

GraphStruct::~GraphStruct()
{
	if (A != nullptr)
		delete[]A;
	if (B != nullptr)
	{
		for (int i = 0; i < 2; i++)
			delete[]B[i];
		delete[]B;
	}
}

bool GraphStruct::init(int v, int e)
{
	n = v;
	m = e;

	A = new int[n];
	for (int i = 0; i < n; i++)
		A[i] = -1;

	B = new int*[2];
	for (int i = 0; i < 2; i++)
		B[i] = new int[2 * m];

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2 * m; j++)
			B[i][j] = -1;

	return 1;
}

bool GraphStruct::add(int v1, int v2)
{
	int j = 0;
	if (A[v1] == -1)
	{
		for (j; j < 2 * m; j++)
			if (B[0][j] == -1)
			{
				B[0][j] = v2;
				break;
			}

		A[v1] = j;
	}
	else
	{
		j = A[v1];
		int jn = B[1][j];
		int k = j;
		while (jn != -1)
		{
			k = jn;
			jn = B[1][jn];
		}

		j = k;

		for (j; j < 2 * m; j++)
			if (B[0][j] == -1)
			{
				B[0][j] = v2;
				break;
			}
		B[1][k] = j;
	}


	j = 0;
	if (A[v2] == -1)
	{
		for (j; j < 2 * m; j++)
			if (B[0][j] == -1)
			{
				B[0][j] = v1;
				break;
			}

		A[v2] = j;
	}
	else
	{
		j = A[v2];
		int jn = B[1][j];
		int k = j;
		while (jn != -1)
		{
			k = jn;
			jn = B[1][jn];
		}

		j = k;

		for (j; j < 2 * m; j++)
			if (B[0][j] == -1)
			{
				B[0][j] = v1;
				break;
			}
		B[1][k] = j;
	}

	return 1;
}

int* GraphStruct::proces()
{
	int* max_dist = new int[n + 2];
	if (is_tree())
	{
		int max = 0;
		for (int i = 0; i < n; i++)
		{
			max = bfs(i);
			max_dist[i + 1] = max;
		}
		max = 0;
		for (int i = 0; i < n; i++)
			if (max_dist[i] > max)
				max = max_dist[i];
		max_dist[0] = max;
		max_dist[n + 1] = -2;
	}
	else
	{
		max_dist[0] = -1;
		return max_dist;
	}
	return max_dist;
}

void GraphStruct::output()
{
	for (int i = 0; i < n; i++)
		cout << A[i] << ' ';
	cout << endl;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2 * m; j++)
			cout << B[i][j] << ' ';
		cout << endl;
	}
}

bool GraphStruct::is_tree()
{
	if (n - 1 != m)
		return 0;
	for (int i = 0; i < n; i++)
	{
		int* arr = nullptr;
		int k = 0;
		arr = bfs(i, k);
		int num = 0;
		while (num != k - 1)
		{
			for (int i = num; i < k - 1; i++)
			{
				if (arr[i] == arr[i + 1])
					return 0;
			}
			num++;
		}
		delete[]arr;
	}
	return 1;
}

int* GraphStruct::bfs(int u, int& k)
{
	int* visited = new int[n];
	visited[u] = 1;
	queue<int> q;
	q.push(u);
	int* arr = new int[m];
	arr[k] = u;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (A[u] != -1)
		{
			int v = B[0][A[u]];
			k++;
			arr[k] = v;

			if (!visited[v])
			{
				visited[v] = 1;
				q.push(v);
			}
			int j = A[u];
			while (B[1][j] != -1)
			{
				j = B[1][j];
				v = B[0][j];
				if (!visited[v])
				{
					visited[v] = 1;
					q.push(v);
				}
			}
		}
	}
	delete[]visited;
	return arr;
}

int GraphStruct::bfs(int u)
{
	int max = 0;
	int* distances = new int[n];
	for (int i = 0; i < n; i++)
		distances[i] = -1;
	distances[u] = 0;
	queue<int> q;
	q.push(u);

	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (A[u] != -1)
		{
			int v = B[0][A[u]];

			if (distances[v] == -1)
			{
				distances[v] = distances[u] + 1;
				q.push(v);
			}
			int j = A[u];
			while (B[1][j] != -1)
			{
				j = B[1][j];
				v = B[0][j];
				if (distances[v] == -1)
				{
					distances[v] = distances[u] + 1;
					q.push(v);
				}
			}
		}
	}
	for (int j = 1; j < n + 1; j++)
		if (distances[j] > max)
			max = distances[j];
	delete[]distances;
	return max;
}

