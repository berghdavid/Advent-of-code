import fileinput

def parse_input():
  measurements = list()
  for line in fileinput.input():
    measurements.append(int(line.strip()))
  fileinput.close()
  return measurements

def solve(measurements):
  nbr = 0
  for i in range(len(measurements) - 3):
    if(measurements[i] < measurements[i + 3]):
      nbr += 1
  return nbr

def main():
  measurements = parse_input()
  nbr = solve(measurements)
  print(nbr)

if __name__ == "__main__":
  main()
