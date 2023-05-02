#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include "GraphForm.h"

using namespace std;

string int_to_sting(int h)	//�������������� ����� � ������
{
	stringstream buf;
	buf << h;
	return buf.str();
}

template <class VertexT, class EdgeT>
class Graph {
protected:
	vector<VertexT*> vectV;			//������ �����������

	bool directed;					//���������������� ����a
	bool dense;						//�-���� ��� L-����
	int edgeCount;					//����� ����
	int getIndexFromName(string n);//��������� ������� ������� �� �����������
	int sz;							//������

public:
	GraphForm<EdgeT>* data;			//������ �����
	Graph();						//����������� ������� L-�����
	Graph(int vertexCount, bool directed, bool dense); //����������� � �������� ������ ������, �������� ����������������� � ��������� ����
	Graph(int vertexCount, int edgeCaunt, bool directed, bool dense); //����������� � �������� ������ ������, ��������� ����, �������� ����������������� � ����
	Graph(const Graph<VertexT, EdgeT>& G); //����������� �����������
	~Graph();						//����������
	int getVertexCount();			//���������� ����� ������ � �����
	int getEdgeCount();				//���������� ����� ����� � �����
	bool Dense();					//���������� ����� ������������� �����
	bool Directed();				//���������� ��� �����   
	double K();						//���������� ����������� ������������ �����	
	void ToListGraph();				//����������� ���� � L-����� 
	void ToMatrixGraph();			//����������� ���� � M-�����

	VertexT* InsertV();				//��������� ������� � ����� � ���������� ����� ����������� ����� ��������� ������� 
	bool DeleteV(int index);		//������� ������� �� �����, �������� �������� index 
	bool DeleteV(string n);
	bool DeleteV(VertexT* v);		//������� ������� �� �����, �������� ������� ����������� v 

	EdgeT* InsertE(VertexT* v1, VertexT* v2); //��������� ����� (v1, v2) � �����, ����������� �������, �������� �������� ������������ v1 � v2	
	EdgeT* InsertE(string v1, string v2);
	EdgeT* InsertE(int v1, int v2);
	bool DeleteE(VertexT* v1, VertexT* v2); //������� �����, ����������� �������, �������� �������� ������������ v1 � v2
	bool DeleteE(string v1, string v2);

	EdgeT* getEdge(VertexT* v1, VertexT* v2); //��������� �����

	bool hasEdge(VertexT* v1, VertexT* v2);		//�������� �� ��������������� �����   
	bool hasEdge(int v1, int v2);

	bool write_name_vertex(string v1, string str);//�������� ������ � �������
	bool write_data_vertex(string v1, int d);//�������� ������ � �������
	int read_data_vertex(string v1);//��������� ������ � �������
	void print_graph();				//����� �� �����
	int read_weight_edge(string ve1, string ve2);//��������� ��� �����
	int read_data_edge(string ve1, string ve2);//��������� ������ � �����
	bool write_weight_edge(string ve1, string ve2, int w);//�������� ��� �����
	bool  write_data_edge(string ve1, string ve2, int data);//�������� ������ � �����
	VertexT* getVertexFromName(string n);
	VertexT* getVertex(int index);
	int getSize();


	int getIndex(VertexT* v);

	//�������� ������
	class VertexIterator {
	private:
		Graph<VertexT, EdgeT>* graph; //�������������� ����
		bool end;					  //��������� ���������
		int cur;					  //������� ���������
	public:
		VertexIterator(Graph<VertexT, EdgeT>& g) { graph = &g; }; //�����������

		//���������� ��������, ������������� �� ������ ������� �����
		bool begin()
		{
			if (graph->vectV.size() == 0)
			{
				end = true;
				return false;
			}
			cur = 0;
			end = false;
			return true;
		}

		//������� � ��������� �������
		bool operator++()
		{
			if (end) {
				cur = -1;
				throw "EXC: �������� �� ��������� �����";
			}
			cur++;
			if (graph->vectV.size() > cur) {
				return true;
			}
			else {
				end = true;
				return true;
			}
		}

		//���������� �������� ������ �� �������� �������
		bool toend()
		{
			end = true;
			cur = graph->vectV.size() - 1;
			if (cur < 0)
				return false;
			else
				return true;
		}

		//�������� �� �����
		bool onEnd()
		{
			return end;
		}

		//��������� �������
		VertexT* operator*()
		{
			if (cur >= graph->vectV.size() || cur == -1)
				throw "EXC: ������ ���������� � �������";
			return graph->vectV[cur];
		}

		//��������� ��� ������� �� ������� ������� ���������
		string read_name_vertex()
		{
			VertexT* v = NULL;
			try
			{
				v = operator*();
			}
			catch (...) { throw; }
			if (v->isNameSet())
				return v->getName();
			else
				throw "EXC: ��� ������� �� �����������";
		}

		//��������� ������ ������� �� ������� ������� ���������
		int read_data_vertex()
		{
			VertexT* v = NULL;
			try
			{
				v = operator*();
			}
			catch (...) { throw; } {
				if (v->isDataSet())
					return v->getData();
				else throw "EXC: ������ ������� �� �����������";
			}
		}

		//�������� ������ � ������� �� ������� ������� ���������
		bool write_data_vertex(int d)
		{
			VertexT* v;
			try
			{
				v = operator*();
			}
			catch (...)
			{
				throw;
			}
			v->setData(d);
			return true;
		}

		//�������� ��� ������� �� ������� ������� ���������
		bool write_name_vertex(string str)
		{
			VertexT* v;
			try
			{
				v = operator*();
			}
			catch (...) {
				throw;
			}
			v->setName(str);
			return true;
		}
	};

	//�������� ����
	class EdgeIterator {
		Graph<VertexT, EdgeT>* graph; //�������������� ����
		typename GraphMatrixForm<EdgeT>::EdgeIterator* mIt;
		typename GraphListForm<EdgeT>::EdgeIterator* lIt;
		bool useM;
	public:
		string name, data, weight, fin;
		bool end;

		EdgeIterator(Graph<VertexT, EdgeT>& g)
		{
			graph = &g;
			if (graph->Dense())
			{
				mIt = new typename GraphMatrixForm<EdgeT>::EdgeIterator(static_cast<GraphMatrixForm<EdgeT>*>(g.data));
				useM = true;
			}
			else {
				lIt = new typename GraphListForm<EdgeT>::EdgeIterator(static_cast<GraphListForm<EdgeT>*>(g.data));
				useM = false;
			}
		}

		//��������� � ������
		bool begin()
		{
			if (useM) return
				mIt->begin();
			else
				return lIt->begin();
		}

		//����� �� ��������� �������
		bool operator++()
		{
			if (useM)
				return mIt->next();
			else
				return lIt->next();
		}

		//�������� �� �����
		bool onEnd()
		{
			if (useM)
				return mIt->onEnd();
			else
				return lIt->onEnd();
		}

		//���������� �������� ���� �� �������� �����
		bool toend()
		{
			if (useM)
				return mIt->toend();
			else
				return lIt->toend();
		}

		//��������� �����
		EdgeT* operator*()
		{
			if (onEnd())
				throw "EXC: �������� �� ��������� �����";
			if (useM)
				return mIt->getEdge();
			else
				return lIt->getEdge();
		}

		//��������� ������� ����� � ��� �� ������� ������� ���������
		string read_edge()
		{
			EdgeT* e = operator*();
			VertexT* ve1, * ve2;
			ve1 = e->getVertex1();
			ve2 = e->getVertex2();
			if (!(ve1->isNameSet()))
				name = "��� ����� �� �����������";
			else
				name = ve1->getName();
			if (!(ve2->isNameSet()))
				data = "������ ����� �� �����������";
			else
				data = ve2->getName();
			if (e->isWeightSet() == false)
				weight = "��� ����� �� ����������";
			else
				weight = int_to_sting(e->getWeight());
			fin = "��������� �������: " + name + ". �������� �������: " + data + ". ��� �����: " + weight;
			return fin;
		}

		//��������� ������ ����� �� ������� ������� ���������
		int read_data_edge()
		{
			EdgeT* f = operator*();
			if (f->isDataSet())
				return f->getData();
			else
				throw "EXC: ������ ����� �� �����������";
		}

		bool write_data_edge(int d)
		{
			EdgeT* e;
			try {
				e = operator*();
			}
			catch (char* e) {
				cerr << endl << e << endl;
				return false;
			}
			e->setData(d);
			return true;
		}

		bool write_weight_edge(int w)
		{
			EdgeT* e;
			try {
				e = operator*();
			}
			catch (char* e) {
				cerr << endl << e << endl;
				return false;
			}
			e->setWeight(w);
			return true;
		}
	};

	//�������� ��������� ����
	class OutputEdgeIterator {
		Graph<VertexT, EdgeT>* graph; //�������������� ����
		typename GraphMatrixForm<EdgeT>::OutputEdgeIterator* mIt;
		typename GraphListForm<EdgeT>::OutputEdgeIterator* lIt;
		bool useM;
	public:
		string name, data, weight, fin;
		bool end;

		OutputEdgeIterator(Graph<VertexT, EdgeT>& g, VertexT& v) {
			graph = &g;
			mIt = NULL;
			lIt = NULL;
			int curV = graph->getIndex(&v);
			if (graph->Dense()) {
				mIt = new typename GraphMatrixForm<EdgeT>::OutputEdgeIterator(static_cast<GraphMatrixForm<EdgeT>*>(g.data), curV);
				useM = true;
			}
			else {
				lIt = new typename GraphListForm<EdgeT>::OutputEdgeIterator(static_cast<GraphListForm<EdgeT>*>(g.data), curV);
				useM = false;
			}
		}

		~OutputEdgeIterator()
		{
			if (mIt != NULL)
				delete mIt;
			if (lIt != NULL)
				delete lIt;
		}

		//��������� � ������
		bool begin() {
			if (useM)
				return mIt->begin();
			else
				return lIt->begin();
		}

		//����� �� ��������� �������
		bool operator++() {
			if (useM)
				return mIt->next();
			else
				return lIt->next();
		}

		bool toend() {
			if (useM)
				return mIt->toend();
			else
				return lIt->toend();
		}

		//�������� �� �����
		bool onEnd() {
			if (useM)
				return mIt->onEnd();
			else
				return lIt->onEnd();
		}

		//��������� �����
		EdgeT* operator*() {
			if (onEnd())
				throw "EXC: �������� �� ��������� �����";
			if (useM)
				return mIt->getEdge();
			else
				return lIt->getEdge();
		}

		string read_edge() {
			EdgeT* e = operator*();
			VertexT* ve1, * ve2;
			ve1 = e->getVertex1();
			ve2 = e->getVertex2();
			if (!(ve1->isNameSet()))
				name = "��� ����� �� �����������";
			else
				name = ve1->getName();
			if (!(ve2->isNameSet()))
				data = "������ ����� �� �����������";
			else
				data = ve2->getName();
			if (e->isWeightSet() == false)
				weight = "��� ����� �� ����������";
			else
				weight = int_to_sting(e->getWeight());
			fin = "��������� �������: " + name + ". �������� �������: " + data + ". ��� �����: " + weight;
			return fin;
		}

		int read_data_edge() {
			EdgeT* e;
			e = operator*();
			if (e->isDataSet())
				return e->getData();
			else
				throw "EXC: ������ ����� �� �����������";
		}

		bool write_data_edge(int d) {
			EdgeT* e;
			try {
				e = operator*();
			}
			catch (char* e) {
				return false;
			}
			e->setData(d);
			return true;
		}

		bool write_weight_edge(int w) {
			EdgeT* e;
			try {
				e = operator*();
			}
			catch (char* e) {
				cerr << endl << e << endl;
				return false;
			}
			e->setWeight(w);
			return true;
		}
	};
	friend class VertexIterator;  //������������� �����
	friend class EdgeIterator;
	friend class OutputEdgeIterator;
};

//��������� ������� ������� �� �����������
template <class VertexT, class EdgeT> int Graph<VertexT, EdgeT>::getIndexFromName(string n)
{
	int index = 0;
	for (int i = 0; i < vectV.size(); i++) {
		if (vectV[index]->getName() == n)
			break;
		index++;
	}
	if (index == vectV.size())
		throw "EXC: ������� �� �������";
	return index;
}

//������� ������ L-���� � ������� ������ ������ � ����
template <class VertexT, class EdgeT> Graph<VertexT, EdgeT>::Graph()
{
	sz = 0;
	data = new GraphListForm<EdgeT>(false);
	directed = false;
	dense = false; //L-���� 
	edgeCount = 0;
}

//������� ���� � V ���������, ��� �����, ���� D, ����� ������������� F
template <class VertexT, class EdgeT> Graph<VertexT, EdgeT>::Graph(int vertexCount, bool directed, bool dense)
{
	sz = 0;
	if (dense)
		data = new GraphMatrixForm<EdgeT>(directed);
	else
		data = new GraphListForm<EdgeT>(directed);
	//������ ������� � �������� � ���������
	for (int i = 0; i < vertexCount; i++) {
		VertexT* v = new VertexT();
		v->setName(int_to_sting(sz));
		sz++;
		vectV.push_back(v);
		data->InsertV(i);
	}
	this->directed = directed;
	this->dense = dense;
	edgeCount = 0;
}

//������� ���� � V ���������, � E ���������� �������, ���� D , ����� F
template <class VertexT, class EdgeT>
Graph<VertexT, EdgeT>::Graph(int vertexCount, int edgeCounter, bool directed, bool dense)
{
	sz = 0;
	if (dense)
		data = new GraphMatrixForm<EdgeT>(directed);
	else
		data = new GraphListForm<EdgeT>(directed);
	//������ ������� � �������� � ���������
	for (int i = 0; i < vertexCount; i++) {
		VertexT* v = new VertexT();
		v->setName(int_to_sting(sz));
		sz++;
		vectV.push_back(v);
		data->InsertV(i);
	}
	this->directed = directed;
	this->dense = dense;
	edgeCount = 0;

	//��������� ����
	if (edgeCounter <= 0) return;
	//������������ ����� ����, ����� �� ��������� ���������
	srand((unsigned)time(NULL));
	if (directed)
	{
		if (edgeCounter > vertexCount * (vertexCount - 1))
			edgeCounter = vertexCount * (vertexCount - 1);
	}
	else
	{
		if (edgeCounter > (vertexCount * (vertexCount - 1)) / 2)
			edgeCounter = (vertexCount * (vertexCount - 1)) / 2;
	}
	//���������
	int v1, v2;

	while (edgeCount < edgeCounter) {
		v1 = rand() % vertexCount;
		v2 = rand() % vertexCount;
		if (v1 == v2)
			continue;
		if (data->hasEdge(v1, v2))
			continue;

		EdgeT* t = new EdgeT(vectV[v1], vectV[v2]);
		data->InsertE(v1, v2, t);
		t->setWeight((rand() % 14) + 1);
		if (directed == false)
			data->InsertE(v2, v1, t);
		edgeCount++;
	}
}

//����������� �����������
template <class VertexT, class EdgeT>
Graph<VertexT, EdgeT>::Graph(const Graph<VertexT, EdgeT>& G)
{
	sz = 0;
	delete data;
	if (G.Dense())
		data = new GraphMatrixForm<EdgeT>(*(G.data));
	else
		data = new GraphListForm<EdgeT>(*(G.data));
	directed = G.directed;
	dense = G.dense;
}

//����������
template <class VertexT, class EdgeT>
Graph<VertexT, EdgeT>::~Graph()
{
	while (vectV.size() != 0)
		DeleteV(0);
	delete data;
}

//���������� ����� ������ � �����
template <class VertexT, class EdgeT>
int Graph<VertexT, EdgeT>::getVertexCount()
{
	return vectV.size();
}

//���������� ����� ����� � �����
template <class VertexT, class EdgeT>
int Graph<VertexT, EdgeT>::getEdgeCount()
{
	return edgeCount;
}

//���������� ��� �����
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::Directed()
{
	return directed;
}

//���������� ����� ������������� �����
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::Dense()
{
	return dense;
}

//���������� ����������� ������������ �����
template <class VertexT, class EdgeT>
double Graph<VertexT, EdgeT>::K()
{
	int max = vectV.size() * (vectV.size() - 1);
	if (!directed) {
		max /= 2;
	}
	if (max == 0) {
		return -1;
	}
	else {
		return (double)edgeCount / (double)max;
	}
}

//����������� ���� � L-�����
template <class VertexT, class EdgeT>
void Graph<VertexT, EdgeT>::ToListGraph()
{
	//������ ��������� �������� L-�����
	GraphForm<EdgeT>* newData = new GraphListForm<EdgeT>(this->directed);

	//������ �������
	for (int i = 0; i < vectV.size(); i++)
		newData->InsertV(i);

	//��������� ����
	for (int i = 0; i < vectV.size(); i++)
		for (int j = 0; j < vectV.size(); j++)
			if (data->hasEdge(i, j))
				newData->InsertE(i, j, data->getEdge(i, j));
	delete data;
	data = newData;
	dense = false;
}

//����������� ���� � M-�����
template <class VertexT, class EdgeT>
void Graph<VertexT, EdgeT>::ToMatrixGraph()
{
	//������ ��������� �������� �-�����
	GraphForm<EdgeT>* newData = new GraphMatrixForm<EdgeT>(this->directed);

	//������ �������
	for (int i = 0; i < vectV.size(); i++)
		newData->InsertV(i);

	//��������� ����
	for (int i = 0; i < vectV.size(); i++)
		for (int j = 0; j < vectV.size(); j++)
			if (data->hasEdge(i, j))
				newData->InsertE(i, j, data->getEdge(i, j));
	delete data;
	data = newData;
	dense = true;
}

//��������� ������� � ����� � ���������� ����� ����������� ����� ��������� �������
template <class VertexT, class EdgeT>
VertexT* Graph<VertexT, EdgeT>::InsertV()
{
	VertexT* v = new VertexT;
	data->InsertV(sz);
	v->setName(int_to_sting(sz));
	sz++;
	vectV.push_back(v);
	return v;
}

//������� ������� �� �����, �������� ������� ����������� v
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::DeleteV(VertexT* v)
{
	int index = getIndex(v);
	edgeCount -= data->DeleteEsFromVertex(index, directed);
	if (data->DeleteV(index))
	{
		vectV.erase(vectV.begin() + index);
		return true;
	}
	return false;
}

//������� ������� �� �����, �������� ������� �������
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::DeleteV(int index)
{
	edgeCount -= data->DeleteEsFromVertex(index, directed);
	if (data->DeleteV(index)) {
		vectV.erase(vectV.begin() + index);
		return true;
	}
	return false;
}

//������� ������� �� �����, �������� ������ �������
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::DeleteV(string n)
{
	VertexT* v = NULL;
	try {
		v = getVertexFromName(n);
	}
	catch (char*) {
		return false;
	}
	return DeleteV(v);
}

template <class VertexT, class EdgeT>
VertexT* Graph<VertexT, EdgeT>::getVertex(int index)
{
	if (index < 0 || index >= vectV.size())
		throw "EXC: ������� �� �������";
	return vectV[index];
}

template<class VertexT, class EdgeT>
inline int Graph<VertexT, EdgeT>::getSize()
{
	return this->sz;
}

template <class VertexT, class EdgeT>
VertexT* Graph<VertexT, EdgeT>::getVertexFromName(string n)
{
	int i;
	for (i = 0; i < vectV.size(); i++)
		if (vectV[i]->getName() == n)
			return vectV[i];
	throw "EXC: ������� �� �������";
}

template <class VertexT, class EdgeT>
int Graph<VertexT, EdgeT>::getIndex(VertexT* v)
{
	int index = 0;
	for (; index < vectV.size(); ++index) {
		if (vectV[index] == v)
			break;

	}
	if (index == vectV.size())
		throw "EXC: ������� �� �������";
	return index;
}

//������� �����, ��������� ������� ������
template <class VertexT, class EdgeT>
EdgeT* Graph<VertexT, EdgeT>::InsertE(string v1, string v2)
{
	VertexT* ve1 = new VertexT;
	VertexT* ve2 = new VertexT;
	EdgeT* reb;
	try {
		ve1 = getVertexFromName(v1);
	}
	catch (...)
	{
		throw;
	}

	try
	{
		ve2 = getVertexFromName(v2);
	}
	catch (...)
	{
		throw;
	}
	try
	{
		reb = InsertE(ve1, ve2);
	}
	catch (...)
	{
		throw;
	}
	return reb;
}

//������� �����, ��������� ��������� ������
template <class VertexT, class EdgeT>
EdgeT* Graph<VertexT, EdgeT>::InsertE(int v1, int v2)
{
	EdgeT* e = new EdgeT(getVertex(v1), getVertex(v2));
	if (!data->InsertE(v1, v2, e)) throw "EXC: ������ ������� �������� �����.";
	if (directed == false)
		data->InsertE(v2, v1, e);
	edgeCount++;
	return e;
}

//������� �����, ��������� ������������� ������
template <class VertexT, class EdgeT>
EdgeT* Graph<VertexT, EdgeT>::InsertE(VertexT* v1, VertexT* v2)
{
	EdgeT* e = new EdgeT(v1, v2);
	if (!data->InsertE(getIndex(v1), getIndex(v2), e)) throw "EXC: ������ ������� �������� �����.";
	if (directed == false)//���� ���� �����������������
		data->InsertE(getIndex(v2), getIndex(v1), e);
	edgeCount++;
	return e;
}

//�������� ����� �� �����, ��������� ������� ������
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::DeleteE(string v1, string v2)
{
	VertexT* ve1 = new VertexT;
	VertexT* ve2 = new VertexT;
	try
	{
		ve1 = getVertexFromName(v1);
	}
	catch (char* e)
	{
		cerr << endl << e << endl;
		return false;
	}
	try
	{
		ve2 = getVertexFromName(v2);
	}
	catch (char* e)
	{
		cerr << endl << e << endl;
		return false;
	}
	if (!DeleteE(ve1, ve2)) return false;
	else return true;
}

//�������� ����� �� �����, ��������� ������������� ������
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::DeleteE(VertexT* v1, VertexT* v2)
{
	if (data->DeleteE(getIndex(v1), getIndex(v2)))
	{
		edgeCount--;
		if (directed == false)
			data->DeleteE(getIndex(v2), getIndex(v1));
		return true;
	}
	else
		return false;
}

//�������� ������� ����� � �����, ��������� ������������� ������
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::hasEdge(VertexT* v1, VertexT* v2)
{
	int ind1, ind2;
	try {
		ind1 = getIndex(v1);
	}
	catch (int& a) {
		return false;
	}
	try {
		ind2 = getIndex(v2);
	}
	catch (int& a)
	{
		return false;
	}
	return data->hasEdge(getIndex(v1), getIndex(v2));
}

//�������� ������� ����� � �����, ��������� ��������� ������
template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::hasEdge(int v1, int v2)
{
	if (v1 < 0 || v1 >= vectV.size())
		return false;
	if (v2 < 0 || v2 >= vectV.size())
		return false;
	return data->hasEdge(v1, v2);
}

//��������� �����, ��������� ������������� ������
template <class VertexT, class EdgeT>
EdgeT* Graph<VertexT, EdgeT>::getEdge(VertexT* v1, VertexT* v2)
{
	EdgeT* e;
	try {
		e = data->getEdge(getIndex(v1), getIndex(v2));
	}
	catch (int) {
		throw "����� �� �������";
	}
	return e;
}

template <class VertexT, class EdgeT>
bool  Graph<VertexT, EdgeT>::write_data_edge(string ve1, string ve2, int data)
{
	EdgeT* e;
	VertexT* v1, * v2;
	try {
		v1 = getVertexFromName(ve1);
	}
	catch (char*) {
		return false;
	}
	try {
		v2 = getVertexFromName(ve2);
	}
	catch (char*) {
		return false;
	}
	try {
		e = getEdge(v1, v2);
		e->setData(data);
	}
	catch (char* e) {
		cerr << endl << e << endl;
		return false;
	}
	return true;
}

template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::write_weight_edge(string ve1, string ve2, int w)
{
	EdgeT* e;
	VertexT* v1, * v2;
	try {
		v1 = getVertexFromName(ve1);
	}
	catch (char*) {
		return false;
	}
	try {
		v2 = getVertexFromName(ve2);
	}
	catch (char*) {
		return false;
	}
	try {
		e = getEdge(v1, v2);
		e->setWeight(w);
	}
	catch (char* e) {
		cerr << endl << e << endl;
		return false;
	}
	return true;
}

template <class VertexT, class EdgeT>
int Graph<VertexT, EdgeT>::read_data_edge(string ve1, string ve2)
{
	EdgeT* e;
	VertexT* v1, * v2;
	try {
		v1 = getVertexFromName(ve1);
		v2 = getVertexFromName(ve2);
	}
	catch (char* e) {
		cerr << endl << e << endl;
		return -1;
	}
	try {
		e = getEdge(v1, v2);
	}
	catch (char* e) {
		cerr << endl << e << endl;
		return -1;
	}
	try {
		if (e->isDataSet())
			return e->getData();
		else
			throw "EXC: ������ ����� �� �����������";
	}
	catch (char* e) {
		cerr << endl << e << endl;
		return -1;
	}
}

template <class VertexT, class EdgeT>
int Graph<VertexT, EdgeT>::read_weight_edge(string ve1, string ve2)
{
	EdgeT* e;
	VertexT* v1, * v2;
	try {
		v1 = getVertexFromName(ve1);
		v2 = getVertexFromName(ve2);
		e = getEdge(v1, v2);
	}
	catch (char* e) {
		cerr << endl << e << endl;
		return -1;
	}
	try {
		if (e->isWeightSet())
			return e->getWeight();
		else
			throw "EXC: ��� ����� �� ����������";
	}
	catch (char* e) {
		cerr << endl << e << endl;
		return -1;
	}
}

template <class VertexT, class EdgeT>
void Graph<VertexT, EdgeT>::print_graph()
{
	if (sz == 0) {
		cout << "���� ����!" << endl;
		return;
	}
	int i, j;
	VertexT* v;
	EdgeT* e;
	if (Dense())
	{
		cout << setw(5) << "  ";
		for (i = 0; i < getVertexCount(); i++)
		{
			v = getVertex(i);
			cout << setw(4) << v->getName();
		}
		cout << endl;
		for (i = 0; i < 5 * getVertexCount() + 4; i++)
			cout << "-";
		cout << endl;
		for (i = 0; i < getVertexCount(); i++)
		{
			v = getVertex(i);
			cout << setw(4) << v->getName() << ":";
			for (j = 0; j < getVertexCount(); j++)
				if (hasEdge(i, j))
				{
					e = getEdge(getVertex(i), getVertex(j));
					cout << setw(4) << e->getWeight();
				}
				else
					cout << setw(4) << "-";
			cout << endl;
		}
	}
	else
	{
		if (directed == true) // ���� ���� ���������������
		{
			for (i = 0; i < getVertexCount(); i++) {
				v = getVertex(i);
				cout << v->getName() << ": ";
				OutputEdgeIterator out(*this, *v);
				while (!out.onEnd())	// ��������� ����
				{
					cout << (*out)->getVertex2()->getName() << "; ";
					++out;
				}
				cout << endl;
			}
		}
		else     //���� ���� �����������������
		{
			for (i = 0; i < getVertexCount(); i++)
			{
				v = getVertex(i);
				cout << v->getName() << ": ";
				for (j = 0; j < getVertexCount(); j++)
				{
					v = getVertex(j);
					if (hasEdge(i, j))
					{
						e = getEdge(getVertex(i), getVertex(j));
						if (e->isWeightSet() != 0) //���� ����� ����� ���
						{
							cout << v->getName() << "(" << e->getWeight() << ")" << "; ";
						}
						else
						{
							cout << v->getName() << "; ";
						}
					}
				}
				cout << endl;
			}
		}
		
	}
};

template <class VertexT, class EdgeT>
int Graph<VertexT, EdgeT>::read_data_vertex(string v1)
{
	VertexT* v;
	try
	{
		v = getVertexFromName(v1);
	}
	catch (char* e) {
		cerr << endl << e << endl;
		return -1;
	}
	int d;
	try {
		if (v->isDataSet()) {
			d = v->getData();
			return d;
		}
		else
			throw invalid_argument("EXC: ��� ������ ��� ������ �������");
	}
	catch (invalid_argument& e) {
		cerr << endl << e.what() << endl;
		return -1;
	}
}

template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::write_data_vertex(string v1, int d)
{
	VertexT* v;
	try
	{
		v = getVertexFromName(v1);
	}
	catch (char*) {
		return false;
	};
	v->setData(d);
	return true;
}

template <class VertexT, class EdgeT>
bool Graph<VertexT, EdgeT>::write_name_vertex(string v1, string str)
{
	VertexT* v;
	try
	{
		v = getVertexFromName(v1);
	}
	catch (char*) {
		return false;
	};
	v->setName(str);
	return true;
}
