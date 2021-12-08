import fileinput

left = list()
right = list()
segments = {
  1: [          "c",           "f"     ], #LEN: 2
  7: ["a",      "c",           "f"     ], #LEN: 3
  4: [     "b", "c", "d",      "f"     ], #LEN: 4
  8: ["a", "b", "c", "d", "e", "f", "g"], #LEN: 7

  2: ["a",      "c", "d", "e",      "g"], #LEN: 5
  3: ["a",      "c", "d",      "f", "g"], #LEN: 5
  5: ["a", "b",      "d",      "f", "g"], #LEN: 5

  0: ["a", "b", "c",      "e", "f", "g"], #LEN: 6
  6: ["a", "b",      "d", "e", "f", "g"], #LEN: 6
  9: ["a", "b", "c", "d",      "f", "g"], #LEN: 6
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
  size = len(left)
  solutions = ["" for x in range(size)]
  segments = [dict.fromkeys(["a", "cf", "eg"]) for x in range(size)]

  for i in range(size):
    for word in left[i]:
      l = len(word)

      if(l == 2):
        n_1 = word
        segments[i]["cf"] = word
      elif(l == 3):
        n_7 = word
      elif(l == 4):
        n_4 = word
      elif(l == 7):
        n_8 = word
    
    for symbol in n_7:
      if(symbol not in n_1):
        segments[i]["a"] = symbol
        break
      
    group = n_4 + n_7
    for symbol in n_8:
      if(symbol not in group):
        val = segments[i]["eg"]
        if(val == None):
          segments[i]["eg"] = symbol
        else:
          segments[i]["eg"] = val + symbol
          break

  for i in range(size):
    row = right[i]
    for nbr in row:
      length = len(nbr)

      if(length == 2):
        solutions[i] += "1"
      elif(length == 3):
        solutions[i] += "7"
      elif(length == 4):
        solutions[i] += "4"
      elif(length == 7):
        solutions[i] = "8"
      elif(length == 5):
        if(string_in_string(segments[i]["eg"], nbr)):
          solutions[i] += "2"
        elif(string_in_string(segments[i]["cf"], nbr)):
          solutions[i] += "3"
        else:
          solutions[i] += "5"
      else:
        if(not string_in_string(segments[i]["eg"], nbr)):
          solutions[i] += "9"
        elif(string_in_string(segments[i]["cf"], nbr)):
          solutions[i] += "0"
        else:
          solutions[i] += "6"

  sum = 0
  for nbr in solutions:
    sum += int(nbr)

  return sum

def string_in_string(s1, s2):
  for symbol in s1:
    if(symbol not in s2):
      return False
  return True

def main():
  parse_input()
  sol = solve()
  print(sol)

main()
