#caleb meador meadorjc at gmail.com
#This code injects a signature comment into the first line of a file for 
#sql files.
#building up to adapation for database project formatting
#adapted from http://www.wellho.net/net/search.php4?search=python+path

import os, re, sys
from os.path import join, getsize

#regex object checks that file ends in sql or mysql and is a lab/exercise
filecheck = re.compile(r'(^lab|^e|^final|^exercise|^p).*.[.](sql$|mysql$)', re.IGNORECASE)

for root, dirs, files in os.walk('.'):
  #print(root, "~", dirs, "~", files, "~\n\n")
  for name in files:
    if filecheck.search(name):              #test filename
      filepath = os.path.join(root, name)   #create pathstring
      print('\n\n************************************\n',filepath)
      infile = open(filepath, "r+")
      header = "/*Caleb Meador meadorjc at gmail.com*/\n"
      headercheck = re.compile(r'^[/][*]C', re.IGNORECASE)  #regex header-test
      try:                                                  #unicode error handle
        print(infile.readline())
        infile.seek(0)
      except UnicodeEncodeError:
        print("unprintable character: continuing")
        
      if headercheck.search(infile.readline()) == None: #search for any sig-head
        print("\tNo signature header detected\n\n")
        infile.seek(0)
        text = infile.read()
        # infile.seek(0)      #uncomment these 3 to write a signature
        # infile.write(header)
        # infile.write(text)
        infile.seek(0)
        try:                                                #unicode error handle
          print(infile.readlines(3))
          infile.seek(0)
        except UnicodeEncodeError:
          print("unprintable character: continuing")
          
      else: #if a signature exists, leave it alone
        print("\tSignature header detected\n")
  
  

#execute    
os.walk('.')









# sofar = 0
# headercheck = re.compile(r'^#C', re.IGNORECASE)
# header = "#Caleb Meador meadorjc at gmail.com\n"
# for item in objects:
  # size = os.path.getsize(item)
  # print(item, "\t", size, "\n")
  # if (item != '.git' and item != 'README.md'):
    # file = open(item, "r+")
    # print(file.readline(), "\n")
    # file.seek(0)
    # if headercheck.search(file.readline()) == None:
      # print("\ttrue\n")
      # file.seek(0)
      # text = file.read()
      # file.seek(0)
      # file.write(header)
      # file.write(text)
    # else:
      # print("\tfalse\n")
    # if size > sofar:
    # sofar = size
    # name = item
# print("Largest file is ", name, " at ", str(sofar), " bytes")
# changed = os.path.getmtime(name)
# reform = time.ctime(changed)
