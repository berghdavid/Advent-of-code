import fileinput

measurements = list()

def parse_input():
  global measurements
  
  for line in fileinput.input():
    measurements.append(int(line))
  fileinput.close()

def solve():
  global measurements

  nbr = 0
  for i in range(len(measurements) - 1):
    if(measurements[i] < measurements[i + 1]):
      nbr += 1
  return nbr

def main():
  parse_input()
  print(solve())

if __name__ == "__main__":
  main()
