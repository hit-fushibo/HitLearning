import sys

careers={}

for career in sys.stdin:
    if career in careers.keys():
        careers[career]=careers[career]+1
    else:
        careers[career]=1

lines=[]
for career in careers.keys():
    line=career+' '+str(int(careers[career]*0.02))+'\n'
    lines.append(line)
for line in lines:
    print(line)