#include <iostream>
#include "Templates.h"

//User Template
//Constructor / Destructor Functions
template<class T>
User<T>::User()
{
}
template<class T>
User<T>::User(T Email, T Name) : Email(Email), Name(Name)
{
}
template<class T>
User<T>::~User()
{
}
//Get Functions
template<class T>
T& User<T>::getContact()
{
  return Email;
}
template<class T>
T& User<T>::getName()
{
  return Name;
}
//Set Functions
template<class T>
void User<T>::setContact(T e)
{
  Email = e;
}
template<class T>
void User<T>::setName(T n)
{
  Name = n;
}



//Student Template
//Constructor / Destructor Functions
template<class T>
Student<T>::Student()
{
}
template<class T>
Student<T>::Student(T Email, T Name) : Email(Email), Name(Name)
{
}
template<class T>
Student<T>::~Student()
{
}
// template<class T>
// void Student<T>::setToRequest(Request<T> *n)
// {
//   next = n;
// }
// template<class T>
// Request<T>* Student<T>::getToRequest()
// {
//   return request;
// }



//Tutor Template
//Constructor / Destructor Functions
template<class T>
Tutor<T>::Tutor()
{
  Subject = "N/A";
}
template<class T>
Tutor<T>::Tutor(T Email, T Name) : Email(Email), Name(Name)
{
  Subject = "N/A";
}
template<class T>
Tutor<T>::~Tutor()
{
}
template<class T>
string Tutor<T>::getSubject()
{
  return Subject;
}
template<class T>
void Tutor<T>::setSubject(string s)
{
  Subject = s;
}



//Request Template
//Constructor / Destructor Functions
template<class T>
Request<T>::Request()
{
 next = nullptr;
 prev = nullptr;
 student = nullptr;
 tutor = nullptr;
}
template<class T>
Request<T>::Request(T Subject, T Description, T Urgency) : Subject(Subject),  Description(Description), Urgency(Urgency)
{
 next = nullptr;
 prev = nullptr;
 student = nullptr;
 tutor = nullptr;
}
template<class T>
Request<T>::~Request()
{
}
//Get Functions
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
Student<T>* Request<T>::getToStudent()
{
  return student;
}
template<class T>
Tutor<T>* Request<T>::getToTutor()
{
  return tutor;
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
template<class T>
void Request<T>::setToStudent(Student<T> *s)
{
  student = s;
}
template<class T>
void Request<T>::setToTutor(Tutor<T> *t)
{
  tutor = t;
}
