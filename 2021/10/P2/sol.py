import fileinput
import math

lines = list()
score_map = {
  ")": 1,
  "]": 2,
  "}": 3,
  ">": 4
}

def parse_input():
  global lines

  for line in fileinput.input():
    lines.append(line.strip())
  fileinput.close()

def solve():
  global lines, score_map

  scores = list()

  for line in lines:
    opening_chars = list()
    incomplete = True

    for sym in line:
      if(eq_opener(sym)):
        opening_chars.append(sym)
      elif(not closes(opening_chars.pop(), sym)):
        incomplete = False
        break
    
    if(incomplete):
      score = 0
      while(opening_chars):
        score *= 5
        score += score_map[equiv_closer(opening_chars.pop())]
      scores.append(score)
  
  scores.sort()
  return scores[math.floor(len(scores)/2)]

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

def equiv_closer(sym):
  if(sym == "{"):
    return "}"
  elif(sym == "<"):
    return ">"
  elif(sym == "("):
    return ")"
  elif(sym == "["):
    return "]"
  else:
    print("ERROR")
    return "AS"

def main():
  parse_input()
  sol = solve()
  print(sol)

if __name__ == "__main__":
  main()
