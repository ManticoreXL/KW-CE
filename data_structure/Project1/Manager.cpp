#include "Manager.h"

// Constructor
Manager::Manager() {}

// Destructor
Manager::~Manager() {}

// Initializer
void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    
    string input;
    while (getline(fcmd, input))
    {
        stringstream ss(input);
        string cmd;
        getline(ss, cmd, ' ');

        if (cmd == "LOAD")
        {
            LOAD();
        }
        else if (cmd == "ADD")
        {
            string data;
            getline(ss, data);
            ADD(data);
        }
        else if (cmd == "QPOP")
        {
            QPOP();
        }
        else if (cmd == "SEARCH")
        {
            string name;
            getline(ss, name, ' ');
            SEARCH(name);
        }
        else if (cmd == "PRINT")
        {
            string object;
            getline(ss, object);
            if (object == "NAME")
            {
                PRINT();
            }
            else
            {
                Type type;
                switch (*object.c_str())
                {
                case 'A':
                    type = A;
                    break;
                case 'B':
                    type = B;
                    break;
                case 'C':
                    type = C;
                    break;
                case 'D':
                    type = D;
                    break;
                default:
                    type = null;
                    break;
                }
                PRINT(type);
            }
        }
        else if (cmd == "DELETE")
        {
            string object;
            getline(ss, object, ' ');
            if (object == "NAME")
            {
                string name;
                getline(ss, name, ' ');
                DELETE(name);
            }
            else if (object == "DATE")
            {
                // Not implemented yet..
                PrintSuccess("DELETE");
            }
            else // !NAME && !DATE
            {
                PrintErrorCode(600);
            }
        }
        else if (cmd == "EXIT")
        {
            PrintSuccess("EXIT");
            exit(0);
        }
        else
        {
            PrintErrorCode(1000);
        }
    }

    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

// LOAD, read "data.txt" and push into MemberQueue.
void Manager::LOAD()
{
   try
   {
        ifstream fdata("data.txt");

        // Cannot read "data.txt"
        if (fdata.fail())
            throw "Manager::LOAD()";

        string line;

        // Read "data.txt"
        // and call Parser to parse data and push into MemberQueue.
        while (getline(fdata, line))
        {
            Parser(line);
        }

        // Stringstream for print the result of LOAD.
        stringstream& ss = m_mq.printqueue();

        flog << "===== LOAD =====" << endl;
        while (getline(ss, line))
        {
            flog << line << endl;
        }
        flog << "===============" << endl << endl;
   }
   // If exception occurs, print error code 100 (LOAD)
   catch (const char* err)
   {
       cout << err << endl;
       PrintErrorCode(100);
   }
}

// Parser function for LOAD command.
void Manager::Parser(string& data)
{
    string tname, tage, tdate, ttype;
    Type type = null;

    stringstream ss(data);

    if (getline(ss, tname, ' '));
    else
        throw "Manager::parser(string& data)";

    if (getline(ss, tage, ' '));
    else
        throw "Manager::parser(string& data)";

    if (getline(ss, tdate, ' '));
    else
        throw "Manager::parser(string& data)";

    if (getline(ss, ttype, ' '));
    else
        throw "Manager::parser(string& data)";
    
    // Parse type and assign.
    // Incorrect type input occurs, throw error.
    switch (*(ttype.c_str()))
    {
    case'A':
        type = A;
        break;
    case'B':
        type = B;
        break;
    case'C':
        type = C;
        break;
    case'D':
        type = D;
        break;
    default:
        throw "Manager::parser(string& data)";
    }
    
    // Push data into MemberQueue.
    PUSH(tname, stoi(tage), tdate, type);
}

// PUSH, insert data to MemberQueue (no log)
void Manager::PUSH(string& name, int age, string& date, Type type)
{
    if (m_mq.full())
    {
        // If MemberQueue is full, throw error
        throw "Manager::PUSH(string& name, int age, string& date, Type type)";
        exit(-1);
    }
    m_mq.push(name, age, date, type);
}

// ADD instruction.
void Manager::ADD(string& data)
{
    try
    {
        string tname, tage, tdate, ttype;
        Type type = null;

        stringstream ss(data);

        if (getline(ss, tname, ' '));
        else
            throw "Manager::ADD(string& data)";

        if (getline(ss, tage, ' '));
        else
            throw "Manager::ADD(string& data)";

        if (getline(ss, tdate, ' '));
        else
            throw "Manager::ADD(string& data)";

        if (getline(ss, ttype, ' '));
        else
            throw "Manager::ADD(string& data)";

        // Parse type and assign.
        // Incorrect type input occurs, throw error.
        switch (*(ttype.c_str()))
        {
        case'A':
            type = A;
            break;
        case'B':
            type = B;
            break;
        case'C':
            type = C;
            break;
        case'D':
            type = D;
            break;
        default:
            throw "Manager::ADD(string& data)";
        }

        // Push data into MemberQueue.
        PUSH(tname, stoi(tage), tdate, type);

        flog << "===== ADD =====" << endl;
        flog << tname << "/";
        flog << stoi(tage) << "/";
        flog << tdate << "/";
        flog << ttype << endl;
        flog << "===============" << endl << endl;
    }
    catch (const char* err) // If exception occurs, print error code 200 (ADD)
    {
        cout << err << endl;
        PrintErrorCode(200);
    }
}

// QPOP, pop MemberQueue and create TermsBST and NameBST
// If input type does not exists, create new TermsListNode.
void Manager::QPOP()
{
    if (m_mq.empty())
    {
        // If MemberQueue is empty, print error code 300 (QPOP)
        PrintErrorCode(300);
        exit(-1);
    }

    try
    {
        // Throw when MemberQueue is Empty.
        if (m_mq.empty())
            throw "Manager::QPOP()";
        do
        {
            MemberQueueNode temp = m_mq.pop();

            // Parse data to deliver to BSTs.
            string name = temp.getName();
            int age = temp.getAge();
            Date date = temp.getDate();
            Type type = temp.getType();

            // Insert data into TermsList and TermsBST.
            m_tlist.insert(name, age, date, type);

            // Insert data into NameBST.
            Date exdate = date;
            exdate.addmonth(type);
            m_nbst.insert(name, age, date, exdate);

        }while (!m_mq.empty());

        PrintSuccess("QPOP");
    }
    catch (const char* err) // If exception occurs, print error code 300 (LOAD)
    {
        cout << err << endl;
        PrintErrorCode(300);
    }
}

// SEARCH. find the correct node in NameBST.
// if there is no correct node in NameBST, throw error.
void Manager::SEARCH(string& name)
{
    try
    {
        stringstream& temp = m_nbst.print(name);
        string buffer;

        getline(temp, buffer);
        flog << "===== SEARCH =====" << endl;
        flog << buffer << endl;
        flog << "===============" << endl << endl;
    }
    catch (const char* err) // If exception occurs, print error code 400 (SEARCH)
    {
        cout << err << endl;
        PrintErrorCode(500);
    }
}

// PRINT NameBST.
void Manager::PRINT()
{
    try
    {
        stringstream& temp = m_nbst.print();
        string buffer;

        flog << "===== PRINT =====" << endl;
        flog << "NameBST" << endl;
        while (getline(temp, buffer))
            flog << buffer << endl;
        flog << "===============" << endl << endl;
    }
    catch (const char* err) // If exception occurs, print error code 500 (PRINT)
    {
        cout << err << endl;
        PrintErrorCode(500);
    }
}

// PRINT TermsBST.
void Manager::PRINT(Type type)
{
    try
    {
        stringstream& temp = m_tlist.print(type);
        string buffer;

        char ctype;

        switch (type)
        {
        case A:
            ctype = 'A';
            break;
        case B:
            ctype = 'B';
            break;
        case C:
            ctype = 'C';
            break;
        case D:
            ctype = 'D';
            break;
        default:
            throw "Manager::PRINT(Type type)";
            break;
        }

        flog << "===== PRINT =====" << endl;
        flog << "TermsBST" << " " << ctype << endl;
        while (getline(temp, buffer))
            flog << buffer << endl;
        flog << "===============" << endl << endl;

    }
    catch (const char* err) // If exception occurs, print error code 500 (PRINT)
    {
        cout << err << endl;
        PrintErrorCode(500);
    }
}

void Manager::DELETE(string& name)
{
    try
    {
        m_tlist.remove(name);
        m_nbst.remove(name);
        PrintSuccess("DELETE");
    }
    catch (const char* err)
    {
        cout << err << endl;
        PrintErrorCode(600);
    }
}