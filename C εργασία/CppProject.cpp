#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Δημιουργούμε την κλάση Student
class Student {
private:
    int id;
    string name;
    int age;
    float gpa;

public:
    // Συναρτήσεις για εισαγωγή δεδομένων
    void input() {
        cout << "Δώσε ID φοιτητή: ";
        cin >> id;
        cin.ignore();
        cout << "Δώσε όνομα φοιτητή: ";
        getline(cin, name);
        cout << "Δώσε ηλικία φοιτητή: ";
        cin >> age;
        cout << "Δώσε GPA φοιτητή: ";
        cin >> gpa;
    }

    // Συναρτήσεις για εμφάνιση δεδομένων
    void display() const {
        cout << "ID: " << id << "\nΌνομα: " << name
             << "\nΗλικία: " << age << "\nGPA: " << gpa << endl;
    }

    // Βοηθητική συνάρτηση για επιστροφή ID (χρήσιμη για αναζήτηση)
    int getID() const {
        return id;
    }

    // Συνάρτηση για ενημέρωση στοιχείων
    void update() {
        cout << "Ενημέρωση στοιχείων φοιτητή:\n";
        input();
    }
};

// Δηλώνουμε ένα vector για να αποθηκεύουμε τους φοιτητές
vector<Student> students;

// Συνάρτηση για αποθήκευση σε αρχείο
void saveToFile() {
    ofstream outFile("students.dat", ios::binary);
    for (const auto& s : students) {
        outFile.write((char*)&s, sizeof(Student));
    }
    outFile.close();
}

// Συνάρτηση για ανάγνωση από αρχείο
void loadFromFile() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        // Αν το αρχείο δεν υπάρχει απλά επιστρέφουμε
        return;
    }
    Student s;
    while (inFile.read((char*)&s, sizeof(Student))) {
        students.push_back(s);
    }
    inFile.close();
}

// Συνάρτηση για προσθήκη νέου φοιτητή
void addStudent() {
    Student s;
    s.input();
    students.push_back(s);
    saveToFile();
    cout << "Ο φοιτητής προστέθηκε επιτυχώς!\n";
}

// Συνάρτηση για εμφάνιση όλων των φοιτητών
void displayAll() {
    if (students.empty()) {
        cout << "Δεν υπάρχουν εγγραφές.\n";
        return;
    }
    for (const auto& s : students) {
        s.display();
        cout << "----------------------\n";
    }
}

// Συνάρτηση για αναζήτηση φοιτητή με βάση το ID
void searchStudent() {
    int searchID;
    cout << "Δώσε ID φοιτητή για αναζήτηση: ";
    cin >> searchID;

    for (const auto& s : students) {
        if (s.getID() == searchID) {
            cout << "Βρέθηκε φοιτητής:\n";
            s.display();
            return;
        }
    }
    cout << "Ο φοιτητής δεν βρέθηκε.\n";
}

// Συνάρτηση για ενημέρωση φοιτητή
void updateStudent() {
    int updateID;
    cout << "Δώσε ID φοιτητή για ενημέρωση: ";
    cin >> updateID;

    for (auto& s : students) {
        if (s.getID() == updateID) {
            s.update();
            saveToFile();
            cout << "Τα στοιχεία ενημερώθηκαν επιτυχώς!\n";
            return;
        }
    }
    cout << "Ο φοιτητής δεν βρέθηκε.\n";
}

// Συνάρτηση για διαγραφή φοιτητή
void deleteStudent() {
    int deleteID;
    cout << "Δώσε ID φοιτητή για διαγραφή: ";
    cin >> deleteID;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getID() == deleteID) {
            students.erase(it);
            saveToFile();
            cout << "Ο φοιτητής διαγράφηκε επιτυχώς!\n";
            return;
        }
    }
    cout << "Ο φοιτητής δεν βρέθηκε.\n";
}

// Κύριο μενού επιλογών
void menu() {
    int choice;
    do {
        cout << "\n====== Διαχείριση Φοιτητών ======\n";
        cout << "1. Προσθήκη Φοιτητή\n";
        cout << "2. Εμφάνιση Όλων\n";
        cout << "3. Αναζήτηση Φοιτητή\n";
        cout << "4. Ενημέρωση Φοιτητή\n";
        cout << "5. Διαγραφή Φοιτητή\n";
        cout << "6. Έξοδος\n";
        cout << "Επιλογή: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Έξοδος από το πρόγραμμα.\n"; break;
            default: cout << "Μη έγκυρη επιλογή.\n";
        }
    } while (choice != 6);
}

// Κύρια συνάρτηση main
int main() {
    loadFromFile(); // Φορτώνουμε όσα δεδομένα υπήρχαν
    menu();         // Εκτελούμε το μενού
    return 0;
}
