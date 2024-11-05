import sys
import math
import time

sys.set_int_max_str_digits(10000000)

def add(f1, f2): #fraction 1, fraction 2. fraction 1 is mutated
    #print("f1:", f1, "f2:", f2)
    f1[0] *= f2[1]
    f1[0] += (f2[0] * f1[1])
    f1[1] *= f2[1]
    
def simplify_frac(f):
    #print("len(str(f[1]))", len(str(f[1])))
    div = math.gcd(f[0], f[1])
    f[0] //= div 
    f[1] //= div

def brute_force(peter_dice, peter_cap, colin_dice, colin_cap):
    # can solve using brute force, generate all combos of 9 dice, then all combos of 6 dice,
    # find the probabilities of getting a face sum in range [4, 36]
    peter_max = peter_dice * peter_cap
    colin_max = colin_dice * colin_cap
    peter_ways = peter_cap**peter_dice
    colin_ways = colin_cap**colin_dice
    peter = [0 for _ in range(peter_max + 1)]
    colin = [0 for _ in range(colin_max + 1)]
    
    def incrementDice(dice, total, cap):
        for i in range(len(dice)):
            if dice[i] == cap:
                dice[i] = 1
                total -= cap
                total += 1
            else:
                dice[i] += 1 
                total += 1 
                return total
        return -1    
    
    def populate(dice, cap, tally):
        rolls = [1 for _ in range(dice)] # the state of the dice 
        total = dice # total sum of dice faces
        ways = cap**dice
        for _ in range(ways):
            tally[total] += 1 
            total = incrementDice(rolls, total, cap) # mutates dice, updates total
        
    
    # peter
    populate(peter_dice, peter_cap, peter)
    print("peter:", peter)
    
    # colin
    populate(colin_dice, colin_cap, colin)
    print("colin:", colin)
    
    # calculate probability peter beats colin 
    # could use prefix array to make this chunk of the logic O(n) rather than O(n^2)
    ways = peter_cap**peter_dice
    prob = [0, 1]
    for i in range(len(peter)):
        for j in range(0, min(i, len(colin))):
            incr = [peter[i], peter_ways]
            incr[0] *= colin[j]
            incr[1] *= colin_ways
            add(prob, incr)
            
    simplify_frac(prob)
    ans = 1.0 * prob[0] / prob[1]
    ans = round(ans, 7)
    return ans
    

def DP(peter_dice, peter_cap, colin_dice, colin_cap):
    peter_max = peter_dice * peter_cap
    colin_max = colin_dice * colin_cap
    peter_ways = peter_cap**peter_dice
    colin_ways = colin_cap**colin_dice
    peter = [0 for _ in range(peter_max + 1)]
    colin = [0 for _ in range(colin_max + 1)]
    
    def populate(dice, cap, tally): # internal subroutine that actually performs DP up to target
        # tally stores the number of ways to reach i, where i is the target sum
        dp = [[0 for _ in range(dice + 1)] for _ in range(len(tally))]
        # dp[number_of_dice_used][face_sum]
        #min_total = dice # when each dice rolls a 1 
        for i in range(1, len(dp)):
            if 1 <= i and i <= cap:
                dp[i][1] = 1 # one way to make a total of i using once die with face i 
            for j in range(1, cap + 1):
                if i - j < 1:
                    break
                for nd in range(1, len(dp[i - j])): # nd number of dice
                    if nd + 1 <= dice:
                        dp[i][nd + 1] += dp[i - j][nd]
        for i in range(len(dp)):
            tally[i] = dp[i][-1]
        
    populate(peter_dice, peter_cap, peter)
    populate(colin_dice, colin_cap, colin)
    print("peter:", peter)
    print("colin:", colin)
    
    prefix = colin[:]
    for i in range(1, len(prefix)):
        prefix[i] += prefix[i - 1]
    prob = [0, 1]
    for i in range(1, len(peter)):
        j = min(i - 1, len(prefix) - 1)
        incr = [peter[i], peter_ways]
        incr[0] *= prefix[j]
        incr[1] *= colin_ways
        add(prob, incr)
    
    simplify_frac(prob)
    ans = 1.0 * prob[0] / prob[1]
    ans = round(ans, 7)
    return ans


peter_dice = 9
peter_cap = 4
colin_dice = 6 
colin_cap = 6 

start = time.perf_counter()
brute_force_ans = brute_force(peter_dice, peter_cap, colin_dice, colin_cap)
end = time.perf_counter()
print("brute force ans:", brute_force_ans)
print("secs elapsed:", end - start)
print()

start = time.perf_counter()
DP_ans = DP(peter_dice, peter_cap, colin_dice, colin_cap)
end = time.perf_counter()
print("DP ans:", DP_ans)
print("secs elapsed:", end - start)