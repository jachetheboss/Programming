# -*- coding: utf-8 -*-
"""
Created on Sun Aug 28 18:38:43 2022

@author: james
"""
# might as well use tuple sort to do the tiebreak shit lmao

# 1. High Card: Highest value card.
# 2. One Pair: Two cards of the same value.
# 3. Two Pairs: Two different pairs.
# 4. Three of a Kind: Three cards of the same value.
# 5. Straight: All cards are consecutive values.
# 6. Flush: All cards of the same suit.
# 7. Full House: Three of a kind and a pair.
# 8. Four of a Kind: Four cards of the same value.
# 9. Straight Flush: All cards are consecutive values of same suit.
# 10. Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.

di = {"T": 10, "J": 11, "Q": 12, "K": 13, "A": 14}
digits = "23456789"
for i in range(len(digits)):
    di.update({digits[i]: i + 2})
# maps the string representation of card rank to int value, 2 --> 14 inclusive

    
fin = open("C:/Users/james/Downloads/p054_poker.txt", "r")
p1_wins = 0
for _ in range(1000):
    
    cards = fin.readline().strip().split()
    print("p1_wins", p1_wins)
    print("cards", cards)
    p1 = cards[0: 5]
    p2 = cards[5: 10]
    v1 = []
    v2 = []
    for x in p1:
        v1.append(di[x[0]])
    for x in p2:
        v2.append(di[x[0]])
    v1.sort() # stores ranks, deal with suits later
    v2.sort()
    map1 = {} # key-value pair. key is card rank, value is frequency
    map2 = {}
    for x in v1:
        if x not in map1:
            map1.update({x: 1})
        else:
            vals = map1[x]
            vals += 1
            map1.update({x: vals})
    for x in v2:
        if x not in map2:
            map2.update({x: 1})
        else:
            vals = map2[x]
            vals += 1
            map2.update({x: vals})
    freq1 = []
    freq2 = []
    for x in map1:
        freq1.append(map1[x])
    for x in map2:
        freq2.append(map2[x])
    freq1.sort(reverse = True)
    freq2.sort(reverse = True) # sorts rank frequencies from high to low
    # print("freq1", freq1)
    
    status1 = 0 # initializes variable storing quality of hand player possesses
    status2 = 0 # 10 exact hands by poker definition are listed above
    
    
    ### checking elements at index 0 and index 1 works since freq1
    ### and freq2 are guaranteed to have lengths of at least two, since
    ### there can be no more than 4 cards of the same rank, and there
    ### are five cards total, by pigeonhole principle there has to be
    ### at least two distinct ranks in a single poker hand with one deck.
    
    
    print("freq1[0]", freq1[0])
    
    
    if freq1[0] == 4: # four of a kind
        status1 = 8
    if freq2[0] == 4:
        status2 = 8
    if freq1[0] == 3:
        if freq1[1] == 2: # full house
            status1 = 7
        else:             # three of a kind
            status1 = 4
    if freq2[0] == 3:
        if freq2[1] == 2:
            status2 = 7
        else:
            status2 = 4
    if freq1[0] == 2:
        if freq1[1] == 2: # two pairs
            status1 = 3
        else:             # pair
            status1 = 2
    if freq2[0] == 2:
        if freq2[1] == 2:
            status2 = 3
        else:
            status2 = 2
    if freq1[0] == 1:
        # v1 already sorted
        # sorts ranks from smallest to largest, check if 5 ranks
        # are consecutive to determine if straight. if not, high
        # card
        straight_bool = True
        for i in range(len(v1)):
            if v1[i] - v1[0] != i:
                straight_bool = False
                break
        if straight_bool == True: # straight
            status1 = 5
        else:                     # high card
            status1 = 1
    if freq2[0] == 1:
        # v2 has already been sorted
        straight_bool = True
        for i in range(len(v2)):
            if v2[i] - v2[0] != i:
                straight_bool = False
                break
        if straight_bool == True: # straight
            status2 = 5
        else:                     # high card
            status2 = 1
    
    # now check if flush. flush beats out 1-5, being 6 in poker hand quality
       
    if p1[0] == p1[1] == p1[2] == p1[3] == p1[4]:
        if status1 == 5: # if already straight (since we checked for that first)
            if v1[0] == 10:
                status1 = 10 # royal flush, lowest rank is 10!
            else:
                status1 = 9 # straight flush, but not royal
        else:
            status1 = max(status1, 6) # four of a kind and full house still
                                      # beats flush
    if p2[0] == p2[1] == p2[2] == p2[3] == p2[4]:
        if status2 == 5: # if already straight (since we checked for that first)
            if v2[0] == 10:
                status2 = 10 # royal flush, lowest rank is 10!
            else:
                status2 = 9 # straight flush, but not royal
        else:
            status2 = max(status2, 6) # four of a kind and full house still
                                      # beats flush
                                      
    # print("status1", status1)
    # print("status2", status2)
    
    if status1 > status2:
        p1_wins += 1
    elif status1 < status2:
        continue
    elif status1 == status2:
        if status1 == 1: # comparing high cards
            for i in reversed(range(len(v1))):
                if v1[i] > v2[i]: # p1 has higher card
                    p1_wins += 1
                    break
                elif v1[i] == v2[i]:
                    continue
                elif v1[i] < v2[i]: # p1 has lower card, p1 loses
                    break
        elif status1 == 2: # comparing better pair/remaining hand
            d1 = 0
            d2 = 0
            temp1 = []
            temp2 = []
            i = 0
            while i < len(v1) - 1:
                if v1[i] != v1[i + 1]:
                    temp1.append(v1[i])
                    i += 1
                elif v1[i] == v1[i + 1]:
                    d1 = v1[i]
                    i += 2
            if v1[-1] != v1[-2]:
                temp1.append(v1[-1])
            i = 0
            while i < len(v2) - 1:
                if v2[i] != v2[i + 1]:
                    temp2.append(v2[i])
                    i += 1
                elif v2[i] == v2[i + 1]:
                    d2 = v2[i]
                    i += 2
            if v2[-1] != v2[-2]:
                temp2.append(v2[-1])
            i = 0 ### do I need this to prevent fuckups from
            # bad scope analysis when using the same variable?
            if d1 > d2:
                p1_wins += 1
            elif d1 == d2:
                temp1.sort()
                temp2.sort()
                for i in reversed(range(len(temp1))):
                    if temp1[i] > temp2[i]: # p1 has higher card
                        p1_wins += 1
                        break
                    elif temp1[i] == temp2[i]:
                        continue
                    elif temp1[i] < temp2[i]: # p1 has lower card, p1 loses
                        break
        elif status1 == 3: # tie-break for two pairs
            d1 = [] # dynamic array instead of int, since
            # two pairs
            d2 = []
            single1 = 0 # the only single rank in the hand
            single2 = 0
            i = 0
            while i < len(v1) - 1:
                if v1[i] != v1[i + 1]:
                    single1 = v1[i]
                    i += 1
                elif v1[i] == v1[i + 1]:
                    d1.append(v1[i])
                    i += 2     
            if v1[-1] != v1[-2]:
                single1 = v1[-1]
            i = 0
            while i < len(v2) - 1:
                if v2[i] != v2[i + 1]:
                    single2 = v2[i]
                    i += 1
                elif v2[i] == v2[i + 1]:
                    d2.append(v2[i])
                    i += 2
            if v2[-1] != v2[-2]:
                single2 = v2[-1]
            d1.sort()
            d2.sort()
            if d1[1] > d2[1]:
                p1_wins += 1
            elif d1[1] == d2[1]:
                if d1[0] > d2[0]:
                    p1_wins += 1
                elif d1[0] == d2[0]:
                    if single1 > single2:
                        p1_wins += 1
                        
        #######
        ####### PROBABLY BUGS WITH THE ARRAY INDEXING, COULD
        ####### LEAD TO INDEX ERROR, if there's pair, triple, quad
        ####### are all the singles accounted for, etc, are all
        ####### 5 cards accounted for, figure it out after dinner
                        
                        
        elif status1 == 4: # tiebreak for three of a kind
            t1 = 0
            t2 = 0
            temp1 = [] # singles
            temp2 = []
            i = 0
            while i < len(v1) - 2:
                if v1[i] != v1[i + 1]:
                    temp1.append(v1[i])
                    i += 1
                elif v1[i] == v1[i + 1]:
                    t1 = v1[i]
                    i += 3
            if v1[-1] != v1[-2] and v1[-2] != v1[-3]:
                temp1.append(v1[-1])
                temp1.append(v1[-2])
            elif v1[-1] != v1[-2]:
                temp1.append(v1[-1])
            i = 0
            while i < len(v2) - 1:
                if v2[i] != v2[i + 1]:
                    temp2.append(v2[i])
                    i += 1
                elif v2[i] == v2[i + 1]:
                    t2 = v2[i]
                    i += 3
            if v2[-1] != v2[-2] and v2[-2] != v2[-3]:
                temp2.append(v2[-1])
                temp2.append(v2[-2])
            elif v2[-1] != v2[-2]:
                temp1.append(v2[-1])
            i = 0 ### do I need this to prevent fuckups from
            # bad scope analysis when using the same variable?
            if t1 > t2:
                p1_wins += 1
            elif t1 == t2:
                temp1.sort()
                temp2.sort()
                for i in reversed(range(len(temp1))):
                    if temp1[i] > temp2[i]: # p1 has higher card
                        p1_wins += 1
                        break
                    elif temp1[i] == temp2[i]:
                        continue
                    elif temp1[i] < temp2[i]: # p1 has lower card, p1 loses
                        break
        elif status1 == 5:
            if v1[0] > v2[0]:
                p1_wins += 1
        elif status1 == 6:
            for i in reversed(range(len(v1))):
                if v1[i] > v2[i]: # p1 has higher card
                    p1_wins += 1
                    break
                elif v1[i] == v2[i]:
                    continue
                elif v1[i] < v2[i]: # p1 has lower card, p1 loses
                    break
        elif status1 == 7:
            t1 = 0
            t2 = 0
            d1 = 0
            d2 = 0
            i = 0
            while i < len(v1) - 2:
                if v1[i] == v1[i + 1] and v1[i] == v1[i + 2]:
                    t1 = v1[i]
                    d1 = v1[-1]
                    i += 3
                elif v1[i] == v1[i + 1]:
                    d1 = v1[i]
                    i += 2
            i = 0
            while i < len(v2) - 2:
                if v2[i] == v2[i + 1] and v2[i] == v2[i + 2]:
                    t2 = v2[i]
                    d2 = v2[-1]
                    i += 3
                elif v2[i] == v2[i + 1]:
                    d2 = v2[i]
                    i += 2
                    
            i = 0 ### do I need this to prevent fuckups from
            # bad scope analysis when using the same variable?
            if t1 > t2:
                p1_wins += 1
            elif t1 == t2:
                temp1.sort()
                temp2.sort()
                for i in reversed(range(len(temp1))):
                    if temp1[i] > temp2[i]: # p1 has higher card
                        p1_wins += 1
                        break
                    elif temp1[i] == temp2[i]:
                        continue
                    elif temp1[i] < temp2[i]: # p1 has lower card, p1 loses
                        break
        elif status1 == 8:
            q1 = 0
            q2 = 0
            single1 = 0
            single2 = 0
            if v1[0] == v1[1]:
                q1 = v1[0]
                single1 = v1[-1]
            else:
                single1 = v1[0]
                q1 = v1[-1]
            if v2[0] == v2[1]:
                q2 = v2[0]
                single2 = v2[-1]
            else:
                single2 = v2[0]
                q2 = v2[-1]
            if q1 > q2:
                p1_wins += 1
            elif q1 == q2:
                if single1 > single2:
                    p1_wins += 1
        elif status1 == 9:
            if v1[0] > v1[1]:
                p1_wins += 1
        
print("p1_wins", p1_wins)
            
                
            
                
                    
            
            
            
            
            
            
            
            