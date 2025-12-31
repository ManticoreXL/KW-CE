#pragma once
#include "TermsListNode.h"

class TermsLIST
{
private:
	TermsListNode* m_head;

public:
	TermsLIST();
	~TermsLIST();

	TermsListNode* getHead() { return m_head; }

	void insert(string& name, int age, Date& date, Type type);
	stringstream& print(Type type);
	void remove(string& name);
};
