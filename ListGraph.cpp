#include "ListGraph.h"
#include <iostream>
#include <fstream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	
}

ListGraph::~ListGraph()	
{
	
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
    return;
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
    return;
}

void ListGraph::insertEdge(int from, int to, int weight)
{
    if (from < 1 || from > m_Size || to < 1 || to > m_Size)
    {
        std::cout << "��ȿ���� ���� �����Դϴ�." << std::endl;
        return;
    }

    // ���� �׷����̹Ƿ� from���� to���� ������ �߰�
    m_List[from][to] = weight;

    // ������ �׷����� ��� to���� from������ ������ �߰�
    if (!m_Type)
    {
        m_List[to][from] = weight;
    }
}

////// PRINT ��ɾ� �Լ� /////
bool ListGraph::printGraph(ofstream* fout)
{
    for (int i = 1; i <= m_Size; ++i)
    {
        *fout << "[" << i << "] -> ";
        for (auto it = m_List[i].begin(); it != m_List[i].end(); ++it)
        {
            if (it != m_List[i].begin())
                *fout << " -> ";
            *fout << "(" << it->first << "," << it->second << ")";
        }
        *fout << endl;
    }
    return true;
}

void ListGraph::LOAD(const char* filename)
{
    if (m_List != nullptr) // �׷����� �̹� �����ϸ� ����
    {
        delete[] m_List;
        m_List = nullptr;
    }

    ifstream fin(filename); // ���� ����
    if (!fin)
    {
        cout << "���� ���� ����: " << filename << endl;
        return;
    }

    // �׷��� Ÿ��(L: List) �б�
    char graphType;
    fin >> graphType;

    // �׷��� ũ�� �б�
    int size;
    fin >> size;
    setSize(size);

    // ���ο� ���� ����Ʈ ����
     m_List = new map<int, int>[size + 1];

     int from, to, weight, vertex;

    while (fin >> from)
    {
        // ���� 1: ���� ������ �ִ� ���
        if (fin.peek() == '\n')
        {
            fin >> to >> weight;
            insertEdge(from, to, weight);
        }
        else
        {
            // ���� 2: ���� ������ ����ġ�� �ִ� ���
            while (fin >> to >> weight)
            {
                // ������ �������� �ʴ� ��쿡�� �߰�
                if (m_List[from].empty())
                    m_List[from][0] = 0; // 0���� ǥ���Ͽ� ���� �߰�

                // ���� �߰�
                m_List[from][to] = weight;

                // ���� ���ڸ� ������ �ݺ��� ����
                if (fin.peek() == '\n')
                {
                    fin.ignore(); // ���� ���� ����
                    break;
                }
            }
        }
    }

    //while (fin >> from)
    //{
    //    if (from == 0) // ������ ��
    //        break;

    //    fin >> to >> weight;

    //    insertEdge(from, to, weight);
    //}

    fin.close();
    return;
}