#include <iostream>
#include <string>

using namespace std;

class tutor //dummy tutor class NOT ACTUAL IMPLEMENTATION
{ 
    private:

    string subjects[10]; //qualified subjects
    int subCnt; //the amount of qualified subjects

    public:

    string name; //tutor's name

    tutor(string name, string* subjects, int count)
    {
        this->name = name;
        subCnt = count;
        for (int i = 0; i < subCnt; i++)
        {
            this->subjects[i] = *(subjects + i);
        }
    }

    bool hasSubject(string search)
    {
        for (int i = 0; i < subCnt; i++)
        {
            if (subjects[i] == search)
            {
                return true;
            }
        }

        return false;
    }

};

class student //dummy student class NOT ACTUAL IMPLEMENTATION
{ 
    public:

    string name; //student's name

    student(string name)
    {
        this->name = name;
    }

};

class request
{
    public:
    
    student quester;
    string subject;

    request(student quester, string subject)
    {
        this->quester = quester;
        this->subject = subject;
    }
};

class match {
public:



};

int main()
{

    string KylesSubjects[2] = {"Math", "English"};
    tutor kyle = tutor("Kyle", KylesSubjects, 2);
    
    cout << kyle.name << " is" << ( (kyle.hasSubject("Math"))? " " : " not " ) << "qualified to tutor in Math" << endl;
    cout << kyle.name << " is" << ( (kyle.hasSubject("Biology"))? " " : " not " ) << "qualified to tutor in Biology" << endl;

    return 0;
}
