#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

Manager::Manager()	
{
	graph = nullptr;	
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt){
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode
		
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}


    // ��ɾ� �б�
    string cmd;
    while (getline(fin, cmd)) {
        istringstream iss(cmd);
        string command;
        iss >> command;

        if (command == "LOAD") {
            string graphType;
            iss >> graphType;

            if (graphType == "graph_L") {
                if (LOAD("graph_L.txt")) {
                    fout << "========== LOAD ==========" << endl << "SUCCESS" << endl << "==========================" << endl;
                }
                else {
                    printErrorCode(100);
                }
            }
            else if (graphType == "graph_M") {
                if (LOAD("graph_M.txt")) {
                    fout << "========== LOAD ==========" << endl << "SUCCESS" << endl << "==========================" << endl;
                }
                else {
                    printErrorCode(100);
                }
            }
            else {
                printErrorCode(100);
            }
        }
        else if (command == "PRINT") {
            PRINT();
        }
        else if (command == "BFS") {
            char option;
            int vertex;
            iss >> option >> vertex;

            if (option == 'Y' || option == 'N') {
                if (!mBFS(option, vertex)) {
                    printErrorCode(300);
                }
            }
            else {
                printErrorCode(300);
            }
        }

        else if (command == "DFS") {
            char option;
            int vertex;
            iss >> option >> vertex;

            if (option == 'Y' || option == 'N') {
                if (!mDFS(option, vertex)) {
                    printErrorCode(400);
                }
            }
            else {
                printErrorCode(400);
            }
        }

        else if (command == "KRUSKAL") {
              mKRUSKAL();
        }
    }

    fin.close();
    return;
}

bool Manager::LOAD(const char* filename)
{
    if (graph != nullptr)
    {
        delete graph;
        graph = nullptr;
    }

    char graphType;
    int size;
    ifstream fin(filename);

    if (!fin)
    {
        printErrorCode(100);
        return false;
    }

    fin >> graphType;
    fin >> size;

    if (graphType == 'L')
    {
        graph = new ListGraph(false, size);
        ListGraph* listGraph = dynamic_cast<ListGraph*>(graph);
        if (listGraph)
        {
            listGraph->LOAD("graph_L.txt");
            load = 1; // �׷����� �ε��
        }
    }

    else if (graphType == 'M')
    {
        graph = new MatrixGraph(true, size);
        MatrixGraph* matrixGraph = dynamic_cast<MatrixGraph*>(graph);
        if (matrixGraph)
        {
            matrixGraph->LOAD("graph_M.txt");
            load = 1; // �׷����� �ε��
        }
    }
    else
    {
        
        return false;
    }

    fin.close();
    return true;
}

bool Manager::PRINT()
{
    if (graph == nullptr)
    {
        printErrorCode(200); // �׷��� ������ �������� ����
        return false;
    }

    // ��� ���Ͽ� ��� ���
    fout << "======== PRINT ========" << endl;

    if (graph->getType() == 0) // List �׷��� ���
    {
        ListGraph* listGraph = dynamic_cast<ListGraph*>(graph);
        if (listGraph)
        {
            listGraph->printGraph(&fout);
        }
    }
    else if (graph->getType() == 1) // Matrix �׷��� ���
    {
        MatrixGraph* matrixGraph = dynamic_cast<MatrixGraph*>(graph);
        if (matrixGraph)
        {
            matrixGraph->printGraph(&fout);
        }
    }

    fout << "=====================" << endl;
    return true;
}

bool Manager::mBFS(char option, int vertex)
{
    // �׷����� �ε�Ǿ� ���� ���� ���
    if (!load) {
        printErrorCode(300);
        return false;
    }

    // ���⼺ ����
    bool isDirected = (option == 'Y');

    // �׷����� Ÿ�Կ� ���� ������ �Լ� ȣ��
    if (graph->getType() == false) {  // ListGraph
        // ListGraph�� BFS �Լ� ȣ��
        ListGraph* listGraph = dynamic_cast<ListGraph*>(graph);
        if (listGraph) {
            // ListGraph�� BFS �Լ� ȣ��
            BFS(listGraph, option, vertex);
        }
        else printErrorCode(300);
    }
    else if (graph->getType() == true) { //MatrixGraph
        MatrixGraph* matrixGraph = dynamic_cast<MatrixGraph*>(graph);
            if (matrixGraph) {
                // MatrixGraph�� BFS �Լ� ȣ��
                BFS(matrixGraph, option, vertex);
            }
            else {
                printErrorCode(300);
            }

    }
    else {  // MatrixGraph
        // MatrixGraph�� BFS �Լ� ȣ��
        if (!BFS(graph, isDirected, vertex)) {
            printErrorCode(101);  // BFS �Լ� ȣ�� ����
            return false;
        }
    }

    return true;
}



bool Manager::mDFS(char option, int vertex)	
{
    // �׷����� �ε�Ǿ� ���� ���� ���
    if (!load) {
        printErrorCode(400);
        return false;
    }

    // ���⼺ ����
    bool isDirected = (option == 'Y');

    // �׷����� Ÿ�Կ� ���� ������ �Լ� ȣ��
    if (graph->getType() == false) {  // ListGraph
        // ListGraph�� BFS �Լ� ȣ��
        ListGraph* listGraph = dynamic_cast<ListGraph*>(graph);
        if (listGraph) {
            // ListGraph�� BFS �Լ� ȣ��
            DFS(listGraph, option, vertex);
        }
        else printErrorCode(400);
    }
    else if (graph->getType() == true) { //MatrixGraph
        MatrixGraph* matrixGraph = dynamic_cast<MatrixGraph*>(graph);
        if (matrixGraph) {
            // MatrixGraph�� BFS �Լ� ȣ��
            DFS(matrixGraph, option, vertex);
        }
        else {
            printErrorCode(400);
        }

    }
    else {  // MatrixGraph
        // MatrixGraph�� BFS �Լ� ȣ��
        if (!BFS(graph, isDirected, vertex)) {
            printErrorCode(400);  // BFS �Լ� ȣ�� ����
            return false;
        }
    }

    return true;
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
    return true;
}

bool Manager::mKRUSKAL()
{
    // �׷����� �ε�Ǿ� ���� ���� ���
    if (!load) {
        printErrorCode(300);
        return false;
    }

    // �׷����� Ÿ�Կ� ���� ������ �Լ� ȣ��
    if (graph->getType() == 0) {  // ListGraph
        ListGraph* listGraph = dynamic_cast<ListGraph*>(graph);
        if (!Kruskal(listGraph)) {
            printErrorCode(500);  // KRUSKAL �Լ� ȣ�� ����
            return false;
        }
    }
    else {  // MatrixGraph
        MatrixGraph* matrixGraph = dynamic_cast<MatrixGraph*>(graph);
        if (!Kruskal(matrixGraph)) {
            printErrorCode(500);  // KRUSKAL �Լ� ȣ�� ����
            return false;
        }
    }

    return true;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
    return true;
}

bool Manager::mFLOYD(char option)
{
    return true;
}

bool Manager::mKwoonWoon(int vertex) 
{
    return true;
}

void Manager::printErrorCode(int n)
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
    return;
}


