def part2():
  ns = []
  with (open("i")) as f:
    ns = f.readlines()
  current_ox = ns.copy()
  current_co = ns.copy()

  def do_alg(l, bit, f):
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

  for i in range(len(ns[0])):
    current_ox = do_alg(
      current_ox, i, lambda zeros, ones: zeros if len(zeros) > len(ones) else ones
    )
    current_co = do_alg(
      current_co, i, lambda zeros, ones: ones if len(zeros) > len(ones) else zeros
    )

  return int(f"0b{current_ox[0]}", 2) * int(f"0b{current_co[0]}", 2)


if __name__ == "__main__":
    print(part2())