#include <iostream>
#include <string>
#include "Templates.cpp"
using namespace std;

Request<string>* prevConnectPntr = nullptr;         //Pointer for new requests to connect to previous ones

void createRequest(Student<string> student) {       //Function for students to create tutor requests
  string subject, description, urgency;
  subject.resize(20);
  description.resize(100);
  int valid = 0;
  cout<<"Describe why you need help: ";             //Prompts user for information reguarding request
  getline (cin, description);
  cout<<"Choose a Subject: ";
  cin>>subject;
  while (valid==0){
    cout<<"What is the Urgency level? {Low, Medium, or High}: ";
    cin>>urgency;
    if ((urgency == "Low") || (urgency == "Medium") || (urgency == "High")) {
      valid=1;
    }
    else{
      cout<<"Invalid input. ";
    }
  }
  cout<<subject<<endl;
  cout<<description<<endl;
  cout<<urgency<<endl;
  Request<string> NewRequest(subject, description, urgency);        //Create Request with filled in variables
  NewRequest.setToStudent(&student);                //Links request to student
//   if (prevConnectPntr != 0){                     //Links request to other requests from the same student
//     NewRequest.setPrevRequest(prevConnectPntr);
//   }

//   prevConnectPntr=&NewRequest;
  NewRequest.setStatus("Posted");                   //Changes Status to Posted
}

void acceptRequest(Tutor<string> tutor, Request<string> request) {    //Once a tutor accepts the request, links request to tutor and sets status to matched
    request.setToTutor(&tutor);
    request.setStatus("Matched");
}

void completeRequest(Request<string> request) {                       //Once request is complete, sets status to complete [and will remove from current requests]
    request.setStatus("Complete");
}

int main() {

  cout << "Hello World!"<<endl;
  Student<string> student1("atme@me.ca", "Johnathan Joestar");
  createRequest(student1);
  return 0;
}
