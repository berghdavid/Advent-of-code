matrix = list()
current_ox = list()
current_co = list()

def parse_input():
  global matrix, current_ox, current_co
  with (open("i")) as f:
    matrix = f.readlines()
  
  current_ox = matrix.copy()
  current_co = matrix.copy()

def alg(l, bit, f):
  if len(l) == 1:
    return l
  zeros = []
  ones = []
  for n in l:
    if n[bit] == "0":
      zeros.append(n)
    else:
      ones.append(n)

  return f(zeros, ones)

def solve():
  global matrix, current_ox, current_co
  
  for i in range(len(matrix[0])):
    current_ox = alg(
      current_ox, i, lambda zeros, ones: zeros if len(zeros) > len(ones) else ones
    )
    current_co = alg(
      current_co, i, lambda zeros, ones: ones if len(zeros) > len(ones) else zeros
    )
  return int(f"0b{current_ox[0]}", 2) * int(f"0b{current_co[0]}", 2)

def main():
  parse_input()
  print(solve())

main()