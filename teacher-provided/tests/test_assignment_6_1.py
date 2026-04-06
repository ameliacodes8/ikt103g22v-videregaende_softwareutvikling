import os
import random
import subprocess
import time

import pytest
import requests

from assignment_helpers import *


base_url = 'http://localhost:5000'


@pytest.fixture(autouse=True)
def server(paths):
    owd, _ = paths
    path = os.path.join(owd, 'assignment_6_server.py')
    proc = subprocess.Popen(['python3', path], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    time.sleep(0.5)
    yield proc
    proc.kill()


class TestAssignment61:
    def test_get_students(self, app):
        students = requests.get(f'{base_url}/students/').json()
        app.check(['1', '6'], [student_to_string(student) for student in students])

    def test_get_student_by_id(self, app):
        students = requests.get(f'{base_url}/students/').json()
        student = random.choice(students)
        students.remove(student)

        app.check(['2', student['id'], '6'], [student_to_string(student)], [student_to_string(s) for s in students])

    def test_get_student_by_id_invalid(self, app):
        id = requests.get(f'{base_url}/nextId').json()['nextId']
        app.check(['2', id, '6'], ['Student not found'])

    def test_add_student(self, app):
        student = get_student()
        del student['id']

        student_expected = student.copy()
        student_expected['id'] = requests.get(f'{base_url}/nextId').json()['nextId']

        app.check(['3'] + list(student.values()) + ['6'], ['Added student: ' + student_to_string(student_expected)])

    def test_edit_student(self, app):
        students = requests.get(f'{base_url}/students/').json()

        old_student = random.choice(students)
        new_student = get_student(old_student['id'])

        app.check(['4'] + list(new_student.values()) + ['1', '6'],
                  ['Student was edited successfully', student_to_string(new_student)],
                  [student_to_string(old_student)])

    def test_edit_student_invalid(self, app):
        id = requests.get(f'{base_url}/nextId').json()['nextId']
        student = get_student(id)

        app.check(['4'] + list(student.values()) + ['1', '6'], ['Student not found'], [student_to_string(student)])

    def test_remove_student(self, app):
        students = requests.get(f'{base_url}/students/').json()
        student = random.choice(students)

        app.check(['5', student['id'], '1', '6'], ['Student was removed successfully'], [student_to_string(student)])

    def test_remove_student_invalid(self, app):
        id = requests.get(f'{base_url}/nextId').json()['nextId']
        app.check(['5', id, '1', '6'], ['Student not found'], ['Student was removed successfully'])

    def test_exit(self, app):
        app.check(['6'], [])
