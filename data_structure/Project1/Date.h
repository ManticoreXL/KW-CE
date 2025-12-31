#pragma once
#include<string>
#include<cstring>
#include<exception>
#include<sstream>
#include<vector>
using namespace std;

// Terms types
enum Type
{
	A, B, C, D, null
};

// Date is a class to manage terms subscription date easily.
// Date class has year, month, day member.
// Date class offers compare, copy, ostream operators.
class Date
{
private:
	int m_year;
	int m_month;
	int m_day;

public:
	// Constructor
	Date()
	{
		m_year = 0;
		m_month = 0;
		m_day = 0;
	}

	// Constructor with integer input
	Date(int year, int month, int day)
	{
		m_year = year;
		m_month = month;
		m_day = day;
	}

	// Constructor with string input
	Date(string& date)
	{
		stringstream ss(date);
		string buffer;
		
		// string to integer year
		if (getline(ss, buffer, '-'))
			m_year = stoi(buffer);
		else
			throw "Date::Date(string& date)";

		// string to integer month
		if (getline(ss, buffer, '-'))
			m_month = stoi(buffer);
		else
			throw "Date::Date(string& date)";

		// string to integer day
		if (getline(ss, buffer, '-'))
			m_day = stoi(buffer);
		else
			throw "Date::Date(string& date)";

		// data input over
		if(getline(ss, buffer))
			throw "Date::Date(string& date)";		
	}

	// Get funcionts
	int getYear() { return m_year; }
	int getMonth() { return m_month; }
	int getDay() { return m_day; }

	// Calculator for adding month to date.
	// use for construct exdate date.
	void addmonth(char termstype)
	{
		// add month and update year.
		switch (termstype)
		{
		case A:
			m_month += 6;
			if (m_month > 12)
			{
				int temp = m_month / 12;
				m_year += temp;
				m_month = m_month % 12;
			}
			break;
		case B:
			m_month += 12;
			if (m_month > 12)
			{
				int temp = m_month / 12;
				m_year += temp;
				m_month = m_month % 12;
			}
			break;
		case C:
			m_month += 24;
			if (m_month > 12)
			{
				int temp = m_month / 12;
				m_year += temp;
				m_month = m_month % 12;
			}
			break;
		case D:
			m_month += 36;
			if (m_month > 12)
			{
				int temp = m_month / 12;
				m_year += temp;
				m_month = m_month % 12;
			}
			break;
		default:
			throw "addmonth(char termstype)";
		}
	}

	// Compare operator overloading
	bool operator<(Date& obj)
	{
		if (m_year != obj.m_year)
			return m_year < obj.m_year;
		if (m_year != obj.m_month)
			return m_month < obj.m_month;
		if (m_day != obj.m_day)
			return m_day < obj.m_day;
		return false;
	}

	// Compare operator overloading
	bool operator>(Date& obj)
	{
		if (m_year != obj.m_year)
			return m_year > obj.m_year;
		if (m_year != obj.m_month)
			return m_month > obj.m_month;
		if (m_day != obj.m_day)
			return m_day > obj.m_day;
		return false;
	}

	// Operator for ostream
	friend ostream& operator<<(ostream& out, const Date& obj)
	{
		// consider output format (filling zero)
		out << obj.m_year << '-';
		if (obj.m_month < 10)
			out << '0' << obj.m_month << '-';
		else
			out << obj.m_month << '-';
		if (obj.m_day < 10)
			out << '0' << obj.m_day;
		else
			out << obj.m_day;
		return out;
	}
};