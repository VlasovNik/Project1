#pragma once
#include "Graph.h"
#include <stack>
#include "Edge.h"
#include "Vertex.h"
using namespace std;
typedef Graph < Vertex<string, int>, Edge< Vertex<string, int>, int, int>> myGraph;
typedef Edge < Vertex<string, int>, int, int> myEdge;

template <class VertexT, class EdgeT>
class Task1
{
private:
	Graph<VertexT, EdgeT>* graph;
	vector<vector<EdgeT*>> matrixE; //�������� ������� ���������, ����� ��������� ��������������
	bool** matrix;//�������������� ������� ���������, ������ 1/0
	int size = 0;
	vector<int> color; // ����� ������
	bool isBipartite; // ����, ����������� �������� �� ���� ����������
	void dfs(int v); // ����� ��� ������ ����� � �������
	vector<int> getNeighbours(int v);
public:
	Task1(Graph<VertexT, EdgeT>* graph); // �����������
	Task1(const Task1& T); // ����������� �����������
	~Task1(); // ����������
	void set(Graph<VertexT, EdgeT>* graph); // ��������� ������ ������ � ������ � ��������� ������� ������
	void restart(); // �������� ��������� ������� ������ ��� �����
	vector<int> result(); // ���������� ��������� ������� ������
};

template<class VertexT, class EdgeT>
inline Task1<VertexT, EdgeT>::Task1(Graph<VertexT, EdgeT>* graph)
{
	if (!graph->Dense()) {
		graph->ToMatrixGraph();//���� �� ��������� �����, �� �����������.
	}
	this->graph = graph;
	this->size = graph->getSize();
	matrix = new bool* [size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new bool[size];
	}

	matrixE = graph->data->getMatrix();//��������� ������� ��������� 1/0
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrixE[i][j] != NULL) {
				matrix[i][j] = 1;
			}
			else {
				matrix[i][j] = 0;
			}
		}
	}
	color.resize(size, -1);
	isBipartite = true;
	set(graph);
}

template<class VertexT, class EdgeT>
inline Task1<VertexT, EdgeT>::Task1(const Task1& T)
{
	this->graph = T.graph;
	this->color = T.color;
	this->isBipartite = T.isBipartite;
}

template<class VertexT, class EdgeT>
inline Task1<VertexT, EdgeT>::~Task1()
{
}
template<class VertexT, class EdgeT>
inline void Task1<VertexT, EdgeT>::set(Graph<VertexT, EdgeT>* graph)
{
	this->graph = graph;
	restart();
}

template<class VertexT, class EdgeT>
inline void Task1<VertexT, EdgeT>::restart()
{
	int size = graph->getSize();
	color.assign(size, -1);
	isBipartite = true;

	for (int i = 0; i < size && isBipartite; i++)
		if (color[i] == -1)
			dfs(i);
	//result();
}

template<class VertexT, class EdgeT>
inline vector<int> Task1<VertexT, EdgeT>::result()
{
	if (isBipartite)
		return color;
	else
		return vector<int>();
}

template<class VertexT, class EdgeT>
void Task1<VertexT, EdgeT>::dfs(int v)
{
	vector<int> neighbours = getNeighbours(v);
	for (int i = 0; i < neighbours.size(); i++)
	{
		int u = neighbours[i];
		if (color[u] == -1)
		{
			color[u] = 1 - color[v];
			dfs(u);
		}
		else if (color[u] == color[v])
			isBipartite = false;
	}
}

template<class VertexT, class EdgeT>
inline vector<int> Task1<VertexT, EdgeT>::getNeighbours(int v)
{
	vector<int> neighbours;
	for (int i = 0; i < size; i++)
		if (matrix[v][i] != 0)
			neighbours.push_back(i);
	return neighbours;
}
