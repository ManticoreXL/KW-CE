#pragma once
#include "NameBSTNode.h"

class NameBST
{
private:
	NameBSTNode* m_root;

protected: // Domestic function
	void recursivedelete(NameBSTNode* root);
	void recursiveprint(NameBSTNode* root, stringstream& s);
	bool remove(NameBSTNode* node, NameBSTNode* parent, string& name);

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot() { return m_root; }

	void insert(string& name, int age, Date& date, Date& exdate);
	stringstream& print();
	stringstream& print(string& name);
	bool remove(string& name);
};