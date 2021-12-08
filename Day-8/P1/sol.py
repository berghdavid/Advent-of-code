import fileinput

left = list()
right = list()
segments = {
  0: ["a", "b", "c", "e", "f", "g"],
  1: ["c", "f"],
  2: ["a", "c", "d", "e", "g"],
  3: ["a", "c", "d", "f", "g"],
  4: ["b", "c", "d", "f"],
  5: ["a", "b", "d", "f", "g"],
  6: ["a", "b", "d", "e", "f", "g"],
  7: ["a", "c", "f"],
  8: ["a", "b", "c", "d", "e", "f", "g"],
  9: ["a", "b", "c", "d", "f", "g"],
  }


def parse_input():
  global left, right

  for line in fileinput.input():
    temp = line.strip().split(" | ")

    row = list()
    for x in temp[0].split(" "):
      row.append(x)
    left.append(row)

    row2 = list()
    for x in temp[1].split(" "):
      row2.append(x)
    right.append(row2)
  
  fileinput.close()

def solve():
  global left, right

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

main()
