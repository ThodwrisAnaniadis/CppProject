
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

class Student {
private:
    int id;
    string name;
    int age;
    float gpa;

public:
    void input();
    void display() const;
    int getId() const;
    string toCSV() const;
    bool fromCSV(const string &line);
    void update();
};

void Student::input() {
    cout << "\nΕισάγετε ID φοιτητή: ";
    cin >> id;
    cin.ignore(); // καθαρισμός του buffer
    cout << "Ονοματεπώνυμο: ";
    getline(cin, name);
    cout << "Ηλικία: ";
    cin >> age;
    cout << "GPA: ";
    cin >> gpa;
}

void Student::display() const {
    cout << left << setw(10) << id
         << setw(25) << name
         << setw(10) << age
         << fixed << setprecision(2)
         << setw(10) << gpa << endl;
}

int Student::getId() const {
    return id;
}

string Student::toCSV() const {
    return to_string(id) + "," + name + "," + to_string(age) + "," + to_string(gpa);
}

bool Student::fromCSV(const string &line) {
    stringstream ss(line);
    string temp;
    getline(ss, temp, ',');
    if (temp.empty()) return false;
    id = stoi(temp);
    getline(ss, name, ',');
    getline(ss, temp, ',');
    age = stoi(temp);
    getline(ss, temp, ',');
    gpa = stof(temp);
    return true;
}

void Student::update() {
    cout << "\n-- Ενημέρωση στοιχείων --\n";
    cout << "Νέο ονοματεπώνυμο: ";
    cin.ignore();
    getline(cin, name);
    cout << "Νέα ηλικία: ";
    cin >> age;
    cout << "Νέο GPA: ";
    cin >> gpa;
}

// Βοηθητικές συναρτήσεις
void addStudent(const string &filename);
void displayAll(const string &filename);
void searchStudent(const string &filename);
void updateStudent(const string &filename);
void deleteStudent(const string &filename);

int main() {
    string filename = "students.txt";
    int choice;

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Προσθήκη φοιτητή\n";
        cout << "2. Προβολή όλων\n";
        cout << "3. Αναζήτηση φοιτητή\n";
        cout << "4. Ενημέρωση φοιτητή\n";
        cout << "5. Διαγραφή φοιτητή\n";
        cout << "6. Έξοδος\n";
        cout << "Επιλογή: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(filename); break;
            case 2: displayAll(filename); break;
            case 3: searchStudent(filename); break;
            case 4: updateStudent(filename); break;
            case 5: deleteStudent(filename); break;
            case 6: cout << "Έξοδος...\n"; break;
            default: cout << "Μη έγκυρη επιλογή!\n";
        }
    } while (choice != 6);

    return 0;
}

void addStudent(const string &filename) {
    Student s;
    s.input();
    ofstream out(filename, ios::app);
    out << s.toCSV() << endl;
    out.close();
    cout << "Ο φοιτητής προστέθηκε με επιτυχία.\n";
}

void displayAll(const string &filename) {
    ifstream in(filename);
    if (!in) {
        cout << "Δεν υπάρχουν δεδομένα.\n";
        return;
    }

    Student s;
    string line;

    cout << "\n-- Λίστα Φοιτητών --\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Ονοματεπώνυμο"
         << setw(10) << "Ηλικία"
         << setw(10) << "GPA" << endl;

    while (getline(in, line)) {
        if (s.fromCSV(line)) {
            s.display();
        }
    }

    in.close();
}

void searchStudent(const string &filename) {
    int targetId;
    bool found = false;
    cout << "Εισάγετε το ID του φοιτητή για αναζήτηση: ";
    cin >> targetId;

    ifstream in(filename);
    string line;
    Student s;

    while (getline(in, line)) {
        if (s.fromCSV(line) && s.getId() == targetId) {
            cout << "\n-- Φοιτητής βρέθηκε --\n";
            s.display();
            found = true;
            break;
        }
    }

    in.close();

    if (!found)
        cout << "Δεν βρέθηκε φοιτητής με αυτό το ID.\n";
}

void updateStudent(const string &filename) {
    int targetId;
    bool found = false;
    cout << "Εισάγετε το ID για ενημέρωση: ";
    cin >> targetId;

    ifstream in(filename);
    vector<Student> students;
    string line;
    Student s;

    while (getline(in, line)) {
        if (s.fromCSV(line)) {
            if (s.getId() == targetId) {
                s.update();
                found = true;
            }
            students.push_back(s);
        }
    }
    in.close();

    ofstream out(filename);
    for (const auto &student : students) {
        out << student.toCSV() << endl;
    }
    out.close();

    if (found)
        cout << "Τα στοιχεία ενημερώθηκαν.\n";
    else
        cout << "Δεν βρέθηκε φοιτητής με αυτό το ID.\n";
}

void deleteStudent(const string &filename) {
    int targetId;
    bool found = false;
    cout << "Εισάγετε το ID για διαγραφή: ";
    cin >> targetId;

    ifstream in(filename);
    vector<Student> students;
    string line;
    Student s;

    while (getline(in, line)) {
        if (s.fromCSV(line)) {
            if (s.getId() != targetId) {
                students.push_back(s);
            } else {
                found = true;
            }
        }
    }
    in.close();

    ofstream out(filename);
    for (const auto &student : students) {
        out << student.toCSV() << endl;
    }
    out.close();

    if (found)
        cout << "Ο φοιτητής διαγράφηκε.\n";
    else
        cout << "Δεν βρέθηκε φοιτητής με αυτό το ID.\n";
}
