#pragma once
#include <vector>

using namespace std;

//����� �������������
template <class EdgeT> class GraphForm {
public:
	virtual bool InsertV(int index) = 0;
	virtual bool DeleteV(int index) = 0;
	virtual bool InsertE(int v1, int v2, EdgeT* t) = 0;
	virtual bool DeleteE(int v1, int v2) = 0;
	virtual int DeleteEsFromVertex(int index, bool directed) = 0;
	virtual bool hasEdge(int v1, int v2) = 0;
	virtual EdgeT* getEdge(int v1, int v2) = 0;
	virtual vector<vector<EdgeT*>> getMatrix() = 0;
};

//����� ������������� ���������
template <class EdgeT> class GraphMatrixForm : public GraphForm < EdgeT >
{
	friend class EdgeIterator;
	bool directed;
public:
	vector<vector<EdgeT*>> matrix;	//������� ���������	
	vector<vector<EdgeT*>> getMatrix();

	GraphMatrixForm(bool directed) : directed(directed) {}

	//������� ������
	bool InsertV(int index) {
		int size = matrix.size(); //����� ������
		//�������� ����� �������
		if (index < 0 || index > size) return false;
		//������ ����� ������ ������
		vector<EdgeT*> newLine;
		newLine.assign(size, NULL);
		//��������� ����� ������:
		matrix.insert(matrix.begin() + index, newLine);
		++size;
		//��������� ����� �������:
		for (int i = 0; i < size; i++)
			matrix[i].insert(matrix[i].begin() + index, (EdgeT*)NULL);
		return true;
	}

	//�������� ������
	bool DeleteV(int index)
	{
		int size = matrix.size(); //����� ������
		//�������� ����� �������
		if (index < 0 || index >= size)
			return false;
		//������� ������:
		matrix.erase(matrix.begin() + index);
		--size;
		//������� �������:
		for (int i = 0; i < size; i++)
			matrix[i].erase(matrix[i].begin() + index);
		return true;
	}

	//������� �����
	bool InsertE(int v1, int v2, EdgeT* t)
	{
		int size = matrix.size(); //����� ������
		//�������� ����� �������
		if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
		//����� ��� ����� ��� ����
		if (v1 == v2 || matrix[v1][v2] != NULL) return false;
		//��������� �����
		matrix[v1][v2] = t;
		return true;
	}

	//�������� �����
	bool DeleteE(int v1, int v2)
	{
		int size = matrix.size(); //����� ������
		//�������� ����� �������
		if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
		//����� ���
		if (v1 == v2 || matrix[v1][v2] == NULL) return false;
		matrix[v1][v2] = NULL;
		return true;
	}

	//������� �������� � ��������� �� ������� ����
	int DeleteEsFromVertex(int index, bool directed)
	{
		int size = matrix.size(); //����� ������
		int deleted = 0;
		//�������� ����� �������
		if (index < 0 || index >= size) return 0;
		//������� ��������� � �������� ����
		for (int i = 0; i < size; i++) {
			if (matrix[i][index] != NULL) {
				delete matrix[i][index];
				matrix[i][index] = NULL;
				++deleted;
				//������� ������������ �����, ���� ���� �����������������
				if (directed == false)
					matrix[index][i] = NULL;
			}
			if (matrix[index][i] != NULL) {
				delete matrix[index][i];
				matrix[index][i] = NULL;
				++deleted;
			}
		}
		return deleted;
	}

	//�������� � ���������
	bool hasEdge(int v1, int v2)
	{
		int size = matrix.size(); //����� ������
		//�������� ����� �������
		if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
			return false;
		if (v1 == v2) //�����
			return false;
		if (matrix[v1][v2] != NULL)
			return true;
		return false;
	}

	EdgeT* getEdge(int v1, int v2)
	{
		int size = matrix.size(); //����� ������
		//�������� ����� �������
		if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
			throw 1;
		if (v1 == v2 || matrix[v1][v2] == NULL)//����� 
			throw 1;
		return matrix[v1][v2];
	}

	//�������� ����
	class EdgeIterator
	{
		bool end;
		GraphMatrixForm* f;
	public:
		int pozI, pozJ;
		EdgeIterator(GraphMatrixForm* f)
		{
			this->f = f;
			begin();
		}

		bool begin()
		{
			for (int i = 0; i < f->matrix.size(); ++i)
				for (int j = 0; j < f->matrix.size(); ++j)
					if (f->matrix[i][j])
					{
						pozI = i;
						pozJ = j;
						end = false;
						return true;
					}
			end = true;
			return false;
		}

		bool onEnd() { return end; }

		bool toend()
		{
			for (int i = f->matrix.size() - 1; i >= 0; --i)
				for (int j = f->matrix.size() - 1; j >= 0; --j)
					if (f->matrix[i][j]) {
						pozI = i;
						pozJ = j;
						end = false;
						return true;
					}
			end = true;
			return false;
		}

		bool next()
		{
			if (end)
				return false;
			++pozJ;
			while (pozI < f->matrix.size()) {
				while (pozJ < f->matrix.size()) {
					if (f->matrix[pozI][pozJ])
						return true;
					++pozJ;
				}
				++pozI;
				pozJ = (f->directed ? 0 : pozI + 1);
			}
			end = true;
			return true;
		}

		EdgeT* getEdge()
		{
			if (end)
				throw 1;
			if (!(f->matrix[pozI][pozJ]))
				throw 1;
			return f->matrix[pozI][pozJ];
		}
	};

	//�������� ��������� ����
	class OutputEdgeIterator
	{
		int pozI, pozJ;
		bool end;
		GraphMatrixForm* f;
	public:
		OutputEdgeIterator(GraphMatrixForm* f, int vIndex)
		{
			this->f = f;
			pozI = vIndex;
			begin();
		}

		bool begin()
		{
			for (pozJ = 0; pozJ < f->matrix.size(); pozJ++)
				if (f->matrix[pozI][pozJ]) {
					end = false;
					return true;
				}
			end = true;
			return false;
		}

		bool toend()
		{
			for (pozJ = f->matrix.size() - 1; pozJ >= 0; --pozJ)
				if (f->matrix[pozI][pozJ]) {
					end = false;
					return true;
				}
			end = true;
			return false;
		}

		bool onEnd()
		{
			return end;
		}

		bool next()
		{
			if (end)
				return false;
			++pozJ;
			while (pozJ < f->matrix.size()) {
				if (f->matrix[pozI][pozJ])
					return true;
				++pozJ;
			}
			end = true;
			return true;
		}

		EdgeT* getEdge()
		{
			if (end)
				throw 1;
			return f->matrix[pozI][pozJ];
		}
	};
};

//����� ������������� ������
template <class EdgeT> class GraphListForm : public GraphForm < EdgeT > {
	friend class Node;
	//������� ������
	class Node
	{
	public:
		EdgeT* edge; //���� �����
		int v2;      //������ �������, ������� ����� ���������
	};

	bool directed;
	vector<list<Node>> vecList; //������ ���������
public:
	GraphListForm(bool directed) : directed(directed) {}

	vector<vector<EdgeT*>> getMatrix() {
		return vector<vector<EdgeT*>>();
	}

	//������� � �������� ������ � ����
	bool InsertV(int index)
	{
		int size = vecList.size(); //������� ����� ������
		if (index < 0 || index > size) //�������� ����� �������
			return false;
		//������ ����� ������ ���������
		list<Node> newList;
		//���������
		vecList.insert(vecList.begin() + index, newList);
		++size;
		//��������� �����������
		for (int i = 0; i < size; ++i) {
			typename list<Node> ::iterator j;
			j = vecList[i].begin();
			for (; j != vecList[i].end(); ++j)
				if ((*j).v2 >= index)//���� ������� ������� ����� ������� �����, ��� �����������,
					++((*j).v2);//�� ����������� ���� �����                   
		}
		return true;
	}

	bool DeleteV(int index)
	{
		int size = vecList.size(); //����� ������
		if (index < 0 || index >= size)  //�������� ����� �������
			return false;
		//������� �� ������� ������ � �����
		for (int i = 0; i < size; ++i)
			for (typename list<Node>::iterator j = vecList[i].begin(); j != vecList[i].end(); ++j)
				if ((*j).v2 == index)
				{
					vecList[i].erase(j);
					break;
				}
		//������� ������ ���������
		vecList.erase(vecList.begin() + index);//
		--size;//
		//��������� �����������
		for (int i = 0; i < size; ++i)//
			for (typename list<Node>::iterator j = vecList[i].begin(); j != vecList[i].end(); ++j)//
				if ((*j).v2 > index)//���� ������� ������� ����� ������� �����, ��� ���������,//
					--((*j).v2);//�� ��������� ���� �����//
		return true;
	}

	bool InsertE(int v1, int v2, EdgeT* t)
	{
		int size = vecList.size(); //����� ������
		if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//�������� ����� �������
			return false;
		if (v1 == v2 || hasEdge(v1, v2))  //����� ��� ����� ��� ����
			return false;
		//��������� �����
		Node node;
		node.edge = t;
		node.v2 = v2;
		vecList[v1].push_front(node);
		return true;
	}

	bool DeleteE(int v1, int v2)
	{
		int size = vecList.size(); //����� ������
		//�������� ����� �������
		if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
			return false;
		//����� ���
		if (v1 == v2 || hasEdge(v1, v2) == false)
			return false;
		//������� �����
		for (typename list<Node>::iterator j = vecList[v1].begin(); j != vecList[v1].end(); ++j)
			if ((*j).v2 == v2) {
				vecList[v1].erase(j);
				break;
			}
		return true;
	}

	//������� �������� � ��������� �� ������� ����
	int DeleteEsFromVertex(int index, bool directed)
	{
		int size = vecList.size(); //����� ������
		int deleted = 0;
		//�������� ����� �������
		if (index < 0 || index >= size)
			return 0;
		//������� ��������� � �������� ����
		for (int i = 0; i < size; ++i)
			for (typename list<Node>::iterator j = vecList[i].begin(); j != vecList[i].end(); ++j)
				if ((*j).v2 == index)
				{
					//������� ������������ �����
					if (!directed)
						for (typename list<Node>::iterator k = vecList[index].begin(); k != vecList[index].end(); ++k)
							if ((*k).v2 == i)
							{
								vecList[index].erase(k);
								break;
							}
					delete (*j).edge;
					vecList[i].erase(j);
					++deleted;
					break;
				}
		return deleted;
	}

	//�������� � ���������
	bool hasEdge(int v1, int v2)
	{
		int size = vecList.size(); //����� ������
		//�������� ����� �������
		if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
			return false;
		//�����
		if (v1 == v2)
			return false;
		for (typename list<Node>::iterator j = vecList[v1].begin(); j != vecList[v1].end(); ++j)
			if ((*j).v2 == v2)
				return true;
		return false;
	}

	EdgeT* getEdge(int v1, int v2)
	{
		int size = vecList.size(); //����� ������
		//�������� ����� �������
		if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
			throw 1;
		//�����
		if (v1 == v2)
			throw 1;
		for (typename list<Node>::iterator j = vecList[v1].begin(); j != vecList[v1].end(); ++j)
			if ((*j).v2 == v2)
				return (*j).edge;
		throw 1;
	}

	//�������� ����
	class EdgeIterator
	{
		int pozI;
		typename list<typename GraphListForm<EdgeT>::Node>::iterator pozJ;
		bool end;
		GraphListForm* f;
	public:
		EdgeIterator(GraphListForm* f)
		{
			this->f = f;
		}

		//���������� �������� ���� �� ��������� �����
		bool begin()
		{
			for (pozI = 0; pozI < f->vecList.size(); ++pozI)
				for (pozJ = f->vecList[pozI].begin(); pozJ != f->vecList[pozI].end(); ++pozJ)
					if ((*pozJ).edge) {
						end = false;
						return true;
					}
			end = true;
			return false;
		}

		bool onEnd()
		{
			return end;
		}

		//���������� �������� ���� �� �������� �����
		bool toend()
		{
			typename list<typename GraphListForm<EdgeT>::Node>::iterator prev_pozJ;
			for (pozI = 0; pozI < f->vecList.size(); ++pozI) {
				for (pozJ = f->vecList[pozI].begin(); pozJ != f->vecList[pozI].end(); ++pozJ) {
					if ((*pozJ).edge)
						prev_pozJ = pozJ;
					if (!(*prev_pozJ).edge) {
						end = true;
						return false;
					}
					else {
						end = false;
						pozJ = prev_pozJ;
						return true;
					}
				}
			}
		}

		//������� � ��������� �������
		bool next()
		{
			if (end)
				return false;
			++pozJ;
			while (pozI < f->vecList.size()) {
				while (pozJ != f->vecList[pozI].end()) {
					if ((*pozJ).edge && (f->directed || !f->directed && (*pozJ).v2 > pozI))
						return true;
					++pozJ;
				}
				++pozI;
				if (pozI < f->vecList.size())
					pozJ = f->vecList[pozI].begin();
			}
			end = true;
			return true;
		}

		EdgeT* getEdge() {
			if (end)
				throw 1;
			return (*pozJ).edge;
		}


	};

	//�������� ��������� ����
	class OutputEdgeIterator
	{
	private:
		int pozI;
		typename list<typename GraphListForm<EdgeT>::Node>::iterator pozJ;
		bool end;
		GraphListForm* f;
	public:
		OutputEdgeIterator(GraphListForm* f, int vIndex)
		{
			this->f = f;
			pozI = vIndex;
			begin();
		}

		bool begin()
		{
			for (pozJ = f->vecList[pozI].begin(); pozJ != f->vecList[pozI].end(); ++pozJ)
				if ((*pozJ).edge) {
					end = false;
					return true;
				}
			end = true;
			return false;
		}

		bool onEnd()
		{
			return end;
		}

		bool toend()
		{
			typename list<typename GraphListForm<EdgeT>::Node>::iterator prev_pozJ;
			for (pozJ = f->vecList[pozI].begin(); pozJ != f->vecList[pozI].end(); ++pozJ)
				if ((*pozJ).edge)
					prev_pozJ = pozJ;
			if (!(*prev_pozJ).edge) {
				end = true;
				return false;
			}
			else {
				end = false;
				pozJ = prev_pozJ;
				return true;
			}
		}

		bool next()
		{
			if (end)
				return false;
			++pozJ;
			while (pozJ != f->vecList[pozI].end()) {
				if ((*pozJ).edge)
					return true;
				++pozJ;
			}
			end = true;
			return true;
		}

		EdgeT* getEdge()
		{
			if (end)
				throw 1;
			return (*pozJ).edge;
		}
	};
};

template<class EdgeT>
inline vector<vector<EdgeT*>> GraphMatrixForm<EdgeT>::getMatrix()
{
	return this->matrix;
}
