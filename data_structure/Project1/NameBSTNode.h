#pragma once
#include"Date.h"

class NameBSTNode
{
private:
	string m_name;
	int m_age;
	Date m_date;
	Date m_exdate;
	NameBSTNode* m_left;
	NameBSTNode* m_right;

public:
	// Constructor
	NameBSTNode(string& name, int age, Date& date, Date& exdate)
	{
		m_name = name;
		m_age = age;
		m_date = date;
		m_exdate = exdate;
		m_left = nullptr;
		m_right = nullptr;
	}

	// Destructor
	~NameBSTNode() {}

	// Get functions
	string& getName() { return m_name; }
	int getAge() { return m_age; }
	Date getDate() { return m_date; }
	Date getExdate() { return m_exdate; }
	NameBSTNode* getLeft() { return m_left; }
	NameBSTNode* getRight() { return m_right; }

	// Set functions
	void setName(string& name) { m_name = name; }
	void setAge(int age) { m_age = age; }
	void setDate(Date date) { m_date = date; }
	void setExdate(Date exdate) { m_exdate = exdate; }
	void setLeft(NameBSTNode* left) { m_left = left; }
	void setRight(NameBSTNode* right) { m_right = right; }

	// using stringstream to deliver node's information to manager.
	friend ostream& operator<<(ostream& out, const NameBSTNode& obj)
	{
		out << obj.m_name << '/' << obj.m_age << '/' << obj.m_date << '/' << obj.m_exdate << endl;
		return out;
	}
};