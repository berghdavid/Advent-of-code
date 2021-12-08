import fileinput
import math

crabs = list()
maxIndex = 0
nbrCrabs = 0

def parse_input():
  global crabs, crabPos, maxIndex, nbrCrabs

  for line in fileinput.input():
    temp = line.strip().split(",")
    for x in temp:
      crabs.append(int(x))
  
  nbrCrabs = len(crabs)
  maxIndex = max(crabs)

  crabPos = [0 for x in range(maxIndex + 1)]

  for x in crabs:
    crabPos[x] += 1

  fileinput.close()

def solve():
  global crabPos, maxIndex, nbrCrabs

  sum = 0
  for i in range(maxIndex + 1):
    sum += i * crabPos[i]

  mean1 = math.floor(sum/nbrCrabs)
  mean2 = math.ceil(sum/nbrCrabs)

  # Determine fuel usage
  fuelUsage1 = 0
  fuelUsage2 = 0
  for i in range(maxIndex + 1):
    n1 = abs(i - mean1)
    n2 = abs(i - mean2)
    diff1 = n1 * (n1 + 1)/2
    diff2 = n2 * (n2 + 1)/2
    fuelUsage1 += crabPos[i] * diff1
    fuelUsage2 += crabPos[i] * diff2
  
  return min(fuelUsage1, fuelUsage2)

def main():
  parse_input()
  sol = solve()
  print(sol)

if __name__ == "__main__":
  main()
