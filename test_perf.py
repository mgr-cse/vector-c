import random
from subprocess import run, PIPE

TEST_BINARY = './perf_test'
INPUT_SIZE = int(10e5) - 1;

p = run(['make', 'perf_test'], stdout=PIPE, encoding='ascii')
print(p.stdout)

input_line = ''

for _ in range(INPUT_SIZE):
    input_line += chr(random.randint(97, 97 + 25))
input_line += '\n'

for _ in range(INPUT_SIZE):
    input_line += chr(random.randint(97, 97 + 25))
input_line += '\n'

p = run([TEST_BINARY], stdout=PIPE, input=input_line, encoding='ascii')

print(p.stdout)
