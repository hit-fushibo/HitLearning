import socket
import random
import select

#server send:1,2,3,4,5,6,7,8,9,10

#server_send: seq+' '+data  recv:'ACK'+' '+seq


        




send_data=['1','2','3','4','5','6','7','8','9','10']

WINDOW_SIZE=8
SEQ_LENGTH=10

MAX_TIME=3

class SendData():
    def __init__(self,data) -> None:
        self.data=data
        self.postion=0
        self.data_len=len(data)
    def next(self):
        if self.postion<self.data_len:
            a=self.data[self.postion]
            self.postion+=1
            return a
            
        else:
            return None


class Data():
    def __init__(self,msg,seq=0,state=0):
        self.msg=msg
        self.state=state
        self.seq=seq%SEQ_LENGTH
    def get_data(self):
        return str(self.seq)+' '+self.msg
        
        
server_socket=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server_socket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
server_socket.bind(('127.0.0.1',6666))
data_to_send=SendData(send_data)
time=0
seq=0
data_windows=[]

client_addr=('127.0.0.1',6666)
while True:
    message,clientAddress=server_socket.recvfrom(2048)
    if message.decode()=='begin':
        client_addr=clientAddress
        break
    
while True:
    if time>MAX_TIME:#超时
        print('time out resend')
        for data in data_windows:
            data.state=0
    while len(data_windows)<WINDOW_SIZE:
        d=data_to_send.next()
        if not d:
            break
        data=Data(d,seq=seq)
        data_windows.append(data)
        seq+=1
    if not data_windows:
        break
    
    for data in data_windows:
        if not data.state:
            print('send:'+data.get_data())
            server_socket.sendto(data.get_data().encode(),client_addr)
            data.state=1
    
    readable, writeable, errors = select.select([server_socket, ], [], [], 1)
    if len(readable)>0:
        time=0
        
        message,address=server_socket.recvfrom(1024)
        print('ACK:'+message.decode())
        for i in range(len(data_windows)):
            if int(message.decode().split(' ')[1])==data_windows[i].seq:
                print('move')
                data_windows=data_windows[i+1:]
                break
    else:
        time+=1

server_socket.sendto('end'.encode(),client_addr)
_=input('send over press enter to exit')
server_socket.close()

        