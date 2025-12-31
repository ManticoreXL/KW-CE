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

	string input;
	
	// parse string into command and data
	while (getline(fin, input))
	{
		stringstream ss(input);
		string cmd;
		getline(ss, cmd, ' ');

		if (cmd == "LOAD")
		{
			string filename;
			getline(ss, filename, '\r');
			if (!LOAD(filename.c_str()))
				printErrorCode(100);
			else
				printSuccessCode("LOAD");
		}
		else if (cmd == "PRINT")
		{
			if (!PRINT())
				printErrorCode(200);
		}
		else if (cmd == "BFS")
		{
			string option, vertex;
			getline(ss, option, ' ');
			getline(ss, vertex, '\r');

			if (option == "" || vertex == "")
				printErrorCode(300);
			else
				if (!mBFS(option[0], stoi(vertex)))
					printErrorCode(300);
		}
		else if (cmd == "DFS")
		{
			string option, vertex;
			getline(ss, option, ' ');
			getline(ss, vertex, '\r');

			if (option == "" || vertex == "")
				printErrorCode(400);
			else
				if (!mDFS(option[0], stoi(vertex)))
					printErrorCode(400);
		}
		else if (cmd == "KWANGWOON")
		{
			if (!mKWANGWOON(1))
				printErrorCode(500);
		}
		else if (cmd == "KRUSKAL")
		{
			if (!mKRUSKAL())
				printErrorCode(600);
		}
		else if (cmd == "DIJKSTRA")
		{
			string option, vertex;
			getline(ss, option, ' ');
			getline(ss, vertex, '\r');

			if (option == "" || vertex == "")
				printErrorCode(700);
			else
				if (!mDIJKSTRA(option[0], stoi(vertex)))
					printErrorCode(700);
			
		}
		else if (cmd == "BELLMANFORD")
		{
			string option, start, end;
			getline(ss, option, ' ');
			getline(ss, start, ' ');
			getline(ss, end, '\r');

			if (option == "" || start == "" || end == "")
				printErrorCode(800);
			else
				if (!mBELLMANFORD(option[0], stoi(start), stoi(end)))
					printErrorCode(800);
		}
		else if (cmd == "FLOYD")
		{
			string option;
			getline(ss, option, ' ');

			if (option == "")
				printErrorCode(900);
			else
				if (!mFLOYD(option[0]))
					printErrorCode(900);
		}
		else if (cmd == "EXIT")
		{
			exit(0);
		}
		else // wrong command
		{
			printErrorCode(1000);
		}
	}
	
	fin.close();
	return;
}

bool Manager::LOAD(const char* filename)
{
	try
	{
		// open file
		ifstream fin(filename);
		if (fin.fail())
		{
			throw "bool Manager::LOAD(const char* filename) - invalid filename,";
			return false;
		}

		// graph is already existing, delete graph
		if (graph != nullptr)
			delete graph;

		// get type
		string gType;
		getline(fin, gType);

		if (gType == "L") // list graph
		{
			string sSize;
			getline(fin, sSize);

			int size = stoi(sSize);

			// make new list graph
			graph = new ListGraph(false, size);

			string data, vertex, weight;
			int from = 1;
			int to, w;

			while (getline(fin, data))
			{
				stringstream lss(data);
				weight = "";
				lss >> vertex >> weight;

				if (weight == "")
					from = stoi(vertex);
				else
				{
					to = stoi(vertex);
					w = stoi(weight);
					graph->insertEdge(from, to, w);
				}
			}
			
		}
		else if (gType == "M") // matrix graph
		{
			string sSize;
			getline(fin, sSize);

			int size = stoi(sSize);

			// make new matrix graph
			graph = new MatrixGraph(true, size);

			for (int i = 1; i < size + 1; i++)
			{
				string row;
				getline(fin, row);

				stringstream rss(row);

				// get matrix elem
				for (int j = 1; j < size + 1; j++)
				{
					string elem;
					if (j == size)
						getline(rss, elem, '\r');
					else
						getline(rss, elem, ' ');

					int weight = stoi(elem);

					if (weight != 0)
						graph->insertEdge(i, j, weight);
				}
			}
		}
		else
		{
			throw "bool Manager::LOAD(const char* filename) - invalid graph type.";
			return false;
		}
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(100);
	}

	// increase load indicator by 1
	load = load + 1;

	return true;
}

bool Manager::PRINT()	
{
	try
	{
		fout << "======== PRINT ========" << endl;
		graph->printGraph(&fout);
		fout << "=====================" << endl << endl;
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(200);
	}

	return true;
}

bool Manager::mBFS(char option, int vertex)
{
	try
	{
		fout << "======== BFS ========" << endl;

		if (option == 'Y')
			fout << "Directed Graph BFS result" << endl;
		else if (option == 'N')
			fout << "Undirected Graph BFS result" << endl;

		fout << "startvertex: " << vertex << endl;

		// call BFS graph method
		BFS(graph, option, vertex);

		fout << "=====================" << endl << endl;
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(300);
	}

	return true;
}

bool Manager::mDFS(char option, int vertex)	
{
	try
	{
		fout << "======== DFS ========" << endl;

		if (option == 'Y')
			fout << "Directed Graph DFS result" << endl;
		else if (option == 'N')
			fout << "Undirected Graph DFS result" << endl;

		fout << "startvertex: " << vertex << endl;

		// call DFS graph method
		DFS(graph, option, vertex);

		fout << "=====================" << endl << endl;
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(400);
	}

	return true;
}

bool Manager::mKWANGWOON(int vertex)
{
	try
	{
		if (graph->getType() == true)
		{
			throw"bool Manager::mKWANGWOON(int vertex) - matrix graph cannot execute KWANGWOON.";
			return false;
		}

		fout << "======== KWANGWOON========" << endl;
		fout << "startvertex: " << vertex << endl;
		// call KWANGWOON method
		KWANGWOON(graph, vertex);
		fout << "============================" << endl << endl;
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(500);
	}

	return true;
}

bool Manager::mKRUSKAL()
{
	try
	{
		fout << "====== Kruskal =======" << endl;
		// call Kruskal method
		Kruskal(graph);
		fout << "=====================" << endl << endl;
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(600);
	}

	return true;
}

bool Manager::mDIJKSTRA(char option, int vertex)
{
	try
	{
		fout << "====== Dijkstra =======" << endl;

		if (option == 'Y')
			fout << "Directed Graph Dijkstra result" << endl;
		else if (option == 'N')
			fout << "Undirected Graph Dijkstra result" << endl;

		// call Dijkstra method
		Dijkstra(graph, option, vertex);

		fout << "=====================" << endl << endl;
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(700);
	}

	return true;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
	try
	{
		fout << "====== Bellman-Ford =======" << endl;

		if (option == 'Y')
			fout << "Directed Graph Bellman-Ford result" << endl;
		else if (option == 'N')
			fout << "Undirected Graph Bellman-Ford result" << endl;

		// call BellmanFord method
		Bellmanford(graph, option, s_vertex, e_vertex);

		fout << "=====================" << endl << endl;
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(800);
	}

	return true;
}

bool Manager::mFLOYD(char option)
{
	try
	{
		fout << "======== FLOYD ========" << endl;

		if (option == 'Y')
			fout << "Directed Graph FLOYD result" << endl;
		else if (option == 'N')
			fout << "Undirected Graph FLOYD result" << endl;

		// call FLOYD method
		FLOYD(graph, option);

		fout << "=====================" << endl << endl;
	}
	catch (const char* err)
	{
		cout << err << endl;
		printErrorCode(900);
	}

	return true;
}

void Manager::printSuccessCode(string cmd)
{
	fout << "========== " << cmd << " ==========" << endl;
	fout << "Success" << endl;
	fout << "==========================" << endl << endl;
}

void Manager::printErrorCode(int n)
{
	fout << "======== ERROR =======" << endl;
	fout << n << endl;
	fout << "====================" << endl << endl;
}

