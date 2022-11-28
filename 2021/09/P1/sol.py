import fileinput

matrix = list()

def parse_input():
  global matrix

  for line in fileinput.input():
    row = list()

    for i in line.strip():
      row.append(int(i))

    matrix.append(row)
  fileinput.close()

def solve():
  global matrix
  
  low_points = list()
  rows = len(matrix)
  cols = len(matrix[0])
  maxRowIndex = rows - 1
  maxColIndex = cols - 1

  # Start in the middle square
  for row in range(1, rows - 1):
    for col in range(1, cols - 1):
      if(not adj_lower_neighbour(matrix, row, col)):
        low_points.append([row, col, matrix[row][col]])
  #print("Middle", low_points)
  #print("Middle len", len(low_points))
  
  # Check edges
  all_dirs = [(0, 1), (-1, 0), (0, -1), (1, 0)]
  edges = [
    ((1, maxRowIndex - 1), (maxColIndex, cols)), 
    ((0, 1), (1, maxColIndex - 1)), 
    ((1, maxRowIndex - 1), (0, 1)), 
    ((maxRowIndex, rows), (1, maxColIndex - 1))
  ]
  for dir in range(4):
    for y in range(edges[dir][0][0], edges[dir][0][1]):
      for x in range(edges[dir][1][0], edges[dir][1][1]):
        lowest = True
        for test_dir in range(4):
          if(test_dir != dir):
            #print("DIR:", dir)
            #print("TestDir:", test_dir)
            #print("(Y, X):", y, x)
            #print("test (Y, X):", y + all_dirs[test_dir][0], x + all_dirs[test_dir][1])
            if(matrix[y + all_dirs[test_dir][0]][x + all_dirs[test_dir][1]] <= matrix[y][x]):
              lowest = False
              break
        if(lowest):
          low_points.append([y, x, matrix[y][x]])
  #print("edges", low_points)
  #print("edges len", len(low_points))

  # Check corners
  if(matrix[1][0] > matrix[0][0] 
    and matrix[0][1] > matrix[0][0]):
    low_points.append([0, 0, matrix[0][0]])
  if(matrix[maxRowIndex - 1][0] > matrix[maxRowIndex][0] 
    and matrix[maxRowIndex][1] > matrix[maxRowIndex][0]):
    low_points.append([maxRowIndex, 0, matrix[maxRowIndex][0]])
  if(matrix[maxRowIndex - 1][maxColIndex] > matrix[maxRowIndex][maxColIndex] 
    and matrix[maxRowIndex][maxColIndex - 1] > matrix[maxRowIndex][maxColIndex]):
    low_points.append([maxRowIndex, maxColIndex, matrix[maxRowIndex][maxColIndex]])
  if(matrix[0][maxColIndex - 1] > matrix[0][maxColIndex] 
    and matrix[1][maxColIndex] > matrix[0][maxColIndex]):
    low_points.append([0, maxColIndex, matrix[0][maxColIndex]])
  #print("corners", low_points)
  #print("corners len", len(low_points))
  
  sum = len(low_points)
  for p in low_points:
    sum += p[2]

  return sum

def adj_lower_neighbour(matrix, row, col):
  val = matrix[row][col]

  return (
    matrix[row][col + 1] <= val or
    matrix[row - 1][col] <= val or
    matrix[row][col - 1] <= val or
    matrix[row + 1][col] <= val
  )

def main():
  parse_input()
  sol = solve()
  print(sol)

if __name__ == "__main__":
  main()
