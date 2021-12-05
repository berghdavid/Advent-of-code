import fileinput

pipes = list()
matrix = [[0 for x in range(1000)] for y in range(1000)]

def parse_input():
  global pipes, matrix

  for line in fileinput.input():
    temp = line.strip().split(" -> ")

  fileinput.close()

def solve():
  global pipes

  collisions = 0

  return collisions

def main():
  parse_input()
  sol = solve()
  print(sol)

main()
