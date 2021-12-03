import fileinput

w = 12
h = 1000
gamma = ""
epsilon = ""
matrix = [[0 for x in range(w)] for y in range(h)]

def parse_input():
  global matrix
  i = 0
  for line in fileinput.input():
    j = 0
    temp = line.strip()
    for bit in temp:
      matrix[i][j] = int(bit)
      j += 1
    i += 1
  fileinput.close()

def solve():
  global w, h, matrix, gamma, epsilon
  for j in range (w):
    sum = 0
    for i in range(h):
      sum += matrix[i][j]
    if(sum > h/2):
      gamma += '1'
      epsilon += '0'
    else:
      gamma += '0'
      epsilon += '1'
  
  dGamma = int(gamma, 2)
  dEpsilon = int(epsilon, 2)
  return dGamma * dEpsilon

def main():
  parse_input()
  sol = solve()
  print(sol)

main()
