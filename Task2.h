#pragma once
#include "Graph.h"
#include <stack>
using namespace std;
typedef Graph < Vertex<string, int>, Edge< Vertex<string, int>, int, int>> myGraph;
typedef Edge < Vertex<string, int>, int, int> myEdge;

template <class VertexT, class EdgeT>
class Task2
{
private:
	class Path
	{
	public:
		int From=-1;
		int To=-1;
		int Distance=-1;
		vector<int> Vertexes;
		bool IsExist = true;
		Path(int from)
		{
			From = from;
			Vertexes = vector<int>();
		}
	};
	vector<Path> Paths = vector<Path>();


	Graph<VertexT, EdgeT>* graph;
	vector<vector<EdgeT*>> matrixE; //�������� ������� ���������, ����� ��������� ��������������
	int** matrix;//�������������� ������� ���������, � ������ �����
	int size = 0, vert;
	int* distance;


	int* Dijkstra(int** GR, int st)
	{
		int* distance = new int[size], count, index, i, u;
		bool* visited = new bool[size];
		//�������������� ����������
		for (i = 0; i < size; i++)
		{
			distance[i] = INT_MAX;//��������� �������������� 
			visited[i] = false;//��������, ��� ������� �� ��������
		}
		distance[st] = 0;
		for (count = 0; count < size - 1; count++)
		{
			int min = INT_MAX;
			for (i = 0; i < size; i++)
				if (!visited[i] && distance[i] <= min)
				{
					min = distance[i];
					index = i;
				}
			u = index;
			visited[u] = true;
			for (i = 0; i < size; i++) {
				if (!visited[i] && GR[u][i] && distance[u] != INT_MAX &&
					distance[u] + GR[u][i] < distance[i])
					distance[i] = distance[u] + GR[u][i];
			}
		}
		delete[] visited;

		return distance;
	}

	int* getPath(int e)
	{
		// �������������� ����
		int* ver = new int[size+1]; // ������ ���������� ������
		int end = e; // ������ �������� �������
		ver[1] = end; // ��������� ������� - �������� �������
		int k = 1; // ������ ���������� �������
		int weight = distance[end]; // ��� �������� �������

		while (end != vert) // ���� �� ����� �� ��������� �������
		{
			for (int i = 0; i < size; i++) // ������������� ��� �������
				if (matrix[i][end] != 0)   // ���� ����� ����
				{
					int temp = weight - matrix[i][end]; // ���������� ��� ���� �� ���������� �������
					if (temp == distance[i]) // ���� ��� ������ � ������������
					{                 // ������ �� ���� ������� � ��� �������
						weight = temp; // ��������� ����� ���
						end = i;       // ��������� ���������� �������
						ver[k] = i; // � ���������� �� � ������
						k++;
					}
				}
		}
		ver[0] = k;
		return ver;
	}

	void transponir(int** matr)
	{
		int i, j;
		int s;
		for (i = 0; i < size; i++)
			for (j = i + 1; j < size; j++) {
				s = matr[i][j];
				matr[i][j] = matr[j][i];
				matr[j][i] = s;
			}
	}

public:
	Task2(Graph<VertexT, EdgeT>* graph, int vert)
	{
		if (!graph->Dense()) {
			graph->ToMatrixGraph();//���� �� ��������� �����, �� �����������.
		}
		this->graph = graph;
		this->size = graph->getSize();
		this->vert = vert;

		matrix = new int* [size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
		}

		matrixE = graph->data->getMatrix();//��������� ������� ���������
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (matrixE[i][j] != NULL) {
					matrix[i][j] = matrixE[i][j]->getWeight();
				}
				else {
					matrix[i][j] = 0;
				}
			}
		}

		transponir(this->matrix);
	}

	void set(Graph<VertexT, EdgeT>* graph)
	{
		if (!graph->Dense()) {
			graph->ToMatrixGraph();//���� �� ��������� �����, �� �����������.
		}
		this->graph = graph;
		this->size = graph->getSize();

		matrix = new int* [size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
		}

		matrixE = graph->data->getMatrix();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (matrixE[i][j] != NULL) {
					matrix[i][j] = matrixE[i][j]->getWeight();
				}
				else {
					matrix[i][j] = 0;
				}
			}
		}

		transponir(this->matrix);
	}

	void Restart()
	{
		Paths.clear();
		distance = Dijkstra(this->matrix, this->vert);
		for (int i = 0; i < graph->getSize(); i++) 
		{
			//������ ������ ����
			Path path = Path(i);
			path.To = vert;
			path.Distance = distance[i];
			//���������� ����, ���� �� ����
			if (distance[i] != INT_MAX) 
			{
				int* way = getPath(i);
				copy(&way[1], &way[way[0]], back_inserter(path.Vertexes));
			}
			//��������� ������ ���� � �������
			Paths.push_back(path);			
		}
	}
	
	Path Result(int v2)
	{

		for (auto it = Paths.begin(); it != Paths.end(); it++)
		{
			if ((*it).From == v2)
				return (*it);
		}
		throw - 1;
	}
};