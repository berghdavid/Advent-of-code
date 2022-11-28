import fileinput

matrix = list()
maxRowIndex = 0
maxColIndex = 0
all_dirs = [(0, 1), (-1, 0), (0, -1), (1, 0)]

def parse_input():
  global matrix

  for line in fileinput.input():
    row = list()

    for i in line.strip():
      row.append(int(i))

    matrix.append(row)
  fileinput.close()

def solve():
  global matrix, maxRowIndex, maxColIndex, all_dirs
  
  low_points = list()
  biggest_basins = list()
  rows = len(matrix)
  cols = len(matrix[0])
  maxRowIndex = rows - 1
  maxColIndex = cols - 1

  # Start in the middle squares
  for row in range(1, rows - 1):
    for col in range(1, cols - 1):
      if(not adj_lower_neighbour(matrix, row, col)):
        low_points.append([row, col, matrix[row][col]])
  
  # Check edges
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
            if(matrix[y + all_dirs[test_dir][0]][x + all_dirs[test_dir][1]] <= matrix[y][x]):
              lowest = False
              break
        if(lowest):
          low_points.append([y, x, matrix[y][x]])

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
  
  for p in low_points:
    basin = basin_size([(p[0], p[1])], p[0], p[1])
    if(len(biggest_basins) < 3):
      biggest_basins.append(len(basin))
      biggest_basins = sorted(biggest_basins)
    elif(len(basin) > min(biggest_basins)):
      biggest_basins.pop(0)
      biggest_basins.append(len(basin))
      biggest_basins = sorted(biggest_basins)
    print(biggest_basins)

  ans = biggest_basins[0] * biggest_basins[1] * biggest_basins[2]

  return ans

def basin_size(visited, row, col):
  global matrix, all_dirs, maxRowIndex, maxColIndex

  test_squares = list()
  for i in range(4):
    y = row + all_dirs[i][0]
    x = col + all_dirs[i][1]
    if((y, x) not in visited and y >= 0 and y <= maxRowIndex 
      and x >= 0 and x <= maxColIndex and matrix[y][x] != 9):
      test_squares.append((y, x))
      visited.append((y, x))
  for sq in test_squares:
    basin_size(visited, sq[0], sq[1])
  return visited

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
