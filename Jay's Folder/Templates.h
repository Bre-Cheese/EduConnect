#pragma once
#include <iostream>
using namespace std;

template<class T>
class Request
{
 public:
  Request();
  Request(int RequestNum, T Subject, T Description, T Urgency);
  ~Request();
  int getRequestNum();
  T& getSubject();
  T& getDescription();
  T& getUrgency();
  T& getStatus();
  void setRequestNum(int RequestNum);
  void setSubject(T Subject);
  void setDescription(T Description);
  void setUrgency(T Urgency);
  void setStatus(T Status);
  Request<T>* getNextRequest();
  Request<T>* getPrevRequest();
  Student<T>* getBackToStudent();
  void setNextRequest(Request *next);
  void setPrevRequest(Request *prev);
  void setBackToStudent(Student *back);
  T Subject;
  T Description;
  T Urgency;
  T Status;
  int RequestNum;
  Request<T>* next;
  Request<T>* prev;
  Student<T>* back;
//  private:
};

template<class T>
class Student
{
 public:
  Student();
  Student(T email, T name);
  ~Student();
  T& getContact();
  T& getName();
  void setContact(T e);
  void setName(T n);
  Request<T>* getRequests();
  void setRequest(Request *r);
  T Email;
  T Name;
  int NumRequests;
  Request<T>* request;
//  private:
};