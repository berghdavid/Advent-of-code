import fileinput

fish = [0 for x in range(9)]

def parse_input():
  global fish

  for line in fileinput.input():
    temp = line.strip().split(",")
    for x in temp:
      fish[int(x)] += 1
  fileinput.close()

def solve():
  global fish

  for i in range(256):
    newFish = [0 for x in range(9)]

    for f in range(9):
      if(f == 0):
        newFish[6] = fish[0]
        newFish[8] = fish[0]
      else:
        newFish[f-1] += fish[f]
    
    for f in range(9):
      fish[f] = newFish[f]

  return sum(fish)

def main():
  parse_input()
  sol = solve()
  print(sol)

main()
