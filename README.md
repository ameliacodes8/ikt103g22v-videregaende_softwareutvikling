# IKT103 — Videregående Softwareutvikling

Course work and assignments from **IKT103 - Videregående Softwareutvikling** at the University of Agder (UiA).

## Repository Structure

```
ikt103-final-exam/          C++ SFML Super Mario game (group final exam project)
assignment_2_1/             Abstract data types and data structures in C++
assignment_4/
  assignment_4_1/           Reading and processing CSV data (rapidcsv)
  assignment_4_2/           Reading and processing JSON data (RapidJSON)
assignment_5_1/             SQLite database operations in C++ (SQLiteCpp)
assignment_6_1/             C++ REST client using cpprestsdk (Casablanca)
libraries/                  Reference examples for third-party libraries
teacher-provided/           Course examples and assignment tests (see attribution below)
```

## Building

Each assignment uses CMake. From an assignment folder:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

**Dependencies:**
- C++11 or later
- SFML (final exam game)
- cpprestsdk / Casablanca (assignment_6_1)
- SQLiteCpp is bundled in assignment_5_1/thirdparty/

## Author

Student project — University of Agder, IKT103 group 14.

## Attribution

The `teacher-provided/` folder contains example code and automated tests written by the course instructor (Christian Auby / IKT103). These are included for personal reference and learning purposes only. I do not claim authorship of any code in that directory.

Third-party libraries used in assignments (rapidcsv, RapidJSON, SQLiteCpp, sqlite_orm) are the work of their respective authors and are included under their original licences.
