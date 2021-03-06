import fileinput

pipes = list()
minX = 0
minY = 0
maxX = 0
maxY = 0

def parse_input():
  global pipes, minX, minY, maxX, maxY, matrix

  allX = list()
  allY = list()

  for line in fileinput.input():
    temp = line.strip().split(" -> ")

    pipeFrom = temp[0].split(",")
    pipeFrom = [int(i) for i in pipeFrom]

    pipeTo = temp[1].split(",")
    pipeTo = [int(i) for i in pipeTo]

    allX.append(pipeFrom[0])
    allX.append(pipeTo[0])
    allY.append(pipeFrom[1])
    allY.append(pipeTo[1])

    pipes.append([pipeFrom, pipeTo])


  minX = min(allX)
  maxX = max(allX)
  minY = min(allY)
  maxY = max(allY)
  matrix = [[0 for x in range(maxX + 1)] for y in range(maxY + 1)]

  fileinput.close()

def solve():
  global pipes, matrix

  for pipe in pipes:
    if(pipe[0][0] == pipe[1][0]):
      x = pipe[0][0]
      minY = min([pipe[0][1], pipe[1][1]])
      maxY = max([pipe[0][1], pipe[1][1]])
      for y in range(minY, maxY + 1):
        matrix[y][x] = matrix[y][x] + 1
    elif(pipe[0][1] == pipe[1][1]):
      y = pipe[0][1]
      minX = min([pipe[0][0], pipe[1][0]])
      maxX = max([pipe[0][0], pipe[1][0]])
      for x in range(minX, maxX + 1):
        matrix[y][x] = matrix[y][x] + 1
    else:
      xDiff = pipe[1][0] - pipe[0][0]
      yDiff = pipe[1][1] - pipe[0][1]

      if(xDiff > 0):
        xAdder = 1
      else:
        xAdder = -1
      if(yDiff > 0):
        yAdder = 1
      else:
        yAdder = -1

      x = pipe[0][0]
      y = pipe[0][1]
      for i in range(abs(xDiff) + 1):
        matrix[y][x] = matrix[y][x] + 1
        
        x += xAdder
        y += yAdder

  collisions = 0
  for row in matrix:
    for cell in row:
      if(cell > 1):
        collisions += 1

  return collisions

def printMatrix(matrix):
  for row in matrix:
    print(row)

def main():
  parse_input()
  sol = solve()
  print(sol)

if __name__ == "__main__":
  main()
