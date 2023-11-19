import matplotlib.pyplot as plt
import numpy as np

T=100
a=np.array([2,4/3,10/3,4])
p=np.array([10,30,35,15])/10**6
w=T
for i in range(4):
    w-=100*p[i]
o=p/a
print(T/(o.sum()+w))

    
