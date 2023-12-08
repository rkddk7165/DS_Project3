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

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	

}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
	
}

void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	
}

////// PRINT 명령어 함수 /////
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
    if (m_Mat != nullptr) // 그래프가 이미 존재하면 삭제
    {
        for (int i = 0; i <= m_Size; ++i)
            delete[] m_Mat[i];
        delete[] m_Mat;
        m_Mat = nullptr;
    }

    ifstream fin(filename); // 파일 열기
    if (!fin)
    {
        cout << "파일 열기 오류: " << filename << endl;
        return;
    }

    // 그래프 타입(M: Matrix) 읽기
    char graphType;
    fin >> graphType;

    // 그래프 크기 읽기
    int size;
    fin >> size;
    setSize(size);

    // 새로운 행렬 생성
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

