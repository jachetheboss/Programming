import math
import time

def main():

    # see if there is application for a binary search
    # in a segmented sieve?

    # segmented sieve

    # can implement special case for first segment.
    # 1st seg is only seg containing primes that contain
    # multiples of themselves IN THE SAME SEGMENT!
    # starting from 2nd seg, primes in seg have smallest multiple
    # in a later seg. So first seg is the only seg where we must
    # mark multiples in the same seg.

    # for each segment starting with 2nd, remember to update next_mult
    # for each prime!
    
    range_size = int(input("Enter range size: "))
    seg_size = 1000
    while seg_size <= range_size:

        begin = time.time()

        primes = [] # (prime, next multiple)
        
        block = [True for _ in range(seg_size)]
        block[0] = False
        block[1] = False

        # 1st segment special case
        bound = int(math.floor(math.sqrt(seg_size)))
        for k in range(2, bound + 1):
            if block[k] is True:
                for j in range(2 * k, len(block), k):
                    block[j] = False

        for k in range(2, len(block)):
            if block[k] is True:
                next_seg_mult = k * ((seg_size - 1) // k + 1)
                primes.append((k, next_seg_mult))

        for left in range(seg_size, range_size, seg_size):

            # reset to all prime
            block = [True for _ in range(seg_size)]

            right = left + seg_size - 1
            for idx in range(len(primes)):
                gap = primes[idx][0] # val of prime is gap
                next_mult = primes[idx][1]
                if left <= next_mult <= right:
                    i = next_mult - left
                    for j in range(i, seg_size, gap):
                        block[j] = False
                primes[idx] = (gap, gap * (right // gap + 1))
                    

            for i in range(seg_size):
                if block[i] is True:
                    primes.append((left + i, 2 * (left + i)))

        
        end = time.time()
        print("len(primes):", len(primes))
        print("seg_size:", seg_size)
        print("elapsed:", end - begin, "sec")
        print()
        
        seg_size *= 10
    
    
if __name__ == "__main__":
    main()
