#include <iostream>
#include <string>
#include "SLList.h"
#include "BST.h"

using namespace std;

class tutor //dummy tutor class NOT ACTUAL IMPLEMENTATION
{ 
    private:

    BST<string> subjects; //qualified subjects
    //int subCnt; //the amount of qualified subjects

    public:

    string name; //tutor's name

    tutor()
    {
        name = "DEFAULT_NAME";
    }
    tutor(const string name, const string* subjects, const int count)
    {
        this->name = name;
        for (int i = 0; i < count; i++)
        {
            this->subjects.add(*(subjects + i));
        }
    }

    bool hasSubject(string param)
    {
        return (subjects.search(param) != nullptr);
    }

};

class student //dummy student class NOT ACTUAL IMPLEMENTATION
{ 
    public:

    string name; //student's name

    student()
    {
        name = "DEFAULT_NAME";
    }
    student(string name)
    {
        this->name = name;
    }

};

class request
{
    public:
    
    student quester; //the requesting student
    string subject; //the subject pertaining to the request

    request()
    {
    }
    request(student quester, string subject)
    {
        this->quester = quester;
        this->subject = subject;
    }
};

class match {
public:

    public:
    
    tutor prospect; //the proposed tutor for this request
    request* reqToMatch; //the request to be matched

    match (request* toMatch, SLList<tutor>* tutorPool)
    {
        SLLNode<tutor>* index = tutorPool->getHead();
        reqToMatch = toMatch;
        while (index != nullptr && prospect.name == "DEFAULT_NAME")
        {
            if (index->getInfo().hasSubject(reqToMatch->subject))
            {
                prospect = index->getInfo();
            }
            else
            {
                index = index->getNext();
            }
        }
    }

};

int main()
{

    string KylesSubjects[2] = {"Math", "English"};
    string MarysSubjects[2] = {"Biology", "Chemistry"};

    tutor kyle("Kyle", KylesSubjects, 2);
    tutor mary("Mary", MarysSubjects, 2);

    SLList<tutor> tutorPool;
    tutorPool.addToTail(kyle);
    tutorPool.addToHead(mary);

    student john("John");

    request req0(john, "History");
    request req1(john, "Math");
    request req2(john, "Biology");

    match match0(&req0, &tutorPool);
    match match1(&req1, &tutorPool);
    match match2(&req2, &tutorPool);

    cout << match0.reqToMatch->subject << " " << match0.prospect.name << endl;
    cout << match1.reqToMatch->subject << " " << match1.prospect.name << endl;
    cout << match2.reqToMatch->subject << " " << match2.prospect.name << endl;

    return 0;
}
