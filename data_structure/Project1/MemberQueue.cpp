#include "MemberQueue.h"

// Constructor
MemberQueue::MemberQueue()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}

// Destructor
MemberQueue::~MemberQueue()
{
	// Visit every node and delete.
	MemberQueueNode* temp = m_head;
	while (temp != nullptr)
	{
		m_head = m_head->getNext();
		delete temp;
		temp = m_head;
	}
}

// Size indicator functions
bool MemberQueue::empty() { return (m_size == 0) ? true : false; }
bool MemberQueue::full() { return (m_size >= 100) ? true : false; }

// Insert new node to MemberQueue's tail and increase size by 1.
void MemberQueue::push(string& name, int age, string& date, Type type)
{
	if (full())
		throw "MemberQueue::push(string& name, int age, string& date, Type type";

	// case 1: Queue is empty.
	// create a new node and set to head and tail.
	if (empty())
	{
		m_head = new MemberQueueNode(name, age, date, type);
		m_tail = m_head;
		m_size++;
		return;
	}

	// case 2: Queue is not empty.
	// create a new node and set to tail.
	m_tail->setNext(new MemberQueueNode(name, age, date, type));
	m_tail = m_tail->getNext();
	m_size++;
}

// Remove a node from MemberQueue's head.
MemberQueueNode MemberQueue::pop()
{
	if (empty())
		throw "MemberQueue::pop()";
	
	// decrease m_size by 1.
	m_size--;

	// copy the node for return
	MemberQueueNode node = *m_head;

	// deletion
	MemberQueueNode* temp = m_head;
	m_head = m_head->getNext();
	delete temp;

	return node;
}

// Return head node (Call by value)
MemberQueueNode MemberQueue::front()
{
	if (full())
		throw "MemberQueueNode::front()";
	return *m_head;
}

// Print every node of MemberQueue.
// using stringstream to deliver node's information to manager.
stringstream& MemberQueue::printqueue()
{
	static stringstream ss;
	ss.clear();
	
	for (MemberQueueNode* temp = m_head;
		temp; 
		temp = temp->getNext()) 
		ss << *temp;
	return ss;
}