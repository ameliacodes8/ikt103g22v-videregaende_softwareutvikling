#include <iostream>
#include <string>
#include "thirdparty/SQLiteCpp/include/SQLiteCpp/Database.h"
#include "thirdparty/SQLiteCpp/include/SQLiteCpp/Statement.h"
#include "thirdparty/SQLiteCpp/include/SQLiteCpp/Column.h"
#include "student.h"

//CREATE TABLE students(
//    id INTEGER PRIMARY KEY AUTOINCREMENT,
//    name            TEXT    NOT NULL,
//    email           TEXT    NOT NULL,
//    year            INT     NOT NULL
//);

int printStudent(SQLite::Statement &query) {
    auto id = query.getColumn(0);
    auto name = query.getColumn(1);
    auto email = query.getColumn(2);
    auto year = query.getColumn(3);

    std::cout   << "id: "
                << id
                << ", name: "
                << name
                << ", email: "
                << email
                << ", year: "
                << year
                << std::endl;
    return 0;
}

void readAll(SQLite::Database &db) {
    auto sql = "select * FROM students order by id";
    bool empty = true;
    SQLite::Statement query(db, sql);
    while (query.executeStep()) {
        empty = false;
        printStudent(query);
    }
    if (empty) {
        std::cout << "No students found" << std::endl;
    }
}

void getByID(SQLite::Database &db) {
    int id;
    std::cout << "ID: ";
    std::cin >> id;

    try {
        SQLite::Statement   query(db, "select * from students where id = ?");
        query.bind(1, id);
        bool empty = true;
        while (query.executeStep()) {
            empty = false;
            printStudent(query);
        }

        if (empty) {
            std::cout << "Student not found" << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

void addStudent(SQLite::Database &db) {
    int id;
    std::string name, email;
    int year;

    std::cin.ignore();
    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Email: ";
    std::getline(std::cin, email);

    std::cout << "Year: ";
    std::cin >> year;

    try {
        auto sql = "insert into students (name, email, year) VALUES ('"+name+"', '"+email+"', '"+ std::to_string(year)+"')";
        SQLite::Statement query(db, sql);
        query.exec();
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }

    try {
        auto sql = "select id FROM students order by id desc limit 1";
        SQLite::Statement query(db, sql);
        while (query.executeStep()) {
            id = query.getColumn(0);
        }
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }

    std::cout    << "Added student: id: "
                 << id
                 << ", name: "
                 << name
                 << ", email: "
                 << email
                 << ", year: "
                 << year
                 << std::endl;
}

Student getStudent(SQLite::Database &db, int id) {
    Student student;

    try {
        SQLite::Statement   query(db, "select * from students where id = ?");
        query.bind(1, id);
        while (query.executeStep()) {
            student.id = id;
            student.name = query.getColumn(1).getString();
            student.email = query.getColumn(2).getString();
            student.year = query.getColumn(3).getInt();
        }
        return student;
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

void editStudent(SQLite::Database &db) {
    int id;
    std::string name, email;
    int year;

    std::cout << "ID: ";
    std::cin >> id;

    Student s = getStudent(db, id);
    if (s.name.empty()) {
        std::cout << "Student not found" << std::endl;
        return;
    }

    std::cin.ignore();
    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Email: ";
    std::getline(std::cin, email);

    std::cout << "Year: ";
    std::cin >> year;

    try {
        SQLite::Statement   query(db, "update students set name = ?, email = ?, year = ? where id = ?");
        query.bind(1, name);
        query.bind(2, email);
        query.bind(3, year);
        query.bind(4, id);
        query.exec();
        std::cout << "Student was edited successfully" << std::endl;
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

void deleteStudent(SQLite::Database &db) {
    int id;

    std::cout << "ID: ";
    std::cin >> id;

    Student s = getStudent(db, id);
    if (s.name.empty()) {
        std::cout << "Student not found" << std::endl;
        return;
    }

    try {
        SQLite::Statement   query(db, "delete from students where id = ?");
        query.bind(1, id);
        query.exec();
        std::cout << "Student was removed successfully" << std::endl;
    } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

void searchStudents(SQLite::Database &db) {
    std::string search;

    std::cout << "Search string: ";
    std::cin.ignore();
    std::getline(std::cin, search);

    bool empty = true;
    SQLite::Statement query(db, "select * FROM students where name like ?");
    query.bind(1, search);
    while (query.executeStep()) {
        empty = false;
        printStudent(query);
    }
    if (empty) {
        std::cout << "No students found" << std::endl;
    }
}

int main() {
    SQLite::Database db("school.sqlite", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    int choice = 0;

    do {
        std::cout   << "1. Read all students\n"
                    << "2. Get student by id\n"
                    << "3. Add student\n"
                    << "4. Edit student\n"
                    << "5. Remove student\n"
                    << "6. Search\n"
                    << "7. Exit\n";
        std::cin >> choice;

        switch (choice) {
            case 1: readAll(db); break;
            case 2: getByID(db); break;
            case 3: addStudent(db); break;
            case 4: editStudent(db); break;
            case 5: deleteStudent(db); break;
            case 6: searchStudents(db); break;
            case 7: return 0;
            default: std::cout << "Invalid option, try again" << std::endl; break;
        }
    } while (choice != 7);
}
