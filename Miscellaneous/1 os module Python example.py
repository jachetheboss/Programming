# -*- coding: utf-8 -*-
"""
Created on Sat Jan  7 13:40:07 2023

@author: james
"""


import os
import sys

print(sys.version) # attribute, a string detailing the version of Python
                   # used. i.e. which compiler/interpreter

print(os.getcwd)
os.chdir("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming")
print(os.getcwd())
# folder = os.listdir(r"C:/Users\james\OneDrive\Desktop\UF Textbooks\Fall 2022\Programming")
folder = os.listdir()

#onsider Current Working Directory(CWD) as a folder

           ## when backslashes are used for file path, make sure to use
           ## Pytnon r"" rawstring, so that the escape character does not
           ## mess things up, but when forward slashes are used,
           ## plain string "" works fine
# folder = os.listdir() # when just bare os.listdir() without saving list
#                       # to variable name, automatically prints to stdout
# # print("folder:", folder)
# for file

# more directories (folders) within current directory may exist.
# if the name ends in .something then it is file, if does not end
# in .something then it is folder (based on naming rules/conventions to allow
# for easy parsing)


# Python syntax is <iterable>.count(<item to count>), iterable can be list, str, tuple,
    # returns integer
# C++ syntax is <my_unordered_hashtable>.count(<key>), returns bool
# C++ also  count(my_vec.begin(), my_vec.end(), <value to count>), returns int
print()
for x in folder:
    is_file = False
    if x.count(".") > 0:
        is_file = True
    if not is_file:
        # print(x)
        # os.chdir(x + "\\")
        # os.chroot()
        # print("hello")
        continue
    num_a = 0
    # Python os module functions to know:
        # os.getcwd()
        # os.chdir(path) path can be entirely new path from the root I think,
                       # or just another folder for just the next depth
        # os.listdir(), without argument it gets content from CWD
        # (current working directory), with argument it gets content from
        # directory specified in argument. When assigned to a variable,
        # does not print to stdout, when called bare without assigning to
        # variable, prints to stdout!
    fin = open(os.getcwd() + "\\" + x, encoding = "    laTin - 1", mode ="r") # this works! # mode
    ####### YOU CAN CHANGE THE ENCODING OF THE FILE THAT IS BEING OPENED, SO THAT IT
    ####### GIVES A TEXTWRAPPER I/O STREAM OF CHARACTERS IN DIFFERENT ENCODINGS!
    
    ########################## WOW! Found something cool while messing around with
    ########################## encoding = "<some encoding>" argument in open() fstream
    ########################## Python method. "latin-1" works, "Latin_1" works, "LATIN-1" works,
    ########################## "      Latin-1" works, "ISO 8859-1" (formal designation for latin-1)
    ########################## works, "ASCII" works, "ascii" works, IN SUMMARY,
    ########################## THERE IS A ROBUST BUILT-IN PARSER THAT ALLOWS FLEXIBILITY
    ########################## IN UPPERCASE, LOWERCASE, LEADING AND TRAILING SPACES, even
    ########################## whitespaces WITHIN the string, near the hypens (some people)
    ########################## have a writing/typing style of putting whitespace around hyphens
    ########################## to make extra room.
    
    # fin = open()
    print(x)
    # if x[-4: ] in [".pdf", "docx", ".jpg", ".JPG"]: # these may contain non-UNICODE?
    #     continue
    S = fin.read()
    for c in S:
        if c == "a":
            num_a += 1
    print(x, "num_a:", num_a)
    fin.close()
    
    
    
    


