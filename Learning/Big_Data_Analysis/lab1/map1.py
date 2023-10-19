import sys

for line in sys.stdin:
    line=line.replace('\n','')
    career=line.split('|')[-2]
    print(career)