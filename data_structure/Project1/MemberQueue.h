#pragma once
#include "MemberQueueNode.h"

class MemberQueue
{
private:
	MemberQueueNode* m_head;
	MemberQueueNode* m_tail;
	int m_size;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(string& name, int age, string& date, Type type);
	MemberQueueNode pop();
	MemberQueueNode front();
	stringstream& printqueue();
};

