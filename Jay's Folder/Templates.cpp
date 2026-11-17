#include <iostream>
#include "Templates.h"

//Request Template
//Constructor / Destructor Functions
template<class T>
Request<T>::Request()
{
 next = nullptr;
 prev = nullptr;
}
template<class T>
Request<T>::Request(int RequestNum, T Subject, T Description, T Urgency) : RequestNum(RequestNum), Subject(Subject),  Description(Description), Urgency(Urgency)
{
 next = nullptr;
 prev = nullptr;
}
template<class T>
Request<T>::~Request()
{
}
//Get Functions
template<class T>
int Request<T>::getRequestNum()
{
  return RequestNum;
}
template<class T>
T& Request<T>::getSubject()
{
  return Subject;
}
template<class T>
T& Request<T>::getDescription()
{
  return Description;
}
template<class T>
T& Request<T>::getUrgency()
{
  return Urgency;
}
template<class T>
T& Request<T>::getStatus()
{
  return Status;
}
//Set Functions
template<class T>
void Request<T>::setRequestNum(int r)
{
  RequestNum = r;
}
template<class T>
void Request<T>::setSubject(T s)
{
  Subject = s;
}
template<class T>
void Request<T>::setDescription(T d)
{
  Description = d;
}
template<class T>
void Request<T>::setUrgency(T u)
{
  Urgency = u;
}
template<class T>
void Request<T>::setStatus(T s)
{
  Status = s;
}
//Pointer Functions
template<class T>
Request<T>* Request<T>::getNextRequest()
{
  return next;
}
template<class T>
Request<T>* Request<T>::getPrevRequest()
{
  return prev;
}
template<class T>
Student<T>* Request<T>::getBackToStudent()
{
  return back;
}
template<class T>
void Request<T>::setNextRequest(Request *n)
{
  next = n;
}
template<class T>
void Request<T>::setPrevRequest(Request *p)
{
  prev = p;
}




//Student Template
//Constructor / Destructor Functions
template<class T>
Student<T>::Student()
{
 request = nullptr;
 NumRequests = 0;
}
template<class T>
Student<T>::Student(T Email, T Name) : Email(Email), Name(Name)
{
 request = nullptr;
 NumRequests = 0;
}
template<class T>
Student<T>::~Student()
{
}
//Get Functions
template<class T>
T& Student<T>::getContact()
{
  return Email;
}
template<class T>
T& Student<T>::getName()
{
  return Name;
}
//Set Functions
template<class T>
void Student<T>::setContact(T e)
{
  Email = e;
}
template<class T>
void Student<T>::setName(T n)
{
  Name = n;
}
//Pointer Functions
template<class T>
Request<T>* Student<T>::getRequests()
{
  return request;
}
template<class T>
void Student<T>::setRequest(Request<string> *r)
{
  request = r;
}