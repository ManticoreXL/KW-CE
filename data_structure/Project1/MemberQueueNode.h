#pragma once
#include"Date.h"

class MemberQueueNode
{
private:
	string m_name;
	int m_age;
	Date m_date;
	Type m_type;

	MemberQueueNode* m_next;

public:
	// Constructor
	MemberQueueNode()
	{
		m_name = "";
		m_age = 0;
		m_date;
		m_type = null;
	}

	// Constructor with input
	MemberQueueNode(string& name, int age, Date& date, Type type)
	{
		m_name = name;
		m_age = age;
		m_date = date;
		m_type = type;
	}

	// Constructor with string date input
	MemberQueueNode(string& name, int age, string& date, Type type)
	{
		m_name = name;
		m_age = age;
		m_date = date;
		m_type = type;
	}

	// Destructor
	~MemberQueueNode() {}

	// get functions
	string getName() { return m_name; }
	int getAge() { return m_age; }
	Date getDate() { return m_date; }
	Type getType() { return m_type; }
	MemberQueueNode* getNext() { return m_next; }

	// set functions
	void setNext(MemberQueueNode* next) { m_next = next; }

	// outstream operator overload.
	friend ostream& operator<<(ostream& out, MemberQueueNode& obj)
	{
		char type;
		switch (obj.m_type)
		{
		case A:
			type = 'A';
			break;
		case B:
			type = 'B';
			break;
		case C:
			type = 'C';
			break;
		case D:
			type = 'D';
			break;
		default:
			throw "ostream& operator<<(ostream& out, MemberQueueNode& queueNode)";
		}

		// return outstream
		out << obj.m_name << '/' << obj.m_age << '/' << obj.m_date << '/' << type << endl;
		return out;
	}
};