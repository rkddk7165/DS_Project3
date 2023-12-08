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
        std::cout << "유효하지 않은 정점입니다." << std::endl;
        return;
    }

    // 방향 그래프이므로 from에서 to로의 간선만 추가
    m_List[from][to] = weight;

    // 무방향 그래프인 경우 to에서 from으로의 간선도 추가
    if (!m_Type)
    {
        m_List[to][from] = weight;
    }
}

////// PRINT 명령어 함수 /////
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
    if (m_List != nullptr) // 그래프가 이미 존재하면 삭제
    {
        delete[] m_List;
        m_List = nullptr;
    }

    ifstream fin(filename); // 파일 열기
    if (!fin)
    {
        cout << "파일 열기 오류: " << filename << endl;
        return;
    }

    // 그래프 타입(L: List) 읽기
    char graphType;
    fin >> graphType;

    // 그래프 크기 읽기
    int size;
    fin >> size;
    setSize(size);

    // 새로운 인접 리스트 생성
     m_List = new map<int, int>[size + 1];

     int from, to, weight, vertex;

    while (fin >> from)
    {
        // 형식 1: 시작 정점만 있는 경우
        if (fin.peek() == '\n')
        {
            fin >> to >> weight;
            insertEdge(from, to, weight);
        }
        else
        {
            // 형식 2: 도착 정점과 가중치가 있는 경우
            while (fin >> to >> weight)
            {
                // 정점이 존재하지 않는 경우에만 추가
                if (m_List[from].empty())
                    m_List[from][0] = 0; // 0으로 표시하여 정점 추가

                // 간선 추가
                m_List[from][to] = weight;

                // 개행 문자를 만나면 반복문 종료
                if (fin.peek() == '\n')
                {
                    fin.ignore(); // 개행 문자 무시
                    break;
                }
            }
        }
    }

    //while (fin >> from)
    //{
    //    if (from == 0) // 파일의 끝
    //        break;

    //    fin >> to >> weight;

    //    insertEdge(from, to, weight);
    //}

    fin.close();
    return;
}