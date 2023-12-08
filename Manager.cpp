#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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


    //명령어 읽기
    while (!fin.eof())
    {
        string cmd;
        if (!getline(fin, cmd))
        {
            break;
        }

        else if (cmd.substr(0,4) == "LOAD"){
            if (cmd.substr(5) == "graph_L") {
                if (LOAD("graph_L.txt")) {
                    fout << "========== LOAD ==========" << endl << "SUCCESS" << endl << "==========================" << endl;
                }
                else {
                    printErrorCode(100);
                }
            }
            else if (cmd.substr(5) == "graph_M") {
                if (LOAD("graph_M.txt")) {
                    fout << "========== LOAD ==========" << endl << "SUCCESS" << endl << "==========================" << endl;
                }
                else {
                    printErrorCode(100);
                }
            }
            else printErrorCode(100);
        }

        else if (cmd == "PRINT") {
            PRINT();
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
            load = 1; // 그래프가 로드됨
        }
    }

    else if (graphType == 'M')
    {
        graph = new MatrixGraph(true, size);
        MatrixGraph* matrixGraph = dynamic_cast<MatrixGraph*>(graph);
        if (matrixGraph)
        {
            matrixGraph->LOAD("graph_M.txt");
            load = 1; // 그래프가 로드됨
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
        printErrorCode(200); // 그래프 정보가 존재하지 않음
        return false;
    }

    // 출력 파일에 결과 기록
    fout << "======== PRINT ========" << endl;

    if (graph->getType() == 0) // List 그래프 출력
    {
        ListGraph* listGraph = dynamic_cast<ListGraph*>(graph);
        if (listGraph)
        {
            listGraph->printGraph(&fout);
        }
    }
    else if (graph->getType() == 1) // Matrix 그래프 출력
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
    return true;
}

bool Manager::mDFS(char option, int vertex)	
{
    return true;
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
    return true;
}

bool Manager::mKRUSKAL()
{
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


