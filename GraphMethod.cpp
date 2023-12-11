#include <iostream>
#include <string>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;

ofstream fout("log.txt", ios::app);

bool BFS(Graph* graph, char option, int vertex)
{
    // 방문 여부를 저장하는 배열
    int size = graph->getSize() + 1;
    bool* visited = new bool[size];
    fill(visited, visited + size, false);

    // BFS를 위한 큐
    queue<int> bfsQueue;

    // 방문한 정점을 큐에 삽입하고 방문 여부를 체크
    bfsQueue.push(vertex);
    visited[vertex] = true;

    // 결과를 기록할 문자열
    string result;

    // BFS 탐색
    while (!bfsQueue.empty()) {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();

        // 현재 정점 기록
        result += to_string(currentVertex) + " -> ";

        // 현재 정점과 연결된 정점들을 큐에 삽입하고 방문 여부를 체크
        map<int, int> adjEdges;
        if (option == 'N') {
            graph->getAdjacentEdges(currentVertex, &adjEdges);
        }
        else if (option == 'Y') {
            graph->getAdjacentEdgesDirect(currentVertex, &adjEdges);
        }

        for (const auto& edge : adjEdges) {
            int adjacentVertex = edge.first;
            if (!visited[adjacentVertex]) {
                bfsQueue.push(adjacentVertex);
                visited[adjacentVertex] = true;
            }
        }
    }

    // 마지막 화살표 삭제
    result = result.substr(0, result.length() - 4);

    // 결과를 log.txt에 출력
    ofstream fout("log.txt", ios::app);
    if (fout.is_open()) {
        fout << "======== BFS ========" << endl;
        fout << "(" << (option == 'Y' ? "Directed" : "Undirected") << ") Graph BFS result" << endl;
        fout << "startvertex: " << vertex << endl;
        fout << result << endl;
        fout << "=====================" << endl;
        fout.close();
    }
    else {
        fout << "Error opening log.txt" << endl;
    }

    delete[] visited;  // 동적 할당한 배열을 삭제

    return true;
}

bool DFS(Graph* graph, char option, int vertex, bool* visited)
{
    // 방문한 정점을 출력
    fout << vertex << " -> ";

    //방문한 정점 체크
    visited[vertex] = true;

    // 현재 정점과 연결된 정점들을 가져옴
    map<int, int> adjEdges;
    if (option == 'N') {
        graph->getAdjacentEdges(vertex, &adjEdges);
    }
    else if (option == 'Y') {
        graph->getAdjacentEdgesDirect(vertex, &adjEdges);
    }

    // 연결된 정점들을 더 작은 정점을 우선으로 정렬
    vector<pair<int, int>> sortedEdges(adjEdges.begin(), adjEdges.end());
    sort(sortedEdges.begin(), sortedEdges.end(),
        [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first;
        });

    // 정렬된 정점들에 대해 재귀 호출
    for (const auto& edge : sortedEdges) {
        int adjacentVertex = edge.first;
        if (!visited[adjacentVertex]) {
            DFS(graph, option, adjacentVertex, visited);
        }
    }

    return true;
}
// DFS driver
bool DFS(Graph* graph, char option, int startVertex)
{
    // 방문 여부를 저장하는 배열
    int size = graph->getSize() + 1;
    bool* visited = new bool[size];
    fill(visited, visited + size, false);

    // 시작 정점부터 DFS 호출
    fout << "======== DFS ========" << endl;
    fout << "(" << (option == 'Y' ? "Directed" : "Undirected") << ") Graph DFS result" << endl;
    fout << "startvertex: " << startVertex << endl;
    DFS(graph, option, startVertex, visited);
    fout << endl << "=====================" << endl;

    // 배열 해제
    delete[] visited;

    return true;
}


struct Edge {
    int startVertex;
    int destVertex;
    int weight;

    Edge(int start, int dest, int w) : startVertex(start), destVertex(dest), weight(w) {}
};



int find(int vertex, vector<int>& parent) {
    if (parent[vertex] == -1) {
        return vertex;
    }
    return find(parent[vertex], parent);
}

void unionSets(int root1, int root2, vector<int>& parent) {
    if (root1 != root2) {
        parent[root1] = root2;
    }
}

bool Kruskal(Graph* graph) {
    // 그래프의 정점 수
    int vertices = graph->getSize();

    // 간선들을 저장할 벡터
    vector<Edge> edges;

    // 그래프의 모든 간선을 추출하여 벡터에 저장
    for (int i = 1; i <= vertices; ++i) {
        map<int, int> adjEdges;
        graph->getAdjacentEdges(i, &adjEdges);

        for (const auto& edge : adjEdges) {
            int destVertex = edge.first;
            int weight = edge.second;
            edges.push_back(Edge(i, destVertex, weight));
        }
    }

    // 간선을 weight를 기준으로 오름차순 정렬
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    // 각 정점이 속한 그룹을 나타내는 배열
    vector<int> parent(vertices + 1, -1);

    // 결과를 저장할 벡터
    vector<Edge> result;

    // 크루스칼 알고리즘 수행
    for (const Edge& edge : edges) {
        int startRoot = find(edge.startVertex, parent);
        int destRoot = find(edge.destVertex, parent);

        // 사이클이 발생하지 않으면 선택
        if (startRoot != destRoot) {
            result.push_back(edge);

            // 두 그룹을 하나로 합침
            unionSets(startRoot, destRoot, parent);
        }
    }

    // 결과를 시작 정점 오름차순으로 정렬하여 출력
    sort(result.begin(), result.end(), [](const Edge& a, const Edge& b) {
        return a.startVertex < b.startVertex;
        });

    // 결과 출력
    fout << "====== Kruskal =======" << endl;
    for (const Edge& edge : result) {
        fout << "[" << edge.startVertex << "] " << edge.destVertex << "(" << edge.weight << ")" << endl;
    }

    // cost 출력
    int totalWeight = 0;
    for (const Edge& edge : result) {
        totalWeight += edge.weight;
    }
    fout << "cost: " << totalWeight << endl;

    fout << "=====================" << endl;

    return true;
}

bool Dijkstra(Graph* graph, char option, int vertex)
{
	return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) 
{
	return true;
}

bool FLOYD(Graph* graph, char option)
{
	return true;
}

bool KWANGWOON(Graph* graph, int vertex)
{
	return true;
}