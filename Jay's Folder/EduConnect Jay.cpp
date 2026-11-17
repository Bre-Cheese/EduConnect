#include <iostream>
#include <string>
#include "Templates.cpp"
using namespace std;

void createRequest(Student<string> student) {
  string subject, description, urgency;
  subject.resize(20);
  description.resize(100);
  int valid = 0;
  cout<<"Describe why you need help: ";
  getline (cin, description);
  cout<<"Choose a Subject: ";
  cin>>subject;
  while (valid==0){
    cout<<"What is the Urgency level? {Low, Medium, or High}: ";
    cin>>urgency;
    if (urgency == "Low" || urgency == "Medium" || urgency == "High") {
      valid=1;
    }
    else{
      cout<<"Invalid input. ";
    }
  }
  cout<<student.NumRequests<<endl;
  cout<<subject<<endl;
  cout<<description<<endl;
  cout<<urgency<<endl;
  student.NumRequests++;
  Request<string> NewRequest(student.NumRequests, subject, description, urgency);
  student.setRequest(&NewRequest);
  NewRequest.setPrevRequest(&student);
}

int main() {

  cout << "Hello World!"<<endl;
  Student<string> student1("atme@me.ca", "Johnathan Joestar");
  createRequest(student1);
  // Request<string> req1(1, "Math", "HELP ME.", "High");
  // Request<string> req2(1, "Science", "I need help with science.", "Medium");
  // Request<string> req3(1, "Art", "Help me if you are free.", "Low");
  return 0;
}