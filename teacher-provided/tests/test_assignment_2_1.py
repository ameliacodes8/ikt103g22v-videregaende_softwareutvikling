import random

import pytest


class Student:
    def __init__(self, id, name, email):
        self.id = id
        self.name = name
        self.email = email

    def cmd(self):
        return [self.name, self.email]

    def __str__(self):
        return "student id = %i, name = %s, email = %s" % (self.id, self.name, self.email)


# Name workaround, can't start with test
class MyTest:
    def __init__(self, id, cname, tname, date):
        self.id = id
        self.cname = cname  # Course name
        self.tname = tname  # Test name
        self.date = date

    def cmd(self):
        return [self.cname, self.tname, self.date]

    def __str__(self):
        return "test id = %i, course name = %s, test name = %s, date = %s"\
               % (self.id, self.cname, self.tname, self.date)


# Name workaround, can't start with test
class MyTestResult:
    def __init__(self, sid, cname, tid, tname, grade):
        self.sid = sid  # Student id
        self.cname = cname  # Course name
        self.tid = tid  # Test id
        self.tname = tname  # Test name
        self.grade = grade

    def __str__(self):
        return "student id = %i, course name = %s, test id = %i, test name = %s, grade = %s"\
               % (self.sid, self.cname, self.tid, self.tname, self.grade)


class Data:
    def __init__(self, fake):
        # Students
        self.sd = []
        self.sde = []

        for i in range(3):
            profile = fake.profile()
            student = Student(i + 1, profile['name'], profile['mail'])
            self.sd.append(student)

            profile = fake.profile()
            student = Student(i + 1, profile['name'], profile['mail'])
            self.sde.append(student)

        # Student commands
        self.sc = []

        for s in self.sd:
            self.sc.extend([1, s.name, s.email])

        # Tests
        self.td = []
        self.tde = []

        codes = random.sample(range(100, 200), 6)

        for i in range(3):
            # Test data
            course = f'IKT{codes[i]}'
            test = MyTest(i + 1, course, f'{course} exam', f'2022.05.0{i}')
            self.td.append(test)

            # Test data edited
            course = f'IKT{codes[i + 3]}'
            test = MyTest(i + 1, course, f'{course} exam', f'2022.05.1{i}')
            self.tde.append(test)

        # Test commands
        self.tc = []
        for t in self.td:
            self.tc.extend([4, t.cname, t.tname, t.date])

        # Test result data, generate from student and test list
        self.trd = []
        self.trde = []

        for s in self.sd:
            for t in self.td:
                self.trd.append(MyTestResult(s.id, t.cname, t.id, t.tname, (s.id - 1) * len(self.sd) + t.id))
                self.trde.append(MyTestResult(s.id, t.cname, t.id, t.tname, (s.id - 1) * len(self.sd) + t.id + 10))

        # Test result commands
        self.trc = []
        for tr in self.trd:
            self.trc.extend([7, tr.sid, tr.tid, tr.grade])


@pytest.fixture
def data(fake):
    return Data(fake)


class TestAssignment21:
    def test_exit(self, app):
        app.check(11)

    def test_add_students(self, app, data):
        app.check(data.sc + [10, 11], data.sd)

    def test_edit_student_back(self, app, data):
        app.check(data.sc + [2, 4, 11])

    def test_edit_first_student(self, app, data):
        app.check(data.sc + [2, 1] + data.sde[0].cmd() + [10, 11], [data.sde[0]] + data.sd[1:], [data.sd[0]])

    def test_edit_last_student(self, app, data):
        app.check(data.sc + [2, 3] + data.sde[2].cmd() + [10, 11], data.sd[:2] + [data.sde[2]], [data.sd[2]])

    def test_remove_student_back(self, app, data):
        app.check(data.sc + [3, 4, 11], [])

    def test_remove_first_student(self, app, data):
        app.check(data.sc + [3, 1, 10, 11], data.sd[1:], [data.sd[0]])

    def test_remove_last_student(self, app, data):
        app.check(data.sc + [3, 3, 10, 11], data.sd[:-1], [data.sd[2]])

    def test_add_tests(self, app, data):
        app.check(data.tc + [10, 11], data.td)

    def test_edit_test_back(self, app, data):
        app.check(data.tc + [5, 4, 11], [])

    def test_edit_first_test(self, app, data):
        app.check(data.tc + [5, 1] + data.tde[0].cmd() + [10, 11], [data.tde[0]] + data.td[1:], [data.td[0]])

    def test_edit_last_test(self, app, data):
        app.check(data.tc + [5, 3] + data.tde[2].cmd() + [10, 11], data.td[:2] + [data.tde[2]], [data.td[2]])

    def test_remove_test_back(self, app, data):
        app.check(data.tc + [6, 4, 11], [])

    def test_remove_first_test(self, app, data):
        app.check(data.tc + [6, 1, 10, 11], data.td[1:], [data.td[0]])

    def test_remove_last_test(self, app, data):
        app.check(data.tc + [6, 3, 10, 11], data.td[:-1], [data.td[2]])

    def test_add_test_results(self, app, data):
        app.check(data.sc + data.tc + data.trc + [10, 11], data.trd)

    def test_edit_test_result_student_back(self, app, data):
        app.check(data.sc + data.tc + data.trc + [8, 4, 11], [])

    def test_edit_test_result_test_back(self, app, data):
        app.check(data.sc + data.tc + data.trc + [8, 1, 4, 11], [])

    def test_edit_test_result_first_student_first_test(self, app, data):
        app.check(data.sc + data.tc + data.trc + [8, 1, 1, data.trde[0].grade, 10, 11],
                  data.sd + data.td + [data.trde[0]] + data.trd[1:], [data.trd[0]])

    def test_edit_test_result_first_student_last_test_back(self, app, data):
        app.check(data.sc + data.tc + data.trc + [8, 1, 3, data.trde[2].grade, 10, 11],
                  data.sd + data.td + data.trd[:2] + [data.trde[2]] + data.trd[3:], [data.trd[2]])

    def test_edit_test_result_last_student_first_test_back(self, app, data):
        app.check(data.sc + data.tc + data.trc + [8, 3, 1, data.trde[6].grade, 10, 11],
                  data.sd + data.td + data.trd[:6] + [data.trde[6]] + data.trd[7:], [data.trd[6]])

    def test_edit_test_result_last_student_last_test_back(self, app, data):
        app.check(data.sc + data.tc + data.trc + [8, 3, 3, data.trde[8].grade, 10, 11],
                  data.sd + data.td + data.trd[:-1] + [data.trde[8]], [data.trd[8]])

    def test_remove_test_result_first_student_first_test(self, app, data):
        app.check(data.sc + data.tc + data.trc + [9, 1, 1, 10, 11], data.sd + data.td + data.trd[1:], [data.trd[0]])

    def test_remove_test_result_first_student_last_test(self, app, data):
        app.check(data.sc + data.tc + data.trc + [9, 1, 3, 10, 11], data.sd + data.td + data.trd[:2] + data.trd[3:],
                  [data.trd[2]])

    def test_remove_test_result_last_student_first_test(self, app, data):
        app.check(data.sc + data.tc + data.trc + [9, 3, 1, 10, 11], data.sd + data.td + data.trd[:6] + data.trd[7:],
                  [data.trd[6]])

    def test_remove_test_result_last_student_last_test(self, app, data):
        app.check(data.sc + data.tc + data.trc + [9, 3, 3, 10, 11], data.sd + data.td + data.trd[:-1], [data.trd[-1]])
