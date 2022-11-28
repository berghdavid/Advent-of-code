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

  finished = 0

  for nbr in nbrs:
    removals = list()
    for brd in brds:
      if(board_bingo(brd, nbr)):
        if(finished == 99):
          return sum_unmarked(brd, nbr)
        else:
          removals.append(brd)
          finished += 1
    for remBrd in removals:
      brds.remove(remBrd)
  
  return 0

def board_bingo(board, nbr):
  for row in range(5):
    for col in range(5):
      if(board[row][col] == nbr):
        board[row][col] = 100

        rowBingo = True
        for row2 in range(5):
          if(board[row2][col] != 100):
            rowBingo = False
            
        colBingo = True
        for col2 in range(5):
          if(board[row][col2] != 100):
            colBingo = False
            
        return rowBingo or colBingo
  return False

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

if __name__ == "__main__":
  main()
