import fileinput

nbrs = list()
brds = list()

def parse_input():
  global nbrs, brds

  firstLine = True
  i = 0

  for line in fileinput.input():
    if(firstLine):
      temp = line.strip().split(",")
      nbrs.extend(temp)
      nbrs = [int(i) for i in nbrs]
      firstLine = False
    else:
      row = line.strip().split(" ")
      if(row != ['']):
        row = list(filter(None, row))
        currBox[i] = [int(i) for i in row]
        i += 1
      else:
        if(i != 0):
          brds.append(currBox)
        currBox = [ [ 0 for i in range(5) ] for j in range(5) ]
        i = 0
  brds.append(currBox)
  fileinput.close()

def solve():
  global nbrs, brds

  for nbr in nbrs:
    for brd in brds:
      for row in range(5):
        for col in range(5):
          if(brd[row][col] == nbr):
            brd[row][col] = 100

            rowBingo = True
            for row2 in range(5):
              if(brd[row2][col] != 100):
                rowBingo = False
            
            colBingo = True
            for col2 in range(5):
              if(brd[row][col2] != 100):
                colBingo = False
            
            if(rowBingo or colBingo):
              return sum_unmarked(brd, nbr)
  
  return 0

def sum_unmarked(board, recent_nbr):
  sum = 0

  for row in range(5):
    for col in range(5):
      if(board[row][col] != 100):
        sum += board[row][col]
  return sum * recent_nbr

def main():
  parse_input()
  sol = solve()
  print(sol)

main()
