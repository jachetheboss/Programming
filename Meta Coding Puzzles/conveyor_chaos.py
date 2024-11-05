from typing import List
# Write any import statements here

def getMinExpectedHorizontalTravelDistance(N: int, H: List[int], A: List[int], B: List[int]) -> float:
  # Write your code here
  # can we do some Monte Carlo simulation or some shit
  # thinking top down, cases: immediately hits the ground when dropped, easy base case branch,
  # if hits "top" belt, then may slide to secondary belt (also have choice of slide right or slide left)
  # then secondary belt may slide to the third level belt, etc... until reach a "bottom level" belt, which will directly fall onto the ground (no lower level belts below it)
  # so instead of top-down, can maybe think about bottom-up after determine which are the "bottom level"
  # belts via topological sorting, then DP?
  return 0.0
