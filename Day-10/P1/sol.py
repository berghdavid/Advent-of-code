import fileinput
from collections import deque
from os import error 

lines = list()
score = {
  ")": 3,
  "]": 57,
  "}": 1197,
  ">": 25137
}

def parse_input():
  global lines

  for line in fileinput.input():
    lines.append(line.strip())
  fileinput.close()

def solve():
  global lines, score

  opening_chars = list()
  errors = list()

  for line in lines:
    for sym in line:
      if(eq_opener(sym)):
        opening_chars.append(sym)
      elif(not closes(opening_chars.pop(), sym)):
        errors.append(score[sym])
        break
  
  return sum(errors)

def eq_opener(sym):
  return (sym == "{" or sym == "<" or sym == "(" or sym == "[")

def closes(sym1, sym2):
  if(sym1 == "{"):
    return sym2 == "}"
  elif(sym1 == "<"):
    return sym2 == ">"
  elif(sym1 == "("):
    return sym2 == ")"
  elif(sym1 == "["):
    return sym2 == "]"
  else:
    print("ERROR")
    return False

def main():
  parse_input()
  sol = solve()
  print(sol)

if __name__ == "__main__":
  main()
