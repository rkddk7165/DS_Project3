#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{

}

MatrixGraph::~MatrixGraph()
{

}

void MatrixGraph::getAdjacentEdges(int vertex, std::map<int, int>* m) {
    m->clear();  // ������ �����͸� �ʱ�ȭ

    // vertex�� ����� �������� m�� �߰�
    for (int i = 1; i < m_Size+1; ++i) {
        if (m_Mat[vertex][i] != 0) {
            (*m)[i] = m_Mat[vertex][i];
        }
    }

    // �ٸ� �������� vertex�� ������ �������� m�� �߰�
    for (int i = 1; i < m_Size+1; ++i) {
        if (m_Mat[i][vertex] != 0) {
            (*m)[i] = m_Mat[i][vertex];
        }
    }

}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, std::map<int, int>* m) {
    m->clear();  // ������ �����͸� �ʱ�ȭ

    // vertex���� ������ �������� m�� �߰�
    for (int i = 1; i < m_Size+1; ++i) {
        if (m_Mat[vertex][i] != 0) {
            (*m)[i] = m_Mat[vertex][i];
        }
    }

    
}

void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	
}

////// PRINT ��ɾ� �Լ� /////
bool MatrixGraph::printGraph(ofstream* fout)
{
    *fout << "     ";
    for (int i = 1; i <= m_Size; ++i)
        *fout << "[" << i << "] ";
    *fout << endl;

    for (int i = 1; i <= m_Size; ++i)
    {
        *fout << "[" << i << "] ";
        for (int j = 1; j <= m_Size; ++j)
        {
            *fout << m_Mat[i][j] << " ";
        }
        *fout << endl;
    }
    return true;
}

void MatrixGraph::LOAD(const char* filename)
{
    if (m_Mat != nullptr) // �׷����� �̹� �����ϸ� ����
    {
        for (int i = 0; i <= m_Size; ++i)
            delete[] m_Mat[i];
        delete[] m_Mat;
        m_Mat = nullptr;
    }

    ifstream fin(filename); // ���� ����
    if (!fin)
    {
        cout << "���� ���� ����: " << filename << endl;
        return;
    }

    // �׷��� Ÿ��(M: Matrix) �б�
    char graphType;
    fin >> graphType;

    // �׷��� ũ�� �б�
    int size;
    fin >> size;
    setSize(size);

    // ���ο� ��� ����
    m_Mat = new int* [size + 1];
    for (int i = 0; i <= size; ++i)
        m_Mat[i] = new int[size + 1];

    for (int i = 1; i <= size; ++i)
    {
        for (int j = 1; j <= size; ++j)
        {
            fin >> m_Mat[i][j];
        }
    }

    fin.close();
}

