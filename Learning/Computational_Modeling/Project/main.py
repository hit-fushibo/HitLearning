import numpy as np
import os
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

def D_count(T,rho,beta,theta,gamma_q,d_q,X=None):
    if not X:
        X0=[10**5,109,12,0,0,0,0,21]
    else:
        X0=X
    

    s1=odeint(func,X0,[0,50],args=(rho,0.5,beta/10**5,0.5,1/T,1/5.2,theta,0.1,gamma_q,0.9,d_q,))
    D=s1[-1,4]
    return D


def T(X,cases):
    save_path='./images/'+cases
    #average
    T=7
    rho=0.5 #0.1-0.9
    beta=5 #0.5-10
    theta=0.9 #0.1-0.9
    gamma_q=0.5 #0.1-0.9
    d_q=1-gamma_q
    
    #T
    arange=[i+1 for i in range(14)]
    
    D=[]
    for T in arange:
        D.append(D_count(T,rho,beta,theta,gamma_q,d_q,X)/10**5)

    plt.figure()
    plt.rc('text', usetex=True)
    plt.xlabel('$T$')
    plt.ylabel('mortality')
    plt.plot(arange,D,'r-')
    plt.savefig(save_path+'/T.png')

def rho(X,cases):
    save_path='./images/'+cases
    #average
    T=7
    rho=0.5 #0.1-0.9
    beta=5 #0.5-10
    theta=0.9 #0.1-0.9
    gamma_q=0.5 #0.1-0.9
    d_q=1-gamma_q
    
    #rho
    start=0.1
    end=0.9
    arange=np.linspace(start,end,100)
    
    D=[]
    for rho in arange:
        D.append(D_count(T,rho,beta,theta,gamma_q,d_q,X)/10**5)

    plt.figure()
    plt.rc('text', usetex=True)
    plt.xlabel('$\\rho$')
    plt.ylabel('mortality')
    plt.plot(arange,D,'r-')
    plt.savefig(save_path+'/rho.png')
    
    
def beta(X,cases):
    save_path='./images/'+cases
    #average
    T=7
    rho=0.5 #0.1-0.9
    beta=5 #0.5-10
    theta=0.9 #0.1-0.9
    gamma_q=0.5 #0.1-0.9
    d_q=1-gamma_q
    
    #beta
    start=0.5
    end=10
    arange=np.linspace(start,end,100)
    
    D=[]
    for beta in arange:
        D.append(D_count(T,rho,beta,theta,gamma_q,d_q,X)/10**5)

    plt.figure()
    plt.rc('text', usetex=True)
    plt.xlabel('$\\beta$')
    plt.ylabel('mortality')
    plt.plot(arange,D,'r-',label='D')
    plt.savefig(save_path+'/beta.png')
    
def theta(X,cases):
    save_path='./images/'+cases
    #average
    T=7
    rho=0.5 #0.1-0.9
    beta=5 #0.5-10
    theta=0.9 #0.1-0.9
    gamma_q=0.5 #0.1-0.9
    d_q=1-gamma_q
    
    #theta
    start=0.1
    end=0.9
    arange=np.linspace(start,end,100)
    
    D=[]
    for theta in arange:
        D.append(D_count(T,rho,beta,theta,gamma_q,d_q,X)/10**5)

    plt.figure()
    plt.rc('text', usetex=True)
    plt.xlabel('$\\theta$')
    plt.ylabel('mortality')
    plt.plot(arange,D,'r-',label='D')
    plt.savefig(save_path+'/theta.png')
    
def gamma_q(X,cases):
    save_path='./images/'+cases
    #average
    T=7
    rho=0.5 #0.1-0.9
    beta=5 #0.5-10
    theta=0.9 #0.1-0.9
    gamma_q=0.5 #0.1-0.9
    d_q=1-gamma_q
    
    
    #gamma_q
    start=0.1
    end=0.9
    arange=np.linspace(start,end,100)
    
    D=[]
    for gamma_q in arange:
        d_q=1-gamma_q
        D.append(D_count(T,rho,beta,theta,gamma_q,d_q,X)/10**5)

    plt.figure()
    plt.rc('text', usetex=True)
    plt.xlabel('$\\gamma_q$')
    plt.ylabel('mortality')
    plt.plot(arange,D,'r-',label='D')
    plt.savefig(save_path+'/gamma_q.png')
    
    
def run(X=None,cases='defult'):
    if  not os.path.exists('./images/'):
        os.mkdir('images/')
    if  not os.path.exists('./images/'+cases):
        os.mkdir('./images/'+cases)

    T(X,cases)
    rho(X,cases)
    beta(X,cases)
    theta(X,cases)
    gamma_q(X,cases)    
    
    
    
    
'''
用法：
X：初始值
cases：情况名，也就是保存到哪个文件夹下

根据不同情况参数设置表修改X值以及对应cases情况名，直接跑就行(跑的时候注意终端路径，相对路径相对于终端当前路径)
保存路径：./image/cases


'''
if __name__=='__main__':
    #X=[S,E,I,R,D,Sq,Eq,Iq]
    
    X=[4500,10000,15000,500,40000,5000,10000,15000]
    
    cases='2'
    
    run(X,cases)