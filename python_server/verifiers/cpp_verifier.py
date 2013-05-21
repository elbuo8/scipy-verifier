import json
import logging
import re
import uuid
import os
import sys
import pwd
from Queue import Queue
import subprocess

test_header = """
#include "UnitTest++.h"
//Solutions
%s

//Tests
%s

int main() {
  return UnitTest::RunAllTests();
}
"""


def run_cpp_instance(jsonrequest, outQueue):
    """ run a CPP instance and  test the code"""
    #load json data in python object
    try:
        jsonrequest = json.loads(jsonrequest)
        solution = str(jsonrequest["solution"])
        tests = str(jsonrequest["tests"])
    except BaseException:
        responseDict = {'errors': 'Bad request'}
        logging.error("Bad request")
        responseJSON = json.dumps(responseDict)
        outQueue.put(responseJSON)
        return

    resultList = []
    solved = False

    uid = uuid.uuid4()
    test_path = '../UnitTest++/solutions/'
    if not os.path.isdir(test_path):
        os.mkdir(test_path)
    test_file = test_path + 'CPPSolution_%s.cpp' % uid
    _test = open(test_file, "w+")
    _test.write(test_header % (solution, tests))
    _test.close()

    cmd = ("g++ -o ../UnitTest++/solutions/%s " % uid) + (test_path + 'CPPSolution_%s.cpp ' % uid) + '../UnitTest++/libUnitTest++.a  -I ../UnitTest++/src'
    cmd = cmd.split()
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, close_fds=False)
    p.wait()
    stdout, stderr = p.communicate()
    cmd = ('../UnitTest++/solutions/%s' % uid)
    cmd = cmd.split()
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, close_fds=False)
    p.wait()
    stdout, stderr = p.communicate()
    if len(stderr) > 0:
        responseDict = {'errors': stderr}
        responseJSON = json.dumps(responseDict)
        outQueue.put(responseJSON)
        return

    lines = stdout.split('\n')
    lines.pop()
    for line in lines:
        values = line.split(':DELIMITER:') #sooo creative right?
        #{"expected": "", "received": "", "call": "test_sum", "correct": true}
        resultList.append({"expected": values[1], "received": values[2], "call": values[0], "correct": values[1] == values[2]})

    responseDict = {"solved": solved, "results": resultList, "printed":None}
    responseJSON = json.dumps(responseDict)
    outQueue.put(responseJSON)



if __name__ == '__main__':
    #pw_record = pwd.getpwnam("verifiers")
    #user_name = pw_record.pw_name
    #user_home_dir = pw_record.pw_dir
    #user_uid = pw_record.pw_uid
    #user_gid = pw_record.pw_gid
    '''os.environ['HOME'] = user_home_dir
    os.environ['LOGNAME'] = user_name
    os.environ['USER'] = user_name
    os.environ['LANGUAGE'] = "en_US.UTF-8"
    os.environ['LANG'] = "en_US.UTF-8"
    os.environ['LC_ALL'] = "en_US.UTF-8"
    os.setgid(user_gid)
    os.setuid(user_uid)'''
    jsonrequet = '''{"solution": "const int a = 101;", "tests":  "TEST(TooSimple){CHECK_EQUAL(a,101);}"}'''
    #sys.argv[1]
    out = Queue()
    run_cpp_instance(jsonrequet, out)
    print out.get()
