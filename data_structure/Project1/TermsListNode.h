#pragma once
#include"Date.h"
#include"TermsBST.h"

class TermsListNode
{
private:
	Type m_type;
	int m_members;
	TermsBST* m_BSTlinker;
	TermsListNode* m_next;


public:
	// Constructor
	TermsListNode(Type type)
	{
		m_type = type;
		m_members = 0;
		m_BSTlinker = new TermsBST;
		m_next = nullptr;
	}

	// Destructor
	~TermsListNode()
	{
		delete m_BSTlinker;
	}

	// Get functions
	Type getType() { return m_type; }
	int getMembers() { return m_members; }
	TermsListNode* getNext() { return m_next; }

	// Set functions
	void setNext(TermsListNode* next) { m_next = next; }

	// Insert member to TermsBST
	void insertmember(string& name, int age, Date& date)
	{
		Date exdate(date);
		exdate.addmonth(m_type);
		m_BSTlinker->insert(name, age, date, exdate);
		m_members++;
	}

	// Print list's BST.
	stringstream& printBST()
	{
		return m_BSTlinker->print();
	}

	// Function for DELETE
	bool remove(string& name)
	{
		if (m_BSTlinker->remove(name) == true)
		{
			m_members--;
			return true;
		}
		return false;
	}
};