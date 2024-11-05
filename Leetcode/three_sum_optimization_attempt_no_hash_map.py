import math

class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        solutions = []
        
        negs = []
        pos = []
        zeroes = []
        
        for x in nums:
            if x>0:
                pos.append(x)
            if x<0:
                negs.append(x)
            if x==0:
                zeroes.append(x)
        
        pos.sort()
        negs.sort(reverse = True)
        nonzeroes = [pos,negs]
        
        if len(zeroes) >= 3:
            solutions.append([0,0,0])
            zeroes = [0]
            
        pos_dupes = []
        neg_dupes = []
        ## every 2n index contains dupe value, 2n+1 indices contain
        ## the index of the first instance of the values in the
        ## original pos or negs list
        
        for x in nonzeroes:
            i=0
            while i<len(x)-1:
                j=i+1
                while j<len(x):
                    if x[i] == x[j]:
                        if j+1<len(x):    
                            if x[i] == x[j+1]:
                                j+=1
                                while x[i] == x[j]:
                                    del x[j]
                                if x[j] < 0:
                                    neg_dupes.append(x[j-2])
                                    neg_dupes.append(j-2)
                                else:
                                    pos_dupes.append(x[j-2])
                                    pos_dupes.append(j-2)
                    else:
                        j+=1
                i+=1
                
        
        ## up to one duplicate for each element remains
        ## in the negs and pos lists
        
        negs_to_pos_len_ratio = 1.0*len(negs)/len(pos)
        ## case
        
        i = 0
        while i < len(neg_dupes) - 1:
            guess_location = math.floor(1.0*(neg_dupes[i + 1])/len(negs)*len(pos))
            while 2*neg_dupes[i] + pos[guess_location] < 0 and guess_location + 1 <= len(pos):
                guess_location += 1
            while 2*neg_dupes[i] + pos[guess_location] == 0 and guess_location + 1 <= len(pos):
                guess_location += 1
                solutions.append([neg_dupes[i],neg_dupes[i],pos[guess_location]])
                
            while 2*neg_dupes[i] + pos[guess_location] > 0 and guess_location - 1 >= 0:
                guess_location -= 1
                
            while 2*neg_dupes[i] + pos[guess_location] == 0 and guess_location - 1 <= 0:
                guess_location -= 1
                solutions.append([neg_dupes[i],neg_dupes[i],pos[guess_location]])
            
            i += 2
            
            
        i = 0
        while i < len(pos_dupes) - 1:
            guess_location = math.floor(1.0*(pos_dupes[i + 1])/len(pos)*len(negs))
            while 2*pos_dupes[i] + negs[guess_location] < 0 and guess_location - 1 >= 0:
                guess_location -= 1
            while 2*pos_dupes[i] + negs[guess_location] == 0 and guess_location - 1 >= len(pos):
                guess_location -= 1
                solutions.append([pos_dupes[i],pos_dupes[i],negs[guess_location]])
                
            while 2*pos_dupes[i] + negs[guess_location] > 0 and guess_location + 1 <= len(neg_dupes):
                guess_location += 1
                
            while 2*pos_dupes[i] + negs[guess_location] == 0 and guess_location + 1 <= 0:
                guess_location += 1
                solutions.append([pos_dupes[i],pos_dupes[i],negs[guess_location]])
            
            i += 2            
            
            
        ## as of now, the x,x,-2x and -x,-x,2x cases have been found.
        
        
        i = 0
        while i < len(neg_dupes) - 1:
            del negs[neg_dupes[i+1]]
            i += 2
            
        
        i = 0
        while i < len(pos_dupes) - 1:
            del pos[pos_dupes[i+1]]
            i += 2
            
        ## as of now, there are no duplicates in negs and pos lists
        
        #############################
        #############################
        #############################
        # the cases that are left are: 
        # x,-x,0 and x,y,-z and -x,-y,z
        # be sure to use the neg/pos list length
        # ratios to best effect, know where to start searching
            
        return solutions
                        
                            
                            
                        