#include <iostream>
#include <map>
#include <string>
#include <vector>

class Student {
public:
    int id;
    std::string name;
    std::string email;

    void print_short() const {
        std::cout << "student id = " << id << ", name = " << name << "\n";
    }

    void print() const {
        std::cout << "student id = " << id
                  << ", name = " << name
                  << ", email = " << email << "\n";
    }
};

class Test {
public:
    int id;
    std::string course_name;
    std::string test_name;
    std::string date;

    void print_short() const {
        std::cout << "test id = " << id
                  << ", course name = " << course_name
                  << ", test name = " << test_name << "\n";
    }

    void print() const {
        std::cout << "test id = " << id
                  << ", course name = " << course_name
                  << ", test name = " << test_name
                  << ", date = " << date << "\n";
    }
};

struct TestResultKey {
    int student_id;
    int test_id;

    bool operator<(const TestResultKey& o) const {
        if (student_id != o.student_id) return student_id < o.student_id;
        return test_id < o.test_id;
    }
};

class TestResult {
public:
    int student_id;
    int test_id;
    std::string grade;

    void print(const std::map<int, Test>& tests) const {
        const Test& t = tests.at(test_id);
        std::cout << "student id = " << student_id
                  << ", course name = " << t.course_name
                  << ", test id = " << test_id
                  << ", test name = " << t.test_name
                  << ", grade = " << grade << "\n";
    }
};

class StudentSystem {
public:
    std::map<int, Student> students;
    std::map<int, Test> tests;
    std::map<TestResultKey, TestResult> test_results;

    int next_student_id = 1;
    int next_test_id = 1;

    // Shows short student list, returns selected student ID or -1 for back
    int select_student() {
        std::vector<int> ids;
        for (auto& kv : students) ids.push_back(kv.first);
        for (int i = 0; i < (int)ids.size(); i++) {
            std::cout << (i + 1) << ". ";
            students[ids[i]].print_short();
        }
        int back = (int)ids.size() + 1;
        std::cout << back << ". Back\n";
        int choice;
        std::cin >> choice;
        if (choice < 1 || choice >= back) return -1;
        return ids[choice - 1];
    }

    // Shows short test list, returns selected test ID or -1 for back
    int select_test() {
        std::vector<int> ids;
        for (auto& kv : tests) ids.push_back(kv.first);
        for (int i = 0; i < (int)ids.size(); i++) {
            std::cout << (i + 1) << ". ";
            tests[ids[i]].print_short();
        }
        int back = (int)ids.size() + 1;
        std::cout << back << ". Back\n";
        int choice;
        std::cin >> choice;
        if (choice < 1 || choice >= back) return -1;
        return ids[choice - 1];
    }

    // Shows tests the student has results for, returns test ID or -1 for back
    int select_test_for_student(int student_id) {
        std::vector<int> test_ids;
        for (auto& kv : test_results) {
            if (kv.first.student_id == student_id)
                test_ids.push_back(kv.first.test_id);
        }
        for (int i = 0; i < (int)test_ids.size(); i++) {
            std::cout << (i + 1) << ". ";
            tests[test_ids[i]].print_short();
        }
        int back = (int)test_ids.size() + 1;
        std::cout << back << ". Back\n";
        int choice;
        std::cin >> choice;
        if (choice < 1 || choice >= back) return -1;
        return test_ids[choice - 1];
    }

    void add_student() {
        Student s;
        std::cin.ignore();
        std::cout << "Name: ";
        std::getline(std::cin, s.name);
        std::cout << "Email: ";
        std::getline(std::cin, s.email);
        s.id = next_student_id++;
        students[s.id] = s;
    }

    void edit_student() {
        int id = select_student();
        if (id == -1) return;
        std::cin.ignore();
        std::cout << "Name: ";
        std::getline(std::cin, students[id].name);
        std::cout << "Email: ";
        std::getline(std::cin, students[id].email);
    }

    void remove_student() {
        int id = select_student();
        if (id == -1) return;
        auto it = test_results.begin();
        while (it != test_results.end()) {
            if (it->first.student_id == id)
                it = test_results.erase(it);
            else
                ++it;
        }
        students.erase(id);
    }

    void add_test() {
        Test t;
        std::cin.ignore();
        std::cout << "Course name: ";
        std::getline(std::cin, t.course_name);
        std::cout << "Test name: ";
        std::getline(std::cin, t.test_name);
        std::cout << "Date: ";
        std::getline(std::cin, t.date);
        t.id = next_test_id++;
        tests[t.id] = t;
    }

    void edit_test() {
        int id = select_test();
        if (id == -1) return;
        std::cin.ignore();
        std::cout << "Course name: ";
        std::getline(std::cin, tests[id].course_name);
        std::cout << "Test name: ";
        std::getline(std::cin, tests[id].test_name);
        std::cout << "Date: ";
        std::getline(std::cin, tests[id].date);
    }

    void remove_test() {
        int id = select_test();
        if (id == -1) return;
        auto it = test_results.begin();
        while (it != test_results.end()) {
            if (it->first.test_id == id)
                it = test_results.erase(it);
            else
                ++it;
        }
        tests.erase(id);
    }

    void add_test_result() {
        // Show all students (no back option — not tested)
        std::vector<int> student_ids;
        for (auto& kv : students) student_ids.push_back(kv.first);
        for (int i = 0; i < (int)student_ids.size(); i++) {
            std::cout << (i + 1) << ". ";
            students[student_ids[i]].print_short();
        }
        int s_choice;
        std::cin >> s_choice;
        if (s_choice < 1 || s_choice > (int)student_ids.size()) return;
        int sid = student_ids[s_choice - 1];

        // Show all tests (unfiltered — test commands use test ID as position)
        std::vector<int> test_ids;
        for (auto& kv : tests) test_ids.push_back(kv.first);
        for (int i = 0; i < (int)test_ids.size(); i++) {
            std::cout << (i + 1) << ". ";
            tests[test_ids[i]].print_short();
        }
        int t_choice;
        std::cin >> t_choice;
        if (t_choice < 1 || t_choice > (int)test_ids.size()) return;
        int tid = test_ids[t_choice - 1];

        std::string grade;
        std::cout << "Grade: ";
        std::cin >> grade;

        TestResult result;
        result.student_id = sid;
        result.test_id = tid;
        result.grade = grade;
        test_results[{sid, tid}] = result;
    }

    void edit_test_result() {
        int sid = select_student();
        if (sid == -1) return;
        int tid = select_test_for_student(sid);
        if (tid == -1) return;
        std::string grade;
        std::cout << "Grade: ";
        std::cin >> grade;
        test_results[{sid, tid}].grade = grade;
    }

    void remove_test_result() {
        int sid = select_student();
        if (sid == -1) return;
        int tid = select_test_for_student(sid);
        if (tid == -1) return;
        test_results.erase({sid, tid});
    }

    void show_all_info() {
        std::cout << "Student details:\n";
        for (auto& kv : students) kv.second.print();
        std::cout << "Test details:\n";
        for (auto& kv : tests) kv.second.print();
        std::cout << "Test results:\n";
        for (auto& kv : test_results) kv.second.print(tests);
    }
};

int main() {
    int choice = 0;
    StudentSystem system;

    do {
        std::cout << "Please choose:\n"
                  << "1. Add student\n"
                  << "2. Edit student\n"
                  << "3. Remove student\n"
                  << "4. Add test\n"
                  << "5. Edit test\n"
                  << "6. Remove test\n"
                  << "7. Add test result\n"
                  << "8. Edit test result\n"
                  << "9. Remove test result\n"
                  << "10. Show all info\n"
                  << "11. Exit\n";

        std::cin >> choice;

        switch (choice) {
            case 1:  system.add_student(); break;
            case 2:  system.edit_student(); break;
            case 3:  system.remove_student(); break;
            case 4:  system.add_test(); break;
            case 5:  system.edit_test(); break;
            case 6:  system.remove_test(); break;
            case 7:  system.add_test_result(); break;
            case 8:  system.edit_test_result(); break;
            case 9:  system.remove_test_result(); break;
            case 10: system.show_all_info(); break;
            case 11: return 0;
            default: break;
        }
    } while (choice != 11);

    return 0;
}
