#pragma once
//АТД «Дескриптор вершины графа»

template <class NameT, class DataT> class Vertex
{
	NameT name;     				//Имя вершины
	DataT data;     				//Данные вершины
	bool nameSet, dataSet;			//признаки установки имени данных 
public:
	Vertex();						//Конструктор пустой вершины
	Vertex(NameT name, DataT data);	//Конструктор с параметрами имени и данных
	void setName(NameT name);		//Установка имени 
	void setData(DataT data);    	//Установка данных
	NameT getName();				//Получение имени
	DataT getData();				//Получение данных
	bool isNameSet();				//Проверка установленности имени
	bool isDataSet();				//Проверка установленности данных
};

//Конструкторы
template <class NameT, class DataT>
Vertex <NameT, DataT>::Vertex() : nameSet(false), dataSet(false) {}

template <class NameT, class DataT>
Vertex <NameT, DataT>::Vertex(NameT name, DataT data) :
	name(name),
	data(data),
	nameSet(true),
	dataSet(true) {}

//Установка имени 
template <class NameT, class DataT>
void Vertex <NameT, DataT>::setName(NameT name)
{
	this->name = name;
	nameSet = true;
}

//Установка данных
template <class NameT, class DataT>
void Vertex <NameT, DataT>::setData(DataT data)
{
	this->data = data;
	dataSet = true;
}

//Получение имени
template <class NameT, class DataT>
NameT Vertex <NameT, DataT>::getName()
{
	return name;
}

//Получение данных
template <class NameT, class DataT>
DataT Vertex <NameT, DataT>::getData()
{
	return data;
}

//Проверка установленности имени
template <class NameT, class DataT>
bool Vertex <NameT, DataT>::isNameSet()
{
	return nameSet;
}

//Проверка установленности данных
template <class NameT, class DataT>
bool Vertex <NameT, DataT>::isDataSet()
{
	return dataSet;
}



