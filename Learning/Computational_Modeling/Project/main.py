import numpy as np

import matplotlib.pyplot as plt
from scipy.integrate import odeint


def func(X,t,rho,phi,beta,epsilon,omega,alpha,theta,gamma_I,gamma_q,d_I,d_q):
    '''
    X=[S,E,I,R,D,Sq,Eq,Iq]
    t=[0,1,2....]
    w=[rho,phi,beta,epsilon,omega,alpha,theta,gamma_I,gamma_q,d_I,d_q]
    
    '''
    a=(1-rho)*phi*beta*(X[2]+epsilon*X[1])*X[0]
    b=rho*phi*beta*(X[2]+epsilon*X[1])*X[0]
    c=rho*(1-phi)*beta*(X[2]+epsilon*X[1])*X[0]
    return [-a-b-c+omega*X[5],\
            a-alpha*X[1],\
            alpha*X[1]-gamma_I*X[2]-d_I*X[2]-theta*X[2],\
            gamma_I*X[2]+gamma_q*X[-1],\
            d_I*X[2]+d_q*X[-1],\
            c-omega*X[5],\
            b-alpha*X[-2],\
            alpha*X[-2]-gamma_q*X[-1]-d_q*X[-1]+theta*X[2]]


# #bad
# T=1
# rho=0.2
# beta=9.08*10**-4
# theta=0.2
# gamma_q=0.2
# d_q=0.7



#average
T=7
rho=0.5
beta=5
theta=0.5
gamma_q=0.5
d_q=0.5




def D_count(T,rho,beta,theta,gamma_q,d_q):
    X0=[10**5,109,12,0,0,0,0,21]
    

    s1=odeint(func,X0,[0,50],args=(rho,0.5,beta/10**5,0.5,1/T,1/5.2,theta,0.1,gamma_q,0.9,d_q,))
    D=s1[-1,4]
    return D

#average
T=7
rho=0.5 #0.1-0.9
beta=5 #0.5-10
theta=0.5 #0.1-0.9
gamma_q=0.5 #0.1-0.9
d_q=1-gamma_q

start=0.1
end=0.9

arange=np.linspace(start,end,100)
D=[]
for gamma_q in arange:
    D.append(D_count(T,rho,beta,theta,gamma_q,d_q)/10**5)

plt.figure()
plt.rc('text', usetex=True)
plt.xlabel('$\\gamma_q$')
plt.ylabel('mortality')
plt.plot(arange,D,'r-',label='D')
plt.show()

