#include <iostream>
#include <string>
#include <iomanip>
#include <memory> // For smart pointers if needed, but using raw pointers for simplicity

using namespace std;

// Base class for virtual inheritance demonstration
class Base {
public:
    virtual ~Base() = default;
};

// Base class for persons (used for virtual inheritance)
class Person : virtual public Base {
protected:
    string name;
    string email;
public:
    Person(string n, string e) : name(n), email(e) {}
    virtual string getInfo() const = 0;
};

// Applicant class with virtual inheritance from Person
class Applicant : virtual public Person {
private:
    float cgpa;
    string status; // "Pending", "Selected", "Not Selected"
    string interviewDate;
    string interviewTime;

public:
    Applicant() : Person("", ""), cgpa(0.0), status("Empty") {}
    Applicant(string n, string e, float c) : Person(n, e), cgpa(c), status("Pending"), interviewDate("N/A"), interviewTime("N/A") {}

    float getCGPA() const { return cgpa; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getStatus() const { return status; }
    string getInterviewInfo() const { return interviewDate + " " + interviewTime; }

    void setStatus(string s) { status = s; }
    void setInterview(string d, string t) { interviewDate = d; interviewTime = t; }

    // Polymorphism: Override virtual function
    string getInfo() const override { return name + " (" + email + ") CGPA: " + to_string(cgpa); }
};

// UserRole class with virtual inheritance from Person (for polymorphism and virtual inheritance)
class UserRole : virtual public Person {
private:
    string password;
    string role;
public:
    UserRole(string u, string p, string r) : Person(u, ""), password(p), role(r) {} // name is username/email
    bool authenticate(string u, string p) { return (name == u && password == p); }
    string getRole() const { return role; }
    string getUsername() const { return name; }
    virtual void panel() = 0; // Pure virtual for polymorphism
};

// Admin class inheriting from UserRole (demonstrates polymorphism)
class Admin : public UserRole {
public:
    Admin(string u, string p) : UserRole(u, p, "admin") {}
    void panel() override { adminPanel(); } // Polymorphic call
};

// Student class inheriting from UserRole (demonstrates polymorphism)
class Student : public UserRole {
public:
    Student(string u, string p) : UserRole(u, p, "student") {}
    void panel() override { studentPanel(name); } // name is email, polymorphic call
};

// Example of virtual inheritance: A class inheriting from both Applicant and UserRole
// This resolves the diamond problem since Person and Base are inherited virtually
class FullApplicant : public Applicant, public UserRole {
public:
    FullApplicant(string n, string e, float c, string p) : Person(n, e), Applicant(n, e, c), UserRole(n, p, "full") {}
    // Must implement getInfo (from Person) and panel (from UserRole) due to virtual inheritance
    string getInfo() const override { return Applicant::getInfo(); } // Use Applicant's version
    void panel() override { /* Custom implementation if needed */ cout << "Full applicant panel not implemented.\n"; }
};

class Internship {
private:
    string deptName;
    string title;
    string description;
    Applicant applicants[5]; 
    int applicantCount; 

public:
    Internship() {
        deptName = ""; title = "Not Posted"; applicantCount = 0;
    }

    void setDeptName(string name) { deptName = name; }
    string getDeptName() const { return deptName; }
    string getTitle() const { return title; }

    // Admin Posts Job [cite: 94-99]
    void postInternship(string t, string d) {
        title = t;
        description = d;
        applicantCount = 0; 
        cout << " -> Success: Internship Posted for " << deptName << ".\n";
    }

    // Student Applies [cite: 106-117]
    string apply(string name, string email, float cgpa) {
        if (title == "Not Posted") return "Error: No internship posted yet.";
        
        if (applicantCount >= 5) {
            return "Error: Department is full (Max 5 applicants reached).";
        }

        for(int i=0; i<applicantCount; i++) {
            if(applicants[i].getEmail() == email) return "Error: You have already applied here.";
        }

        applicants[applicantCount] = Applicant(name, email, cgpa);
        applicantCount++;
        return "Success: Application Submitted!";
    }

    void sortApplicants() {
        for (int i = 0; i < applicantCount - 1; i++) {
            for (int j = 0; j < applicantCount - i - 1; j++) {
                if (applicants[j].getCGPA() < applicants[j + 1].getCGPA()) {
                    Applicant temp = applicants[j];
                    applicants[j] = applicants[j + 1];
                    applicants[j + 1] = temp;
                }
            }
        }
    }

    void viewAndShortlist() {
        if (applicantCount == 0) {
            cout << "No applicants for " << deptName << " yet.\n";
            return;
        }

        sortApplicants(); 

        cout << "\n--- Applicants for " << deptName << " (Sorted by CGPA) ---\n";
        cout << left << setw(20) << "Name" << setw(10) << "CGPA" << setw(15) << "Status" << endl;
        cout << "------------------------------------------------\n";
        
        for (int i = 0; i < applicantCount; i++) {
            cout << left << setw(20) << applicants[i].getName() 
                 << setw(10) << applicants[i].getCGPA() 
                 << setw(15) << applicants[i].getStatus() << endl;
        }

        cout << "\nDo you want to shortlist top candidates? (1=Yes, 0=No): ";
        int choice; 
        if (!(cin >> choice)) { 
            cin.clear(); cin.ignore(1000, '\n'); choice = 0; 
        }

        if (choice == 1) {
            cout << "\n--- Shortlisting Process ---\n";
            for (int i = 0; i < applicantCount; i++) {
                if (i < 3) { // Select top 3
                    string d, t;
                    cout << "Candidate: " << applicants[i].getName() << " (CGPA: " << applicants[i].getCGPA() << ")\n";
                    cout << "  > Assign Interview Date: "; cin >> d;
                    cout << "  > Assign Interview Time: "; cin >> t;
                    applicants[i].setStatus("Selected");
                    applicants[i].setInterview(d, t);
                    cout << "  > Marked as Selected.\n\n";
                } else {
                    applicants[i].setStatus("Not Selected");
                }
            }
            cout << "Shortlisting Complete.\n";
        }
    }

    void checkStatus(string email) {
        for (int i = 0; i < applicantCount; i++) {
            if (applicants[i].getEmail() == email) {
                cout << "Dept: " << deptName << " | Status: " << applicants[i].getStatus();
                if (applicants[i].getStatus() == "Selected") {
                    cout << " | Interview: " << applicants[i].getInterviewInfo();
                }
                cout << endl;
            }
        }
    }
};

// ==========================================
// Global System Data
// ==========================================
Internship departments[3]; 
UserRole* users[50]; 
int userCount = 0;

void initSystem() {
    departments[0].setDeptName("Computer Science");
    departments[1].setDeptName("Urdu");
    departments[2].setDeptName("Arabic");

    // Admin Account
    users[userCount] = new Admin("admin", "admin123");
    userCount++;
}

// ==========================================
// ADMIN MODULE
// ==========================================
void adminPanel() {
    while (true) {
        cout << "\n================ 2. ADMIN PANEL ================\n";
        cout << "1. Post Internship Notification\n";
        cout << "2. View & Shortlist Applicants\n";
        cout << "3. Logout\n";
        cout << "Enter Choice: ";
        int ch; cin >> ch;

        if (ch == 1) {
            cout << "\n--- Post Internship ---\n";
            cout << "1. Computer Science\n2. Urdu\n3. Arabic\nSelect Dept: ";
            int d; cin >> d;
            
            if(d >= 1 && d <= 3) {
                string t, desc;
                cin.ignore(); // FIX: Clear buffer before getline
                cout << "Enter Title: "; getline(cin, t);
                cout << "Enter Description: "; getline(cin, desc);
                departments[d-1].postInternship(t, desc);
            } else cout << "Invalid Department.\n";
        } 
        else if (ch == 2) {
            cout << "\n--- View Applications ---\n";
            cout << "1. Computer Science\n2. Urdu\n3. Arabic\nSelect Dept: ";
            int d; cin >> d;
            if(d >= 1 && d <= 3) departments[d-1].viewAndShortlist();
            else cout << "Invalid Department.\n";
        } 
        else break;
    }
}

// ==========================================
// STUDENT MODULE
// ==========================================
void studentPanel(string email) {
    while(true) {
        cout << "\n================ 1. JOBSEEKER PANEL ================\n";
        cout << "User: " << email << endl;
        cout << "1. View All Internships\n";
        cout << "2. Apply for Internship\n";
        cout << "3. Check My Status\n";
        cout << "4. Logout\n";
        cout << "Enter Choice: ";
        int ch; cin >> ch;

        if(ch == 1) {
            cout << "\n--- Open Internships ---\n";
            bool found = false;
            for(int i=0; i<3; i++) {
                if(departments[i].getTitle() != "Not Posted") {
                    found = true;
                    cout << "[" << i+1 << "] Dept: " << departments[i].getDeptName() 
                         << "\n    Title: " << departments[i].getTitle() << endl;
                }
            }
            if(!found) cout << "No internships available yet.\n";
        }
        else if(ch == 2) {
            cout << "\n--- Apply for Internship ---\n";
            cout << "1. Computer Science\n2. Urdu\n3. Arabic\nSelect Dept: ";
            int d; cin >> d;
            
            if(d >= 1 && d <= 3) {
                string name; float cgpa;
                cin.ignore(); // FIX: Clear buffer before getline
                cout << "Enter Your Name: "; getline(cin, name);
                cout << "Enter Your CGPA: "; cin >> cgpa;
                cout << departments[d-1].apply(name, email, cgpa) << endl;
            } else cout << "Invalid Department.\n";
        }
        else if(ch == 3) {
            cout << "\n--- Application Status ---\n";
            for(int i=0; i<3; i++) departments[i].checkStatus(email);
        }
        else break;
    }
}

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    initSystem();
    int ch;
    
    while(true) {
        cout << "\n**************************************************\n";
        cout << "          ONLINE INTERNSHIP PORTAL SYSTEM         \n";
        cout << "**************************************************\n";
        cout << "Access Info: [Admin: admin | admin123]\n\n";
        
        cout << "1. Login\n";
        cout << "2. Register (Jobseeker)\n";
        cout << "3. Exit\n";
        cout << "Select Option: ";
        cin >> ch;

        if(ch == 1) {
            string u, p;
            cout << "\n--- LOGIN ---\n";
            cout << "Username/Email: "; cin >> u;
            cout << "Password: "; cin >> p;
            
            bool found = false;
            for(int i=0; i<userCount; i++) {
                if(users[i]->authenticate(u, p)) {
                    found = true;
                    users[i]->panel(); // Polymorphic call
                    break;
                }
            }
            if(!found) cout << "Error: Invalid Credentials.\n";
        }
        else if(ch == 2) {
            if(userCount >= 50) {
                cout << "Error: User Database Full.\n";
                continue;
            }
            string u, p;
            cout << "\n--- REGISTER ---\n";
            cout << "Enter New Email: "; cin >> u;
            
            bool exists = false;
            for(int i=0; i<userCount; i++) {
                if(users[i]->getUsername() == u) exists = true;
            }
            
            if(exists) cout << "Error: Email already exists!\n";
            else {
                cout << "Enter Password: "; cin >> p;
                users[userCount] = new Student(u, p); // Polymorphism
                userCount++;
                cout << "Success: Registered! Please Login.\n";
            }
        }
        else if (ch == 3) {
            cout << "Exiting...\n";
            // Clean up dynamic memory
            for(int i=0; i<userCount; i++) delete users[i];
            break;
        }
        else {
            cout << "Invalid Option.\n";
            cin.clear(); cin.ignore(1000, '\n'); // Fix infinite loop on bad input
        }
    }
    return 0;
}
