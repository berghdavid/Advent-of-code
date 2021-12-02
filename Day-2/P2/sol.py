import fileinput

dir = list()
pwr = list()
x = 0
depth = 0
aim = 0

def parse_input():
  global dir, pwr
  for line in fileinput.input():
    temp = line.strip().split(" ")
    dir.append(temp[0])
    pwr.append(int(temp[1]))
  fileinput.close()

def solve():
  global x, depth, aim
  for i in range(len(dir)):
    if(dir[i] == "forward"):
      x += pwr[i]
      depth += aim*pwr[i]
    elif(dir[i] == "up"):
      aim -= pwr[i]
    else:
      aim += pwr[i]
  return x*depth

def main():
  parse_input()
  nbr = solve()
  print(nbr)

main()
