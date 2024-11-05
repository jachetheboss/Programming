# -*- coding: utf-8 -*-
"""
Created on Fri Jan 13 17:51:45 2023

@author: james
"""

WRITE YOUR OWN BIGNUM CLASS FOR C++,
SO THAT I CAN WORK WITH FIXED-PRECISION NUMBERS
OF ARBITRARY SIZE, JUST LIKE IN PYTHON!

1. First, check the type of the numeric variable -
   (int, long, long long), do an if statement
   block to check if result of the operation could
   overflow the maxsize (negative OR positive, check!)
   of the type. If possible overflow, then convert to
   bignum (implemented with vectors).
2. My C++ bignum class should be able to support addition,
   subtraction, multiplication, and division. Hopefully
   it should be able to support large exponentiation using
   square-and-multiply algorithm. Hopefully it should
   also be able to support square root, taking arbitrary
   powers, and logarithms, sines, cosines, tangents.
3. This will be quite an undertaking, and quite interesting.

******* Also, just explore how C++ cmath library, and Python
******* math library implements special math functions, and
******* how they are calculated quickly.

You should back up your computer contents (Documents, Desktop,
C:/users/james) to a flashdrive, or to a cloud drive