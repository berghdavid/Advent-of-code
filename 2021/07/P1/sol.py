import fileinput
import math

crabs = list()

def parse_input():
  global crabs

  for line in fileinput.input():
    temp = line.strip().split(",")
    for x in temp:
      crabs.append(int(x))
  
  crabs.sort()

  fileinput.close()

def solve():
  global crabs

  median = crabs[math.floor(len(crabs)/2)]
  
  fuelUsage = 0
  for crab in crabs:
    fuelUsage += abs(crab - median)

  return round(fuelUsage)

def main():
  parse_input()
  sol = solve()
  print(sol)

if __name__ == "__main__":
  main()
