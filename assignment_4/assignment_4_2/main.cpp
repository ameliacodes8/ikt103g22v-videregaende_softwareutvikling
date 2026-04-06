#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include <fstream>
#include <list>
#include "student.h"

using namespace rapidjson;

std::string getFileContent(const std::string& fileName) {
    std::ifstream ifs(fileName);
    std::string content( (std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));

    return content;
}

int main() {
    std::list<Student*> studentList;
    std::list<Student> badStudents;
    //auto json = getFileContent("C:\\Users\\helga\\ikt103g22v\\assignments\\solutions\\assignment_4_2\\students.json");
    auto json = getFileContent("students.json");
    char char_array[json.length()+1];
    strcpy(char_array, json.c_str());
    Document document;
    document.Parse(char_array);

    auto arr = document.GetArray();
    for (int i = 0; i < arr.Size(); i++) {
        auto &row = arr[i];

        Student* newStudent(new Student());
        newStudent->id = row["id"].GetInt();
        newStudent->name = row["name"].GetString();
        newStudent->age = row["age"].GetInt();
        newStudent->attendance = row["attendance"].GetInt();
        studentList.push_back(newStudent);
    }

    bool first = true;
    Student youngest;
    Student oldest;
    int numberOfStudents = 0;
    int totalAge = 0;

    for (std::list<Student*>::iterator it=studentList.begin(); it != studentList.end();++it) {
        numberOfStudents++;
        totalAge += (*it)->age;

        if ((*it)->attendance < 30) {
            badStudents.push_back(*(*it));
        }

        if (first) {
            youngest = *(*it);
            oldest = *(*it);
            first = false;
            continue;
        }

        if ((*it)->age > oldest.age) {
            oldest = *(*it);
        }
        if ((*it)->age < youngest.age) {
            youngest = *(*it);
        }
    }
    std::list<Student>::iterator student;
    std::cout   << "Youngest: "
                << youngest.name
                << std::endl

                << "Oldest: "
                << oldest.name
                << std::endl

                << "Average age: "
                << (totalAge / numberOfStudents)
                << std::endl;

    for (student = badStudents.begin(); student != badStudents.end(); ++student) {
        std::cout   << "Bad student: "
                    << student->name
                    << std::endl;
    }

}
