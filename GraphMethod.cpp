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
    // �湮 ���θ� �����ϴ� �迭
    int size = graph->getSize() + 1;
    bool* visited = new bool[size];
    fill(visited, visited + size, false);

    // BFS�� ���� ť
    queue<int> bfsQueue;

    // �湮�� ������ ť�� �����ϰ� �湮 ���θ� üũ
    bfsQueue.push(vertex);
    visited[vertex] = true;

    // ����� ����� ���ڿ�
    string result;

    // BFS Ž��
    while (!bfsQueue.empty()) {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();

        // ���� ���� ���
        result += to_string(currentVertex) + " -> ";

        // ���� ������ ����� �������� ť�� �����ϰ� �湮 ���θ� üũ
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

    // ������ ȭ��ǥ ����
    result = result.substr(0, result.length() - 4);

    // ����� log.txt�� ���
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

    delete[] visited;  // ���� �Ҵ��� �迭�� ����

    return true;
}

bool DFS(Graph* graph, char option, int vertex, bool* visited)
{
    // �湮�� ������ ���
    fout << vertex << " -> ";

    //�湮�� ���� üũ
    visited[vertex] = true;

    // ���� ������ ����� �������� ������
    map<int, int> adjEdges;
    if (option == 'N') {
        graph->getAdjacentEdges(vertex, &adjEdges);
    }
    else if (option == 'Y') {
        graph->getAdjacentEdgesDirect(vertex, &adjEdges);
    }

    // ����� �������� �� ���� ������ �켱���� ����
    vector<pair<int, int>> sortedEdges(adjEdges.begin(), adjEdges.end());
    sort(sortedEdges.begin(), sortedEdges.end(),
        [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first;
        });

    // ���ĵ� �����鿡 ���� ��� ȣ��
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
    // �湮 ���θ� �����ϴ� �迭
    int size = graph->getSize() + 1;
    bool* visited = new bool[size];
    fill(visited, visited + size, false);

    // ���� �������� DFS ȣ��
    fout << "======== DFS ========" << endl;
    fout << "(" << (option == 'Y' ? "Directed" : "Undirected") << ") Graph DFS result" << endl;
    fout << "startvertex: " << startVertex << endl;
    DFS(graph, option, startVertex, visited);
    fout << endl << "=====================" << endl;

    // �迭 ����
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
    // �׷����� ���� ��
    int vertices = graph->getSize();

    // �������� ������ ����
    vector<Edge> edges;

    // �׷����� ��� ������ �����Ͽ� ���Ϳ� ����
    for (int i = 1; i <= vertices; ++i) {
        map<int, int> adjEdges;
        graph->getAdjacentEdges(i, &adjEdges);

        for (const auto& edge : adjEdges) {
            int destVertex = edge.first;
            int weight = edge.second;
            edges.push_back(Edge(i, destVertex, weight));
        }
    }

    // ������ weight�� �������� �������� ����
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    // �� ������ ���� �׷��� ��Ÿ���� �迭
    vector<int> parent(vertices + 1, -1);

    // ����� ������ ����
    vector<Edge> result;

    // ũ�罺Į �˰��� ����
    for (const Edge& edge : edges) {
        int startRoot = find(edge.startVertex, parent);
        int destRoot = find(edge.destVertex, parent);

        // ����Ŭ�� �߻����� ������ ����
        if (startRoot != destRoot) {
            result.push_back(edge);

            // �� �׷��� �ϳ��� ��ħ
            unionSets(startRoot, destRoot, parent);
        }
    }

    // ����� ���� ���� ������������ �����Ͽ� ���
    sort(result.begin(), result.end(), [](const Edge& a, const Edge& b) {
        return a.startVertex < b.startVertex;
        });

    // ��� ���
    fout << "====== Kruskal =======" << endl;
    for (const Edge& edge : result) {
        fout << "[" << edge.startVertex << "] " << edge.destVertex << "(" << edge.weight << ")" << endl;
    }

    // cost ���
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