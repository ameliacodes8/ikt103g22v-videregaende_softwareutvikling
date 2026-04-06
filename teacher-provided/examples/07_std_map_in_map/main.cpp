/*

Shows how to store a map container inside a map container
Shows how to set values on the innermost value in such a container
Shows how to iterate a container and then iterate the container it contains

*/

#include <iostream>
#include <map>

// Create an alias type for a map with string to int lookup.
// The key represents a course name and the int the course grade.
typedef std::map<std::string, int> Grades;

// Create an alias type for a map with string to map with string to int lookup.
// The key represents a student name, and the value a list of grades for that student.
typedef std::map<std::string, Grades> Students;

int main()
{
    // Create container for students
    Students students;

    // Add some students to it
    students["eric"]["dat119"] = 4;
    students["eric"]["dat220"] = 3;
    students["lisa"]["dat119"] = 6;
    students["lisa"]["dat220"] = 2;

    // Iterate all students
    for(const auto &student: students)
    {
        // Print student name
        std::cout << student.first << ":" << std::endl;

        // Iterate and print all grades of this student
        for(const auto& grade: student.second)
            std::cout << grade.first << ": " << grade.second << std::endl;

        std::cout << std::endl;
    }

    return 0;
}
