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
"ГЛАВНОЕ МЕНЮ", "-----------------", "Создание графа:", "-----------------",
"[1] Создать пустой L-граф с нулевым количеством вершин и ребер",
"[2] Создать граф с V вершинами, без ребер, типа D, формы представления F",
"[3] Создать граф с V вершинами, с E случайными ребрами, типа D, формы F",
"-----------------", "Операции", "-----------------",
"[4] Распечатать граф", "[5] Опрос числа вершин в графе", "[6] Опрос числа ребер в графе",
"[7] Опрос типа графа", "[8] Опрос формы представления графа", "[9] Опрос коэффициента насыщенности графа",
"[10] Преобразовать граф к L-форме", "[11] Преобразовать граф к M-форме", "[12] Добавить вершину к графу",
"[13] Удалить вершину из графа", "[14] Вставить ребро в граф", "[15] Удалить ребро из графа",
"-----------------", "Операции над вершинами", "-----------------",  "[16] Прочитать данные о вершине",
"[17] Записать данные о вершине", "[18] Перезаписать имя вершины", "-----------------",
"Операции над ребрами", "-----------------", "[19] Прочитать вес ребра", "[20] Прочитать данные о ребре",
"[21] Записать данные о ребре", "[22] Записать вес ребра", "-----------------",
"Остальное", "-----------------", "[23] Меню итератора вершин", "[24] Меню итератора ребер",
 "[25] Меню итератора исходящих ребер", "[26] Задача 2 (1 вариант)", "[27] Задача 3 (3 вариант)",
 "[0] Выход"
};

vector<string> menuIterVert = {
"МЕНЮ ИТЕРАТОРА ВЕРШИН", "[1] Установить на начальную вершину", "[2] Установить на конечную вершину",
"[3] Переход к следующей позиции", "[4] Прочитать имя вершины по текущей позиции",
"[5] Прочитать данные вершины по текущей позиции", "[6] Записать данные вершины по текущей позиции",
"[7] Записать имя вершины по текущей позиции", "[0] Назад к главному меню"
};

vector <string>  menuIterEdge = {
"МЕНЮ ИТЕРАТОРА РЁБЕР", "[1] Установить на начальное ребро", "[2] Установить на конечное ребро",
"[3] Переход к следующей позиции", "[4] Прочитать информацию о ребре по текущей позиции",
"[5] Прочитать данные ребра по текущей позиции", "[6] Записать данные ребра по текущей позиции",
"[7] Записать вес ребра по текущей позиции", "[0] Назад к главному меню"
};

vector <string>  menuIterEdgeOut = {
"МЕНЮ ИТЕРАТОРА ИСХОДЯЩИХ РЁБЕР", "[1] Выбрать вершину", "[2] Установить на начальное ребро",
"[3] Установить на конечное ребро", "[4] Переход к следующей позиции",
"[5] Прочитать вершины ребра и вес по текущей позиции", "[6] Прочитать данные ребра по текущей позиции",
"[7] Записать данные о ребре по текущей позиции", "[8] Записать вес ребра по текущей позиции",
"[0] Назад к главному меню"
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
		cout << "Введите номер команды: " << endl;
		cout << ">>> ";
		cin >> command;

		switch (command)
		{
		default:
			cout << "Введены некорректные данные! Попробуйте еще раз!" << endl;
			break;
		case 0:
			exit(0);
			break;
		case 1:
			graph = new Graph< Vertex<string, int>, Edge< Vertex<string, int>, int, int>>();
			cout << "Граф успешно создан!" << endl;
			break;
		case 2:
			cout << "Введите количество вершин: ";
			cin >> countVertex;
			cout << "Ориентированный ли граф? (0 - НЕТ, 1 - ДА): ";
			cin >> directed;
			cout << "Форма представления графа (0 - СПИСОК, 1 - МАТРИЦА): ";
			cin >> type;

			graph = new Graph< Vertex<string, int>, Edge< Vertex<string, int>, int, int>>(countVertex, directed, type);
			cout << "Граф успешно создан!" << endl;
			break;
		case 3:
			cout << "Введите количество вершин: ";
			cin >> countVertex;
			cout << "Введите количество ребер: ";
			cin >> countEdge;
			cout << "Ориентированный ли граф? (0 - НЕТ, 1 - ДА): ";
			cin >> directed;
			cout << "Форма представления графа (0 - СПИСОК, 1 - МАТРИЦА): ";
			cin >> type;

			graph = new Graph< Vertex<string, int>, Edge< Vertex<string, int>, int, int>>(countVertex, countEdge, directed, type);
			cout << "Граф успешно создан!" << endl;
			break;
		case 4:
			graph->print_graph();
			break;
		case 5:
			cout << "Число вершин в графе: " << graph->getVertexCount();
			break;
		case 6:
			cout << "Число ребер в графе: " << graph->getEdgeCount();
			break;
		case 7:
			cout << "Тип графа (0 - неориентированный, 1 - ориентированный): " << graph->Directed();
			break;
		case 8:
			cout << "Форма предстваления графа (0 - L-граф, 1 - M-граф): " << graph->Dense();
			break;
		case 9:
			cout << "Коэффициент насыщенности: " << graph->K();
			break;
		case 10:
			graph->ToListGraph();
			cout << "Граф успешно преобразован к L-Форме!";
			break;
		case 11:
			graph->ToMatrixGraph();
			cout << "Граф успешно преобразован к M-Форме!";
			break;
		case 12:
			graph->InsertV();
			cout << "Вершина успешно добавлена в граф!";
			break;
		case 13:
			cout << "Введите номер удаляемой вершины: ";
			cin >> command;
			cout << "Удаление вершины (1 - вершина удалена, 0 - вершина не удалена): " << graph->DeleteV(command);
			break;
		case 14:
			cout << "Введите номер вершины, из которой выходит ребро: ";
			cin >> v1;
			cout << "Введите номер вершины, в которую входит ребро: ";
			cin >> v2;
			try {
				graph->InsertE(v1, v2);
			}
			catch (const char* e) {
				cout << e;
				break;
			}
			catch (...) {
				cout << "Что то пошло не так!";
			}
			cout << "Ребро добавлено в граф!";
			break;
		case 15:
			cout << "Введите имя вершины из которой выходит ребро: ";
			cin >> v1;
			cout << "Введите имя вершины, в которую входит ребро: ";
			cin >> v2;
			try {
				cout << "Удаление ребра (1 - ребро удалено, 0 - ребро не удалено): " << graph->DeleteE(int_to_sting(v1), int_to_sting(v2));
			}
			catch (const char* e) {
				cout << e;
			}
			break;
		case 16:
			cout << "Введите имя вершины: ";
			cin >> s1;
			try {
				cout << "Данные вершины: " << graph->read_data_vertex(s1);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 17:
			cout << "Введите имя вершины: ";
			cin >> s1;
			cout << "Введите данные для вершины: ";
			cin >> command;
			try {
				cout << "Данные для вершины записаны (1 - ДА, 0 - НЕТ): " << graph->write_data_vertex(s1, command);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 18:
			cout << "Введите старое имя вершины: ";
			cin >> s1;
			cout << "Введите новое имя: ";
			cin >> s2;
			try {
				cout << "Имя вершины перезаписано (1 - ДА, 0 - НЕТ): " << graph->write_name_vertex(s1, s2);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 19:
			cout << "Введите имя вершины из которой выходит ребро: ";
			cin >> s1;
			cout << "Введите имя вершины, в которую входит ребро: ";
			cin >> s2;
			try {
				cout << graph->read_weight_edge(s1, s2);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 20:
			cout << "Введите имя вершины из которой выходит ребро: ";
			cin >> s1;
			cout << "Введите имя вершины, в которую входит ребро: ";
			cin >> s2;
			try {
				cout << graph->read_data_edge(s1, s2);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 21:
			cout << "Введите имя вершины из которой выходит ребро: ";
			cin >> s1;
			cout << "Введите имя вершины, в которую входит ребро: ";
			cin >> s2;
			cout << "Введите данные для ребра: ";
			cin >> command;
			try {
				cout << "Данные для ребра записаны (1 - ДА, 0 - НЕТ): " << graph->write_data_edge(s1, s2, command);
			}
			catch (const char* e) {
				cout << e << endl;
			}
			break;
		case 22:
			cout << "Введите имя вершины из которой выходит ребро: ";
			cin >> s1;
			cout << "Введите имя вершины, в которую входит ребро: ";
			cin >> s2;
			cout << "Введите вес ребра: ";
			cin >> command;
			try {
				cout << "Вес ребра записан (1 - ДА, 0 - НЕТ): " << graph->write_weight_edge(s1, s2, command);
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
				cout << "Введите номер команды: " << endl;
				cout << ">>> ";
				cin >> command;
				switch (command)
				{
				default:
					cout << "Введены некорректные данные! Попробуйте еще раз!" << endl;
					break;
				case 0:
					work = false;
					break;
				case 1:
					cout << "Результат установки: " << iterVert->begin();
					break;
				case 2:
					cout << "Результат установки: " << iterVert->toend();
					break;
				case 3:
					try {
						cout << "Результат установки: " << iterVert->operator++();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 4:
					try {
						cout << "Результат чтения: " << iterVert->read_name_vertex();
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
						cout << "Результат чтения: " << iterVert->read_data_vertex();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					catch (...) {
						cout << "ERROR!" << endl;
					}
					break;
				case 6:
					cout << "Введите данные: ";
					cin >> command;
					try {
						cout << "Результат записи: " << iterVert->write_data_vertex(command);
					}
					catch (...) {
						cout << "ERROR!" << endl;
					}
					break;
				case 7:
					cout << "Введите имя вершины: ";
					cin >> s1;
					try {
						cout << "Результат записи: " << iterVert->write_name_vertex(s1);
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
				cout << "Введите номер команды: " << endl;
				cout << ">>> ";
				cin >> command;
				switch (command)
				{
				default:
					cout << "Введены некорректные данные! Попробуйте еще раз!" << endl;
					break;
				case 0:
					work = false;
					break;
				case 1:
					cout << "Результат установки: " << iterEdge->begin();
					break;
				case 2:
					cout << "Результат установки: " << iterEdge->toend();
					break;
				case 3:
					try {
						cout << "Результат установки: " << iterEdge->operator++();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 4:
					try {
						cout << "Результат чтения: " << iterEdge->read_edge();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 5:
					try {
						cout << "Результат чтения: " << iterEdge->read_data_edge();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 6:
					cout << "Введите данные: ";
					cin >> command;
					try {
						cout << "Результат записи: " << iterEdge->write_data_edge(command);
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 7:
					cout << "Введите вес ребра: ";
					cin >> command;
					try {
						cout << "Результат записи: " << iterEdge->write_weight_edge(command);
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
				cout << "Введите номер команды: " << endl;
				cout << ">>> ";
				cin >> command;
				switch (command)
				{
				default:
					cout << "Введены некорректные данные! Попробуйте еще раз!" << endl;
					break;
				case 0:
					work = false;
					break;
				case 1:
					cout << "Введите номер вершины: ";
					cin >> command;
					try {
						iterEdgeOut = new myGraph::OutputEdgeIterator(*graph, *graph->getVertex(command));
					}
					catch (const char* e) {
						cout << e << endl;
					}
					cout << "Итератор успешно создан!";
					break;
				case 2:
					cout << "Результат установки: " << iterEdgeOut->begin();
					break;
				case 3:
					cout << "Результат установки: " << iterEdgeOut->toend();
					break;
				case 4:
					try {
						cout << "Результат установки: " << iterEdgeOut->operator++();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 5:
					try {
						cout << "Результат чтения: " << iterEdgeOut->read_edge();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 6:
					try {
						cout << "Результат чтения: " << iterEdgeOut->read_data_edge();
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 7:
					cout << "Введите данные: ";
					cin >> command;
					try {
						cout << "Результат записи: " << iterEdgeOut->write_data_edge(command);
					}
					catch (const char* e) {
						cout << e << endl;
					}
					break;
				case 8:
					cout << "Введите вес ребра: ";
					cin >> command;
					try {
						cout << "Результат записи: " << iterEdgeOut->write_weight_edge(command);
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
			for (int i = 0; i < result.size(); i++) // Выводим результат на экран
				cout << result[i] << ' ';
			cout << endl;
			result.clear();
			break;
		case 27:
			cout << "Введите вершину, в которую будем искать пути: ";
			cin >> command;
			t2 = new myTask2(graph, command);
			t2->Restart();
			cout << "Введите индекс вершины из которой надо посмотреть путь" << endl;
			cin >> v2;

			cout << "Стоимость пути в начальную вершины из остальных:\t\n";
			try
			{


				auto result = t2->Result(v2);
				if (result.Distance != INT_MAX)
				{
					cout << result.From << " -> " << result.To << " = " << result.Distance << "\tПуть: " << result.From;
					for (auto wayIt = result.Vertexes.begin(); wayIt != result.Vertexes.end(); wayIt++)
					{
						cout << "-" << *wayIt;
					}
					cout << endl;
				}
				else
				{
					cout << result.From << " -> " << result.To << " = " << "маршрут недоступен" << endl;
				}
			}
			catch (...)
			{
				cout << "Исключение" << endl;
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


