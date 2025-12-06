

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For sorting
#include <iomanip>

using namespace std;
class Applicant {
private:
    string name;
    string email;
    float cgpa;
    string status; // "Pending", "Selected", "Not Selected"
    string interviewDate;
    string interviewTime;

public:
    Applicant(string n, string e, float c) {
        name = n;
        email = e;
        cgpa = c;
        status = "Pending";
        interviewDate = "N/A";
        interviewTime = "N/A";
    }
    float getCGPA() const { return cgpa; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getStatus() const { return status; }
    string getInterviewDetails() const { return interviewDate + " " + interviewTime; }

    void setStatus(string s) { status = s; }
    void setInterview(string date, string time) {
        interviewDate = date;
        interviewTime = time;
    }
};
class Internship {
private:
    string deptName;
    string title;
    string description;
    const int seatsAvailable = 3; // Fixed as per SRS [cite: 74]
    vector<Applicant> applicants;
    static bool compareCGPA(const Applicant &a, const Applicant &b) {
        return a.getCGPA() > b.getCGPA();
    }

public:
    Internship(string dept) {
        deptName = dept;
        title = "Not Posted";
        description = "N/A";
    }

    void postInternship(string t, string d) {
        title = t;
        description = d;
    }

    string getTitle() const { return title; }
    string getDeptName() const { return deptName; }
    string getDescription() const { return description; }
    int getSeatCount() const { return seatsAvailable; }

    string apply(string name, string email, float cgpa) {
        if (title == "Not Posted") return "Error: No internship posted yet.";
        
        
        if (applicants.size() >= 5) {
            return "Error: No more applicants allowed for this department.";
        }

        
        for (const auto &app : applicants) {
            if (app.getEmail() == email) return "You have already applied.";
        }

        applicants.push_back(Applicant(name, email, cgpa));
        return "Application Submitted Successfully!";
    }

   
    void viewAndShortlist() {
        if (applicants.empty()) {
            cout << "No applicants for " << deptName << " yet.\n";
            return;
        }


        sort(applicants.begin(), applicants.end(), compareCGPA);

        cout << "\n--- Applicants for " << deptName << " (Sorted by CGPA) ---\n";
        cout << left << setw(15) << "Name" << setw(10) << "CGPA" << setw(15) << "Status" << endl;
        for (const auto &app : applicants) {
            cout << left << setw(15) << app.getName() << setw(10) << app.getCGPA() << setw(15) << app.getStatus() << endl;
        }

        cout << "\nShortlist top candidates now? (1=Yes, 0=No): ";
        int choice; cin >> choice;

        if (choice == 1) {
            int count = 0;
            for (auto &app : applicants) {
                if (count < 3) { // Select top 3 [cite: 127]
                    string date, time;
                    cout << "Enter Interview Date for " << app.getName() << ": "; cin >> date;
                    cout << "Enter Interview Time: "; cin >> time;
                    app.setStatus("Selected");
                    app.setInterview(date, time);
                } else {
                    app.setStatus("Not Selected");
                }
                count++;
            }
            cout << "Shortlisting Complete.\n";
        }
    }

    
    void checkStatus(string email) {
        for (const auto &app : applicants) {
            if (app.getEmail() == email) {
                cout << "Dept: " << deptName << " | Status: " << app.getStatus();
                if (app.getStatus() == "Selected") {
                    cout << " | Interview: " << app.getInterviewDetails();
                }
                cout << endl;
            }
        }
    }
};


class User {
private:
    string username;
    string password;
    string role; 

public:
    User(string u, string p, string r) : username(u), password(p), role(r) {}

    bool authenticate(string u, string p) {
        return (username == u && password == p);
    }

    string getRole() const { return role; }
    string getUsername() const { return username; }
};


vector<Internship> departments;
vector<User> users;

void initSystem() {
    
    departments.push_back(Internship("Computer Science"));
    departments.push_back(Internship("Urdu"));
    departments.push_back(Internship("Arabic"));

    users.push_back(User("admin", "admin123", "admin")); // [cite: 148]
}

void adminPanel() {
    while (true) {
        cout << "\n=== ADMIN PANEL ===\n";
        cout << "1. Post Internship\n";
        cout << "2. Shortlist Applicants\n";
        cout << "3. Logout\nChoice: ";
        int ch; cin >> ch;

        if (ch == 1) {
            cout << "\nSelect Department:\n";
            for(size_t i=0; i<departments.size(); i++) 
                cout << i+1 << ". " << departments[i].getDeptName() << endl;
            
            int d; cin >> d;
            if(d >= 1 && d <= 3) {
                string t, desc;
                cin.ignore();
                cout << "Title: "; getline(cin, t);
                cout << "Description: "; getline(cin, desc);
                departments[d-1].postInternship(t, desc);
                cout << "Internship Posted.\n";
            }
        } 
        else if (ch == 2) {
             cout << "\nSelect Department:\n";
            for(size_t i=0; i<departments.size(); i++) 
                cout << i+1 << ". " << departments[i].getDeptName() << endl;
            
            int d; cin >> d;
            if(d >= 1 && d <= 3) departments[d-1].viewAndShortlist();
        } 
        else break;
    }
}

void studentPanel(string email) {
    while(true) {
        cout << "\n=== STUDENT PANEL (" << email << ") ===\n";
        cout << "1. View Internships\n";
        cout << "2. Apply\n";
        cout << "3. My Status\n";
        cout << "4. Logout\nChoice: ";
        int ch; cin >> ch;

        if(ch == 1) {
            for(const auto &dept : departments) {
                if(dept.getTitle() != "Not Posted") {
                    cout << "Dept: " << dept.getDeptName() << " | Title: " << dept.getTitle() << endl;
                }
            }
        }
        else if(ch == 2) {
            cout << "\nSelect Department:\n";
            for(size_t i=0; i<departments.size(); i++) 
                cout << i+1 << ". " << departments[i].getDeptName() << endl;
            int d; cin >> d;
            if(d >= 1 && d <= 3) {
                string name; float cgpa;
                cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter CGPA: "; cin >> cgpa;
                
                // Calling Class Method
                cout << departments[d-1].apply(name, email, cgpa) << endl;
            }
        }
        else if(ch == 3) {
            for(auto &dept : departments) dept.checkStatus(email);
        }
        else break;
    }
}


int main() {
    initSystem();
    int ch;
    
    while(true) {
        cout << "\n--- ONLINE INTERNSHIP PORTAL ---\n";
        cout << "1. Login\n2. Register\n3. Exit\nChoice: ";
        cin >> ch;

        if(ch == 1) {
            string u, p;
            
            cout << "Email/User: "; cin >> u;
            cout << "Password: "; cin >> p;
            
            bool loginSuccess = false;
            for(auto &user : users) {
                if(user.authenticate(u, p)) {
                    loginSuccess = true;
                    if(user.getRole() == "admin") adminPanel();
                    else studentPanel(user.getUsername());
                    break;
                }
            }
            if(!loginSuccess) cout << "Invalid Credentials.\n";
        }
        else if(ch == 2) {
            string u, p;
            cout << "Enter New Email: "; cin >> u;
            // Check duplicate
            bool exists = false;
            for(auto &user : users) if(user.getUsername() == u) exists = true;
            
            if(exists) cout << "Email already exists!\n";
            else {
                cout << "Enter Password: "; cin >> p;
                users.push_back(User(u, p, "jobseeker"));
                cout << "Registered! Please Login.\n";
            }
        }
        else break;
    }
    return 0;
}1