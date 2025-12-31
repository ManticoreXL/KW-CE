#include "TermsList.h"

// Constructor
TermsLIST::TermsLIST()
{
	m_head = nullptr;
}

// Destructor
// Visit every node and delete one by one.
TermsLIST::~TermsLIST()
{
	TermsListNode* temp;
	while (m_head != nullptr)
	{
		temp = m_head;
		m_head = m_head->getNext();
		delete temp;
	}
}

// Insert a member to TermsBST.
void TermsLIST::insert(string& name, int age, Date& date, Type type)
{
	// Case 1: TermsLIST is empty.
	if (m_head == nullptr)
	{
		m_head = new TermsListNode(type);
		m_head->insertmember(name, age, date);
		return;
	}

	// Case 2: Type already exists in TermsLIST.
	TermsListNode* temp = nullptr;
	for (TermsListNode* curr = m_head; 
		curr;
		curr = curr->getNext())
	{
		if (curr->getType() == type)
		{
			curr->insertmember(name, age, date);
			return;
		}
		if (curr->getNext() == nullptr)
			temp = curr;
	}

	// Case 3: Create a new list node of type.
	temp->setNext(new TermsListNode(type));
	temp->getNext()->insertmember(name, age, date);
}

// Print BST (type).
stringstream& TermsLIST::print(Type type)
{
	for (TermsListNode* curr = m_head; 
		curr; 
		curr = curr->getNext()) 
	{
		if (curr->getType() == type) 
			return curr->printBST();
	}
	throw "TermLIST::print(Type type)";
}

// Remove a BST Node that name matches.
void TermsLIST::remove(string& name)
{
	// If list is empty.
	if (m_head == nullptr)
	{
		throw "TermsLIST::remove(string& name)";
		return;
	}

	// Remove indicator
	bool removed = false;

	for (TermsListNode* curr = m_head, *prev = nullptr;
		curr;)
	{

		removed = removed || curr->remove(name);

		// Remove list node if it is empty
		if (curr->getMembers() == 0)
		{
			// Case 1: first node is empty
			if (prev == nullptr)
			{
				m_head = curr->getNext();
				delete curr;
				curr = m_head;
			}
			// Case 2: middle or last node is empty
			else
			{
				prev->setNext(curr->getNext());
				delete curr;
				curr = prev->getNext();
			}
		}
		else // Move forward
		{
			prev = curr;
			curr = curr->getNext();
		}
	}

	// If no node deleted 
	if (removed == false)
	{
		throw "TermsLIST::remove(string& name)";
	}
}