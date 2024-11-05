"""
ID: your_id_here
LANG: PYTHON2
TASK: ride
"""
import sys

sys.stderr.write('message')

chars = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]

char_values = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26]

fin = open('ride.in','r')
fout = open('ride.out','w')

a = fin.readline()
b = fin.readline()
inputs = [a,b]

products = []
for x in inputs:
    product = 1
    for y in x:
        if y in chars:
            index = chars.index(y)
            product *= char_values[index]
    products.append(product)


if products[0] % 47 != products[1] % 47:
    fout.write("STAY" + "\n")
    fout.close()
else:
    fout.write("GO" + "\n")
    fout.close()
    
            
            
            