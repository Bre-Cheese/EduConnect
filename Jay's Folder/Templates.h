// #pragma once
#include <iostream>
using namespace std;

template<class T>
class User
{
 public:
  User();
  User(T email, T name);
  ~User();
  T& getContact();
  T& getName();
  T Email;
  T Name;
  int NumRequests;
 private:
  void setContact(T e);
  void setName(T n);
};

template<class T>
class Student : public User<T>
{
 public:
  Student();
  Student(T email, T name);
  ~Student();
  T Email;
  T Name;
//   Request<T>* getToRequest();
//   void setToRequest(Request<T> *next);
//   Request<T>* next;
//  private:
};

template<class T>
class Tutor : public User<T>
{
 public:
  Tutor();
  Tutor(T email, T name);
  ~Tutor();
  T Email;
  T Name;
  string getSubject();
  void setSubject(string s);
  string Subject;
//  private:
};

template<class T>
class Request
{
 public:
  Request();
  Request(T Subject, T Description, T Urgency);
  ~Request();
  T& getSubject();
  T& getDescription();
  T& getUrgency();
  T& getStatus();
  void setSubject(T Subject);
  void setDescription(T Description);
  void setUrgency(T Urgency);
  void setStatus(T Status);
  Request<T>* getNextRequest();
  Request<T>* getPrevRequest();
  Student<T>* getToStudent();
  Tutor<T>* getToTutor();
  void setNextRequest(Request *next);
  void setPrevRequest(Request *prev);
  void setToStudent(Student<T> *student);
  void setToTutor(Tutor<T> *tutor);
  T Subject;
  T Description;
  T Urgency;
  T Status;
  Request<T>* next;
  Request<T>* prev;
  Student<T>* student;
  Tutor<T>* tutor;
  private:
};
