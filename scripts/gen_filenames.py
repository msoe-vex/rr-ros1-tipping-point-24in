import os

a = open("filenames.txt", "w")
files = [f for f in os.listdir('.') if os.path.isfile(f)]
for file in files:
    if file.endswith(".json"):
        a.write(file + os.linesep) 
