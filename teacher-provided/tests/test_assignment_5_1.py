import sqlite3

import pytest

from assignment_helpers import *


@pytest.fixture()
def students(database):
    nextId = 1

    c = database.cursor()

    students = []
    for i in range(random.randint(5, 10)):
        student = get_student(nextId)

        students.append(student)
        nextId += 1

        c.execute('INSERT INTO students VALUES (?,?,?,?)', tuple(student.values()))

    database.commit()

    return students


@pytest.fixture(autouse=True)
def database(paths):
    conn = sqlite3.connect('school.sqlite')

    c = conn.cursor()

    c.execute('''
        CREATE TABLE students
        (
            id integer
                constraint students_pk
                    primary key autoincrement,
            name text,
            email text,
            year integer
        )
    ''')

    conn.commit()

    return conn


def get_students_from_database(database):
    c = database.cursor()
    c.execute('SELECT * FROM students')
    return c.fetchall()


class TestAssignment51:
    def test_get_students_empty_table(self, app, database):
        app.check(['1', '7'], ['No students found'])

    def test_get_students_filled_table(self, app, database, students):
        app.check(['1', '7'], [student_to_string(student) for student in students])

    def test_add_student_empty_table(self, app, database):
        student = get_student()

        student_expected = student.copy()
        student_expected['id'] = 1

        del student['id']

        app.check(['3'] + list(student.values()) + ['7'], ['Added student: ' + student_to_string(student_expected)])

        assert tuple(student_expected.values()) in get_students_from_database(database),\
            'Failed to find new student in database.'

    def test_add_student_filled_table(self, app, database, students):
        student = get_student()

        student_expected = student.copy()
        student_expected['id'] = len(students) + 1

        del student['id']

        app.check(['3'] + list(student.values()) + ['7'], ['Added student: ' + student_to_string(student_expected)])

        assert tuple(student_expected.values()) in get_students_from_database(database),\
            'Failed to find new student in database.'

    def test_edit_student_empty_table(self, app, database):
        app.check(['4', '1', '7'], ['Student not found'])

    def test_edit_student_filled_table(self, app, database, students):
        old_student = random.choice(students)
        new_student = get_student(old_student['id'])

        app.check(['4'] + list(new_student.values()) + ['1', '7'],
                  ['Student was edited successfully', student_to_string(new_student)],
                  [student_to_string(old_student)])

        assert tuple(new_student.values()) in get_students_from_database(database),\
            'Failed to find edited student in database.'

        assert tuple(old_student.values()) not in get_students_from_database(database),\
            'Found unedited student in database.'

    def test_remove_student_empty_table(self, app, database):
        app.check(['5', '1', '7'], ['Student not found'])

    def test_remove_student_filled_table(self, app, database, students):
        student = random.choice(students)

        app.check(['5', student['id'], '1', '7'], ['Student was removed successfully'], [student_to_string(student)])

        assert tuple(student.values()) not in get_students_from_database(database),\
            'Found removed student in database.'

    @pytest.mark.parametrize("type", ['starts', 'contains', 'ends'])
    def test_search(self, app, database, students, type):
        student = random.choice(students)

        expected = []
        unexpected = students.copy()
        search = None

        if type == 'starts':
            text = student['name'].split()[0]
            search = text + '%'

            for s in students:
                if s['name'].startswith(text):
                    expected.append(s)
                    unexpected.remove(s)

        if type == 'contains':
            name = student['name']
            start = random.randint(1, len(name) // 2)
            end = random.randint(start + 1, len(name) - 1)

            text = student['name'][start:end]
            search = '%' + text + '%'

            for s in students:
                if text.lower() in s['name'].lower():
                    expected.append(s)
                    unexpected.remove(s)

        if type == 'ends':
            text = student['name'].split()[-1]
            search = '%' + text

            for s in students:
                if s['name'].endswith(text):
                    expected.append(s)
                    unexpected.remove(s)

        app.check(['6', search, '7'],
                  [student_to_string(s) for s in expected], [student_to_string(s) for s in unexpected])

    def test_exit(self, app):
        app.check(['7'], [])
