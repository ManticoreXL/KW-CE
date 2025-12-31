#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <iostream>
#include <fstream>
using namespace std;

class Manager
{
private:

	ifstream fcmd;
	ofstream flog;
	MemberQueue m_mq;
	TermsLIST m_tlist;
	NameBST m_nbst;

public:
	Manager();
	~Manager();

	void run(const char* command);
	
	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	void Parser(string& data);
	void PUSH(string& name, int age, string& date, Type type);

	void LOAD();
	void ADD(string& data);
	void QPOP();
	void SEARCH(string& name);
	void PRINT();
	void PRINT(Type type);
	void DELETE(string& name);
};
