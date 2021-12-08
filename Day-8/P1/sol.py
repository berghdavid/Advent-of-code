import fileinput

right = list()

def parse_input():
  global right

  for line in fileinput.input():
    temp = line.strip().split(" | ")

    row = list()
    for x in temp[1].split(" "):
      row.append(x)
    right.append(row)
  
  fileinput.close()

def solve():
  global left

  nbr = 0
  for t in right:
    for s in t:
      l = len(s)
      if(l == 2 or l == 3 or l == 4 or l == 7):
        nbr += 1

  return nbr

def main():
  parse_input()
  sol = solve()
  print(sol)

if __name__ == "__main__":
  main()
