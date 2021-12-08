import fileinput

left = list()
right = list()

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
  sum = 0

  for i in range(size):
    segments = dict.fromkeys(["a", "cf", "eg"])
    solution = ""
    
    for word in left[i]:
      length = len(word)

      if(length == 2):
        n_1 = word
        segments["cf"] = word
      elif(length == 3):
        n_7 = word
      elif(length == 4):
        n_4 = word
      elif(length == 7):
        n_8 = word
    
    for symbol in n_7:
      if(symbol not in n_1):
        segments["a"] = symbol
        break
      
    group = n_4 + n_7
    for symbol in n_8:
      if(symbol not in group):
        val = segments["eg"]
        if(val == None):
          segments["eg"] = symbol
        else:
          segments["eg"] = val + symbol
          break
    
    for nbr in right[i]:

      if(length == 2):
        solution += "1"
      elif(length == 3):
        solution += "7"
      elif(length == 4):
        solution += "4"
      elif(length == 7):
        solution += "8"
      elif(length == 5):
        if(string_in_string(segments["eg"], nbr)):
          solution += "2"
        elif(string_in_string(segments["cf"], nbr)):
          solution += "3"
        else:
          solution += "5"
      else:
        if(not string_in_string(segments["eg"], nbr)):
          solution += "9"
        elif(string_in_string(segments["cf"], nbr)):
          solution += "0"
        else:
          solution += "6"
    sum += int(solution)
  
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
