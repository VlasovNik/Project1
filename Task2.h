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
	vector<vector<EdgeT*>> matrixE; //»сходна€ матрица смежности, чтобы заполнить дополнительную
	int** matrix;//дополнительна€ матрица смежности, с весами ребер
	int size = 0, vert;
	int* distance;


	int* Dijkstra(int** GR, int st)
	{
		int* distance = new int[size], count, index, i, u;
		bool* visited = new bool[size];
		//первоначальное заполнение
		for (i = 0; i < size; i++)
		{
			distance[i] = INT_MAX;//заполн€ем бесконечностью 
			visited[i] = false;//помечаем, что вершины не посещали
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
		// ¬осстановление пути
		int* ver = new int[size+1]; // массив посещенных вершин
		int end = e; // индекс конечной вершины
		ver[1] = end; // начальный элемент - конечна€ вершина
		int k = 1; // индекс предыдущей вершины
		int weight = distance[end]; // вес конечной вершины

		while (end != vert) // пока не дошли до начальной вершины
		{
			for (int i = 0; i < size; i++) // просматриваем все вершины
				if (matrix[i][end] != 0)   // если св€зь есть
				{
					int temp = weight - matrix[i][end]; // определ€ем вес пути из предыдущей вершины
					if (temp == distance[i]) // если вес совпал с рассчитанным
					{                 // значит из этой вершины и был переход
						weight = temp; // сохран€ем новый вес
						end = i;       // сохран€ем предыдущую вершину
						ver[k] = i; // и записываем ее в массив
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
			graph->ToMatrixGraph();//≈сли не матрична€ форма, то преобразуем.
		}
		this->graph = graph;
		this->size = graph->getSize();
		this->vert = vert;

		matrix = new int* [size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
		}

		matrixE = graph->data->getMatrix();//заполн€ем матрицу смежности
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
			graph->ToMatrixGraph();//≈сли не матрична€ форма, то преобразуем.
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
			//—оздаЄм объект пути
			Path path = Path(i);
			path.To = vert;
			path.Distance = distance[i];
			//«аписываем путь, если он есть
			if (distance[i] != INT_MAX) 
			{
				int* way = getPath(i);
				copy(&way[1], &way[way[0]], back_inserter(path.Vertexes));
			}
			//—охран€ем объект пути в векторе
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