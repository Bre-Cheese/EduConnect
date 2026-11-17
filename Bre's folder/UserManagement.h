#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H
#endif

#include <algorithm>
#include <cctype>
#include <list>
#include <string>
#include <vector>
using namespace std;

enum class Role { Student, Tutor };

struct User {
    Role role;
    string name;
    string email;              // always lowercase so lookups are case-insensitive
    vector<string> subjects;   // tutors only

    bool isTutor() const { return role == Role::Tutor; }

    // Compares lowercase copies so "calculus" matches "Calculus"
    bool teaches(const string& subject) const {
        string s = lower(subject);
        for (const string& x : subjects)
            if (lower(x) == s) return true;
        return false;
    }

    // Skips subjects the tutor already has instead of adding duplicates
    bool addSubject(const string& subject) {
        if (!isTutor() || subject.empty()) return false;
        if (!teaches(subject)) subjects.push_back(subject);
        return true;
    }

    // TODO: removeSubject (keep at least one subject)

    static string lower(string s) {
        // cast to unsigned char because tolower is undefined for negative values
        for (char& c : s) c = tolower((unsigned char)c);
        return s;
    }
};

class UserManager {
public:
    bool registerStudent(const string& name, const string& email) {
        return add(Role::Student, name, email, {});
    }
    bool registerTutor(const string& name, const string& email, const vector<string>& subjects) {
        return add(Role::Tutor, name, email, subjects);
    }

    // Returns a pointer to the stored user, or nullptr if not found.
    User* find(const string& email) {
        string key = User::lower(email);
        for (User& u : bucket(key))   // only this one bucket is searched
            if (u.email == key) return &u;
        return nullptr;
    }

    // TODO: updateEmail (user has to move to a new bucket)

private:
    vector<list<User>> table = vector<list<User>>(16);   // fixed size for now
    size_t count = 0;

    // Hash the email, then % table size to pick a bucket index
    list<User>& bucket(const string& email) {
        return table[hash<string>{}(email) % table.size()];
    }

    // Simple format check only: something before '@', a '.' after it, no spaces
    static bool validEmail(const string& e) {
        size_t at = e.find('@');
        return at != string::npos && at > 0 && e.find('.', at) != string::npos &&
               e.find(' ') == string::npos;
    }

    // TODO: grow() - table never resizes yet, so find() slows down with many users

    bool add(Role role, const string& name, const string& rawEmail, const vector<string>& subjects) {
        string email = User::lower(rawEmail);
        if (name.empty() || !validEmail(email) || find(email)) return false;
        if (role == Role::Tutor && subjects.empty()) return false;

        User u{role, name, email, {}};
        for (const string& s : subjects)
            if (!u.addSubject(s)) return false;

        bucket(email).push_back(u);
        count++;
        return true;
    }
};
