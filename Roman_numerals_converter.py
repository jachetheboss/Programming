class Solution(object):
    def romanToInt(self, s):
        """    
        :type s: str
        :rtype: int
        """
        sum = 0
        
        i = 0
        
        while i < len(s):
    
            if i < len(s):
                
                if s[i] == "M":
                    
                    sum += 1000
                    i += 1
                    
            if i < len(s):
                    
                if s[i] == "D":
                    
                    sum += 500
                    i += 1
                    
            if i < len(s):
                
                if s[i] == "L":
                    
                    sum += 50
                    i += 1
                    
            if i < len(s):
                
                if s[i] == "V":
                    
                    sum += 5
                    i += 1
                    
            if i < len(s):
                    
                if s[i] == "C":
                    
                    if i + 1 < len(s):
                
                        if s[i+1] == "D":
                            sum += 400
                            i += 2
                            
                        elif s[i+1] == "M":            
                            sum += 900
                            i += 2
                        
                        else:
                            sum += 100
                            i += 1
                            
                    else:
                        sum += 100
                        i += 1
                            
            if i < len(s):
                    
                    if s[i] == "X":
                        
                        if i + 1 < len(s):
                
                            if s[i+1] == "L":
                                sum += 40
                                i += 2    
                                
                            elif s[i+1] == "C":
                                sum += 90
                                i += 2
                                
                            else:
                                sum += 10
                                i += 1
                                
                        else:
                            sum += 10
                            i += 1
                                
            if i < len(s):
                     
                    if s[i] == "I":
                        
                        if i + 1 < len(s):
                
                            if s[i+1] == "V":
                                sum += 4
                                i += 2    
                                
                            elif s[i+1] == "X":
                                sum += 9
                                i += 2
                                
                            else:
                                sum += 1
                                i += 1        
                                
                        else:
                            sum += 1
                            i += 1    
        return sum                    

djokovic = Solution()
print(djokovic.romanToInt("III"))
                    
                
                        
                        
                        
                        
                    
                        
            
            
            