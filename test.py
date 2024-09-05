import random
from subprocess import run, PIPE

TEST_BINARY = './vec_test'
LINES = 256
LINE_SIZE = 256

p = run(['make'], stdout=PIPE, encoding='ascii')
print(p.stdout)

input_line = ''

for _ in range(LINES):
    for _ in range(LINE_SIZE + random.randint(-50, 50)):
        input_line += chr(random.randint(97, 97 + 25))
    input_line += '\n'
input_line += '\n'

p = run([TEST_BINARY], stdout=PIPE, input=input_line, encoding='ascii')

output = p.stdout

TESTS = 2
input_index = output.find(input_line[:-1])

if input_index != -1:
    print(f"TEST 1/{TESTS} Passed: Input found at offset {input_index}!")

if output.count('freed!'):
    print(f"TEST 2/{TESTS} Passed: Freed lines = input lines!")

realloc_calls = output.count('+++ realloc')
print(f"{realloc_calls} times realloc() called")


