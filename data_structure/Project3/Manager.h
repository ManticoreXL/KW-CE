#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager{	
private:
	Graph* graph;	
	ofstream fout;	
	int load;

public:
	Manager();	
	~Manager();	

	void run(const char * command_txt);
	
	bool LOAD(const char* filename);	
	bool PRINT();	
	bool mBFS(char option, int vertex);	
	bool mDFS(char option, int vertex);	
	bool mKWANGWOON(int vertex);	
	bool mKRUSKAL();
	bool mDIJKSTRA(char option, int vertex);
	bool mBELLMANFORD(char option, int s_vertex, int e_vertex);	
	bool mFLOYD(char option); 
	void printSuccessCode(string cmd);
	void printErrorCode(int n); 
};

#endif