#include <iostream>
#include <vector>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "Task1.h"
#include "Task2.h"
using namespace std;
typedef Graph < Vertex<string, int>, Edge< Vertex<string, int>, int, int>> myGraph;
typedef Task1 < Vertex<string, int>, Edge< Vertex<string, int>, int, int>> myTask1;
typedef Task2 < Vertex<string, int>, Edge< Vertex<string, int>, int, int>> myTask2;

vector<string> mainMenuStr = {
"������� ����", "-----------------", "�������� �����:", "-----------------",
"[1] ������� ������ L-���� � ������� ����������� ������ � �����",
"[2] ������� ���� � V ���������, ��� �����, ���� D, ����� ������������� F",
"[3] ������� ���� � V ���������, � E ���������� �������, ���� D, ����� F",
"-----------------", "��������", "-----------------",
"[4] ����������� ����", "[5] ����� ����� ������ � �����", "[6] ����� ����� ����� � �����",
"[7] ����� ���� �����", "[8] ����� ����� ������������� �����", "[9] ����� ������������ ������������ �����",
"[10] ������������� ���� � L-�����", "[11] ������������� ���� � M-�����", "[12] �������� ������� � �����",
"[13] ������� ������� �� �����", "[14] �������� ����� � ����", "[15] ������� ����� �� �����",
"-----------------", "�������� ��� ���������", "-----------------",  "[16] ��������� ������ � �������",
"[17] �������� ������ � �������", "[18] ������������ ��� �������", "-----------------",
"�������� ��� �������", "-----------------", "[19] ��������� ��� �����", "[20] ��������� ������ � �����",
"[21] �������� ������ � �����", "[22] �������� ��� �����", "-----------------",
"���������", "-----------------", "[23] ���� ��������� ������", "[24] ���� ��������� �����",
 "[25] ���� ��������� ��������� �����", "[26] ������ 2 (1 �������)", "[27] ������ 3 (3 �������)",
 "[0] �����"
};

vector<string> menuIterVert = {
"���� ��������� ������", "[1] ���������� �� ��������� �������", "[2] ���������� �� �������� �������",
"[3] ������� � ��������� �������", "[4] ��������� ��� ������� �� ������� �������",
"[5] ��������� ������ ������� �� ������� �������", "[6] �������� ������ ������� �� ������� �������",
"[7] �������� ��� ������� �� ������� �������", "[0] ����� � �������� ����"
};

vector <string>  menuIterEdge = {
"���� ��������� Ш���", "[1] ���������� �� ��������� �����", "[2] ���������� �� �������� �����",
"[3] ������� � ��������� �������", "[4] ��������� ���������� � ����� �� ������� �������",
"[5] ��������� ������ ����� �� ������� �������", "[6] �������� ������ ����� �� ������� �������",
"[7] �������� ��� ����� �� ������� �������", "[0] ����� � �������� ����"
};

vector <string>  menuIterEdgeOut = {
"���� ��������� ��������� Ш���", "[1] ������� �������", "[2] ���������� �� ��������� �����",
"[3] ���������� �� �������� �����", "[4] ������� � ��������� �������",
"[5] ��������� ������� ����� � ��� �� ������� �������", "[6] ��������� ������ ����� �� ������� �������",
"[7] �������� ������ � ����� �� ������� �������", "[8] �������� ��� ����� �� ������� �������",
"[0] ����� � �������� ����"
};

void printMenu(vector<string> menu);

int main()
{
	setlocale(LC_ALL, "ru");
	myGraph* graph = new Graph< Vertex<string, int>, Edge< Vertex<string, int>, int, int>>(); ;
	myGraph::VertexIterator* iterVert;
	myGraph::EdgeIterator* iterEdge;
	myGraph::OutputEdgeIterator* iterEdgeOut;
	myTask1* t1;
	myTask2* t2;
	vector<int> result;

	int countVertex = 0, countEdge = 0, directed = 0, type = 0;
	int command = 0;
	string s1 = "";
	string s2 = "";
	int v1 = 0, v2 = 0;
	bool work = true;

	while (true) {
		printMenu(mainMenuStr);
		graph->print_graph();
		cout << "������� ����� �������: " << endl;
		cout << ">>> ";
		cin >> command;

		switch (command)
		{
		default:
			cout << "������� ������������ ������! ���������� ��� ���!" << endl;
			break;
		case 0:
			exit(0);
			break;
		case 1:
			graph = new Graph< Vertex<string, int>, Edge< Vertex<string, int>, int, int>>();
			cout << "���� ������� ������!" << endl;
			break;
		case 2:
			cout << "������� ���������� ������: ";
			cin >> countVertex;
			cout << "��������������� �� ����? (0 - ���, 1 - ��): ";
			cin >> directed;
			cout << "����� ������������� ����� (0 - ������, 1 - �������): ";
			cin >> type;

			graph = new Graph< Vertex<string, int>, Edge< Vertex<string, int>, int, int>>(countVertex, directed, type);
			cout << "���� ������� ������!" << endl;
			break;
		case 3:
			cout << "������� ���������� ������: ";
			cin >> countVertex;
			cout << "������� ���������� �����: ";
			cin >> countEdge;
			cout << "��������������� �� ����? (0 - ���, 1 - ��): ";
			cin >> directed;
			cout << "����� ������������� ����� (0 - ������, 1 - �������): ";
			cin >> type;

			graph = new Graph< Vertex<string, int>, Edge< Vertex<string, int>, int, int>>(countVertex, countEdge, directed, type);
			cout << "���� ������� ������!" << endl;
			break;
		case 4:
			graph->print_graph();
			break;
		case 5:
			cout << "����� ������ � �����: " << graph->getVertexCount();
			break;
		case 6:
			cout << "����� ����� � �����: " << graph->getEdgeCount();
			break;
		case 7:
			cout << "��� ����� (0 - �����������������, 1 - ���������������): " << graph->Directed();
			break;
		case 8:
			cout << "����� ������������� ����� (0 - L-����, 1 - M-����): " << graph->Dense();
			break;
		case 9:
			cout << "����������� ������������: " << graph->K();
			break;
		case 10:
			graph->ToListGraph();
			cout << "���� ������� ������������ � L-�����!";
			break;
		case 11:
			graph->ToMatrixGraph();
			cout << "���� ������� ������������ � M-�����!";
			break;
		case 12:
			graph->InsertV();
			cout << "������� ������� ��������� � ����!";
			break;
		case 13:
			cout << "������� ����� ��������� �������: ";
			cin >> command;
			cout << "�������� ������� (1 - ������� �������, 0 - ������� �� �������): " << graph->DeleteV(command);
			break;
		case 14:
			cout << "������� ����� �������, �� ������� ������� �����: ";
			cin >> v1;
			cout << "������� ����� �������, � ������� ������ �����: ";
			cin >> v2;
			try {
				graph->InsertE(v1, v2);
			}
			catch (const char* e) {
				cout << e;
				break;
			}
			catch (...) {
				cout << "��� �� ����� �� ���!";
			}
			cout << "����� ��������� � ����!";
			break;
		case 15:
			cout << "������� ��� ������� �� ������� ������� �����: ";
			cin >> v1;
			cout << "������� ��� �������, � ������� ������ �����: ";
			cin >> v2;
			try {
				cout << "�������� ����� (1 - ����� �������, 0 - ����� �� �������): " << graph->DeleteE(int_to_sting(v1), int_to_sting(v2));
			}
			catch (const char* e) {
				cout << e;
			}
			break;
		case 16:
			cout << "������� ��� �������: ";
			cin >> s1;
			try {
				cout << "������ �������: " << graph->read_data_vertex(s1);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 17:
			cout << "������� ��� �������: ";
			cin >> s1;
			cout << "������� ������ ��� �������: ";
			cin >> command;
			try {
				cout << "������ ��� ������� �������� (1 - ��, 0 - ���): " << graph->write_data_vertex(s1, command);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 18:
			cout << "������� ������ ��� �������: ";
			cin >> s1;
			cout << "������� ����� ���: ";
			cin >> s2;
			try {
				cout << "��� ������� ������������ (1 - ��, 0 - ���): " << graph->write_name_vertex(s1, s2);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 19:
			cout << "������� ��� ������� �� ������� ������� �����: ";
			cin >> s1;
			cout << "������� ��� �������, � ������� ������ �����: ";
			cin >> s2;
			try {
				cout << graph->read_weight_edge(s1, s2);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 20:
			cout << "������� ��� ������� �� ������� ������� �����: ";
			cin >> s1;
			cout << "������� ��� �������, � ������� ������ �����: ";
			cin >> s2;
			try {
				cout << graph->read_data_edge(s1, s2);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 21:
			cout << "������� ��� ������� �� ������� ������� �����: ";
			cin >> s1;
			cout << "������� ��� �������, � ������� ������ �����: ";
			cin >> s2;
			cout << "������� ������ ��� �����: ";
			cin >> command;
			try {
				cout << "������ ��� ����� �������� (1 - ��, 0 - ���): " << graph->write_data_edge(s1, s2, command);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 22:
			cout << "������� ��� ������� �� ������� ������� �����: ";
			cin >> s1;
			cout << "������� ��� �������, � ������� ������ �����: ";
			cin >> s2;
			cout << "������� ��� �����: ";
			cin >> command;
			try {
				cout << "��� ����� ������� (1 - ��, 0 - ���): " << graph->write_weight_edge(s1, s2, command);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 23:
			iterVert = new myGraph::VertexIterator(*graph);
			work = true;
			while (work) {
				printMenu(menuIterVert);
				graph->print_graph();
				cout << "������� ����� �������: " << endl;
				cout << ">>> ";
				cin >> command;
				switch (command)
				{
				default:
					cout << "������� ������������ ������! ���������� ��� ���!" << endl;
					break;
				case 0:
					work = false;
					break;
				case 1:
					cout << "��������� ���������: " << iterVert->begin();
					break;
				case 2:
					cout << "��������� ���������: " << iterVert->toend();
					break;
				case 3:
					try {
						cout << "��������� ���������: " << iterVert->operator++();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 4:
					try {
						cout << "��������� ������: " << iterVert->read_name_vertex();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					catch (...) {
						cout << "ERROR!" << endl;
					}
					break;
				case 5:
					try {
						cout << "��������� ������: " << iterVert->read_data_vertex();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					catch (...) {
						cout << "ERROR!" << endl;
					}
					break;
				case 6:
					cout << "������� ������: ";
					cin >> command;
					try {
						cout << "��������� ������: " << iterVert->write_data_vertex(command);
					}
					catch (...) {
						cout << "ERROR!" << endl;
					}
					break;
				case 7:
					cout << "������� ��� �������: ";
					cin >> s1;
					try {
						cout << "��������� ������: " << iterVert->write_name_vertex(s1);
					}
					catch (...) {
						cout << "ERROR!" << endl;
					}
					break;
				}
				cout << endl;
				system("pause");
			}
			break;
		case 24:
			iterEdge = new myGraph::EdgeIterator(*graph);
			work = true;
			while (work) {
				printMenu(menuIterEdge);
				graph->print_graph();
				cout << "������� ����� �������: " << endl;
				cout << ">>> ";
				cin >> command;
				switch (command)
				{
				default:
					cout << "������� ������������ ������! ���������� ��� ���!" << endl;
					break;
				case 0:
					work = false;
					break;
				case 1:
					cout << "��������� ���������: " << iterEdge->begin();
					break;
				case 2:
					cout << "��������� ���������: " << iterEdge->toend();
					break;
				case 3:
					try {
						cout << "��������� ���������: " << iterEdge->operator++();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 4:
					try {
						cout << "��������� ������: " << iterEdge->read_edge();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 5:
					try {
						cout << "��������� ������: " << iterEdge->read_data_edge();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 6:
					cout << "������� ������: ";
					cin >> command;
					try {
						cout << "��������� ������: " << iterEdge->write_data_edge(command);
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 7:
					cout << "������� ��� �����: ";
					cin >> command;
					try {
						cout << "��������� ������: " << iterEdge->write_weight_edge(command);
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				}
				cout << endl;
				system("pause");
			}
			break;
		case 25:
			iterEdgeOut = new myGraph::OutputEdgeIterator(*graph, *graph->getVertex(0));
			work = true;
			while (work)
			{
				printMenu(menuIterEdgeOut);
				graph->print_graph();
				cout << "������� ����� �������: " << endl;
				cout << ">>> ";
				cin >> command;
				switch (command)
				{
				default:
					cout << "������� ������������ ������! ���������� ��� ���!" << endl;
					break;
				case 0:
					work = false;
					break;
				case 1:
					cout << "������� ����� �������: ";
					cin >> command;
					try {
						iterEdgeOut = new myGraph::OutputEdgeIterator(*graph, *graph->getVertex(command));
					}
					catch (const char* e) {
						cout << e << endl;
					}
					cout << "�������� ������� ������!";
					break;
				case 2:
					cout << "��������� ���������: " << iterEdgeOut->begin();
					break;
				case 3:
					cout << "��������� ���������: " << iterEdgeOut->toend();
					break;
				case 4:
					try {
						cout << "��������� ���������: " << iterEdgeOut->operator++();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 5:
					try {
						cout << "��������� ������: " << iterEdgeOut->read_edge();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 6:
					try {
						cout << "��������� ������: " << iterEdgeOut->read_data_edge();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 7:
					cout << "������� ������: ";
					cin >> command;
					try {
						cout << "��������� ������: " << iterEdgeOut->write_data_edge(command);
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 8:
					cout << "������� ��� �����: ";
					cin >> command;
					try {
						cout << "��������� ������: " << iterEdgeOut->write_weight_edge(command);
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				}
				cout << endl;
				system("pause");
			}
			break;
		case 26:
			t1 = new myTask1(graph);
			result = t1->result();
			for (int i = 0; i < result.size(); i++) // ������� ��������� �� �����
				cout << result[i] << ' ';
			cout << endl;
			result.clear();
			break;
		case 27:
			cout << "������� �������, � ������� ����� ������ ����: ";
			cin >> command;
			t2 = new myTask2(graph, command);
			t2->Restart();
			cout << "������� ������ ������� �� ������� ���� ���������� ����" << endl;
			cin >> v2;

			cout << "��������� ���� � ��������� ������� �� ���������:\t\n";
			try
			{


				auto result = t2->Result(v2);
				if (result.Distance != INT_MAX)
				{
					cout << result.From << " -> " << result.To << " = " << result.Distance << "\t����: " << result.From;
					for (auto wayIt = result.Vertexes.begin(); wayIt != result.Vertexes.end(); wayIt++)
					{
						cout << "-" << *wayIt;
					}
					cout << endl;
				}
				else
				{
					cout << result.From << " -> " << result.To << " = " << "������� ����������" << endl;
				}
			}
			catch (...)
			{
				cout << "����������" << endl;
			}
			break;
		}
		cout << endl;
		system("pause");
	}


}

void printMenu(vector<string> menu) {
	system("cls");
	for (int i = 0; i < menu.size(); i++)
	{
		cout << menu.at(i) << endl;
	}
}


