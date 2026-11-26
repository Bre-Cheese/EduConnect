/*
 * External functions:
 * Person::registerStudent(name, email)
 * Person::registerTutor(name, email, subjects)
 * Person::find(email)
 * Tutor::addSubject(subject)
 * Tutor::teaches(subject)
 */
#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <cctype> 
#include <cstddef> 
#include <functional> 
#include <list> 
#include <memory> // For unique_ptr
#include <string>
#include <utility> // For move
#include <vector> 

using namespace std;

class Person {
public:
    string name;
    string email;

    Person(const string& name, const string& email) 
        : name(name), email(email) {}
    virtual ~Person() = default;

    static string lower(string value) {
        for (char& c : value)
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        return value;
    }

    static bool registerStudent(const string& name, const string& email);
    static bool registerTutor(const string& name, const string& email,
                              const vector<string>& subjects);
    static Person* find(const string& email); // Returns a pointer to the Person object with the given email, or nullptr if not found.

private:
    static vector<list<unique_ptr<Person>>>& table() {
        static vector<list<unique_ptr<Person>>> buckets(16); // Initialize the hash table with 16 buckets.
        return buckets;
    }

    static list<unique_ptr<Person>>& bucket(const string& email) { // Returns a reference to the list of Person objects in the bucket corresponding to the given email.
        return table()[hash<string>{}(email) % table().size()];
    }

    static bool validEmail(const string& email) {
        const size_t at = email.find('@');
        return at != string::npos && at > 0 &&
               email.find('.', at) != string::npos &&
               email.find(' ') == string::npos;
    }

    static bool add(unique_ptr<Person> person) { // Adds a Person object to the hash table
        if (person->name.empty() || !validEmail(person->email) || find(person->email))
            return false;

        bucket(person->email).push_back(move(person));
        return true;
    }
};

class Student : public Person {
public:
    Student(const string& name, const string& email)
        : Person(name, email) {}
};

class Tutor : public Person {
public:
    vector<string> subjects;

    Tutor(const string& name, const string& email)
        : Person(name, email) {}

    bool teaches(const string& subject) const {
        const string key = lower(subject);
        for (const string& existing : subjects)
            if (lower(existing) == key) return true;
        return false;
    }

    bool addSubject(const string& subject) {
        if (subject.empty()) return false;
        if (!teaches(subject)) subjects.push_back(subject);
        return true;
    }
};

inline bool Person::registerStudent(const string& name, const string& email) {
    return add(unique_ptr<Person>(new Student(name, lower(email)))); // Create a unique_ptr to a new Student object and add it to the hash table
}

inline bool Person::registerTutor(const string& name, const string& email, // 
                                  const vector<string>& subjects) {
    if (subjects.empty()) return false;

    unique_ptr<Tutor> tutor(new Tutor(name, lower(email))); // Create a unique_ptr to a new Tutor object
    for (const string& subject : subjects)
        if (!tutor->addSubject(subject)) return false;
    unique_ptr<Person> person(move(tutor));// Move the unique_ptr to a Person pointer
    return add(move(person));
}

inline Person* Person::find(const string& email) {
    const string key = lower(email);
    for (const unique_ptr<Person>& person : bucket(key))
        if (person->email == key) return person.get();
    return nullptr;
}

#endif
