#pragma once
#include "TermsBSTNode.h"

class TermsBST
{
private:
	TermsBSTNode* m_root;

protected: // Domestic functions
	void recursivedelete(TermsBSTNode* root);
	void recursiveprint(TermsBSTNode* root, stringstream& s);
	bool remove(TermsBSTNode* root, TermsBSTNode* parent, string& name);

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot() { return m_root; }

	void insert(string& name, int age, Date& date, Date& exdate);
	stringstream& print();
	bool remove(string& name);
};