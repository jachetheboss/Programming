cases = int(input().strip())
for case in range(1, cases + 1):
    input()
    P = str(input().strip())
    ### can't just brute force it, O(n^2) time
    ### complexity, will result in TLE for the
    ### second test case
    
    ### find the repeating unit of palindrome
    
    ### what if P was any random string, and not
    ### a palindrome? How can this problem be solved?
    
    ### aba --> ababa
    ### abba --> abbaabba, maybe if original
    ### palindrome has a center char, it can be
    ### re-palindromed after concatenation of a Q
    ### of less than the length of P?
    ### cccc --> ccccc
    
    ### if repeating unit is of length 1, then
    ### add 1.
    
    ### Check if palindrome P is already a complex
    ### palindrome with smaller repeating units!
    
    ### palindromes may be nested, and have many separations
    ### check if palindrome is composed of smaller chunks with
    ### separations
    
    ### ^^ i.e., abcdcbaEabcdcbaEabcdcba
    ### idea of "nested" palindromes