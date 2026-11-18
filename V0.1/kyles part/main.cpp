#include <iostream>
#include <string>
#include "BST.h"
#include "SLList.h"

enum Status {posted, matched, completed};

class Tutor //dummy Tutor class NOT ACTUAL IMPLEMENTATION
{ 
    private:

    BST<string> subjects; //qualified subjects

    public:

    string name;            //Tutor's name
    int activeMatchCnt = 0; //number of matches that are currently active
    int openedMatchCnt = 0; //number of opened matches: complete and uncomplete
    int ratingSum = 0;      //gross sum of all ratings

    Tutor()
    {
        name = "DEFAULT_NAME";
    }
    Tutor(string name, string* subjects, int count)
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

    float completionRate()
    {
        return (openedMatchCnt - activeMatchCnt + 0.0)/(openedMatchCnt + 0.0);
    }

    float aveRating()
    {
        return (ratingSum + 0.0)/(openedMatchCnt - activeMatchCnt + 0.0);
    }

};

SLList<Tutor*> TutorPool;

class Student //dummy Student class NOT ACTUAL IMPLEMENTATION
{ 
    public:

    string name; //Student's name

    Student()
    {
        name = "DEFAULT_NAME";
    }
    Student(string name)
    {
        this->name = name;
    }

};

class Request //mostly a dummy Request class with real matching algorithm initial prototype
{
    public:
    
    Student quester; //the Requesting Student
    string subject;  //the subject pertaining to the Request
    Status currStatus = posted;
    Tutor* match; //the matched tutor assumed to be an individual value, could easily be adapted into an array or linked list

    Request(Student quester, string subject)
    {
        this->quester = quester;
        this->subject = subject;        

        //the following is just a simple traversal of the Tutor pool
        //in following iterations, the Tutor pool may be stored as a priority queue or under another structure, this may affect traversal
        SLLNode<Tutor*>* index = TutorPool.getHead();
        while (index != nullptr && match == nullptr)
        {
            //DEBUGcout << index->getInfo()->name << " " << ((match == nullptr)? "..." : " ");
            if (index->getInfo()->hasSubject(subject))
            {
                //DEBUGcout << "match" << endl;
                currStatus = matched;

                match = index->getInfo();

                match->openedMatchCnt += 1;
                match->activeMatchCnt += 1;
            }
            else
            {
                //DEBUGcout << "failed" << endl;
                index = index->getNext();
            }
        }
        
    }

    void complete(int rating)
    {
        if (currStatus = matched)
        {
            currStatus = completed;
            
            match->activeMatchCnt -= 1;
            match->ratingSum += rating;
        }
    }


};

int main()
{

    string KylesSubjects[3] = {"Math", "English", "Programming"};
    string MarysSubjects[2] = {"Biology", "Chemistry"};

    TutorPool.addToTail(new Tutor("Kyle", KylesSubjects, 3));
    TutorPool.addToTail(new Tutor("Mary", MarysSubjects, 2));

    Student john("John");
    Student max("Max");

    Request* reqs[5] = {new Request(john, "History"), new Request(max, "Math"), new Request(john, "Biology"), new Request(max, "Programming"), new Request(john, "English")};

    cout << endl <<  "-- Initial requests --" << endl << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << " student : " << reqs[i]->quester.name << endl;
        cout << " subject : " << reqs[i]->subject << endl;
        cout << " status  : " << reqs[i]->currStatus << endl;
        cout << " tutor   : " << ((reqs[i]->currStatus > posted)? reqs[i]->match->name : "none") << endl << endl;
    }

    cout << endl << "-- Close English and Programming requests --" << endl << endl;

    reqs[3]->complete(5);
    reqs[4]->complete(4);

    for (int i = 0; i < 5; i++)
    {
        cout << " student : " << reqs[i]->quester.name << endl;
        cout << " subject : " << reqs[i]->subject << endl;
        cout << " status  : " << reqs[i]->currStatus << endl;
        cout << " tutor   : " << ((reqs[i]->currStatus > posted)? reqs[i]->match->name : "none") << endl << endl;
    }
    
    cout << endl <<  "-- Tutor statistics --" << endl << endl;

    cout << " Kyle's average rating  : " << TutorPool.getHead()->getInfo()->aveRating() << endl;
    cout << " Kyle's completion rate : %" << TutorPool.getHead()->getInfo()->completionRate()*100.0 << endl << endl;

    return 0;
}
