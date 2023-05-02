#pragma once
//��� ����������� ������� �����

template <class NameT, class DataT> class Vertex
{
	NameT name;     				//��� �������
	DataT data;     				//������ �������
	bool nameSet, dataSet;			//�������� ��������� ����� ������ 
public:
	Vertex();						//����������� ������ �������
	Vertex(NameT name, DataT data);	//����������� � ����������� ����� � ������
	void setName(NameT name);		//��������� ����� 
	void setData(DataT data);    	//��������� ������
	NameT getName();				//��������� �����
	DataT getData();				//��������� ������
	bool isNameSet();				//�������� ��������������� �����
	bool isDataSet();				//�������� ��������������� ������
};

//������������
template <class NameT, class DataT>
Vertex <NameT, DataT>::Vertex() : nameSet(false), dataSet(false) {}

template <class NameT, class DataT>
Vertex <NameT, DataT>::Vertex(NameT name, DataT data) :
	name(name),
	data(data),
	nameSet(true),
	dataSet(true) {}

//��������� ����� 
template <class NameT, class DataT>
void Vertex <NameT, DataT>::setName(NameT name)
{
	this->name = name;
	nameSet = true;
}

//��������� ������
template <class NameT, class DataT>
void Vertex <NameT, DataT>::setData(DataT data)
{
	this->data = data;
	dataSet = true;
}

//��������� �����
template <class NameT, class DataT>
NameT Vertex <NameT, DataT>::getName()
{
	return name;
}

//��������� ������
template <class NameT, class DataT>
DataT Vertex <NameT, DataT>::getData()
{
	return data;
}

//�������� ��������������� �����
template <class NameT, class DataT>
bool Vertex <NameT, DataT>::isNameSet()
{
	return nameSet;
}

//�������� ��������������� ������
template <class NameT, class DataT>
bool Vertex <NameT, DataT>::isDataSet()
{
	return dataSet;
}



