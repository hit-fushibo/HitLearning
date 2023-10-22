import socket
import random
import select

PACKET_LOSS_P=0.2

WINDOW_SIZE=8
SEQ_LENGTH=10

MAX_TIME=3

client_socket=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

client_socket.sendto('begin'.encode(),('127.0.0.1',6666))

last_ack = SEQ_LENGTH - 1

data_windows = []

while True:
    readable, writeable, errors = select.select([client_socket, ], [], [], 1)
    if len(readable)>0:
        msg,addr=client_socket.recvfrom(1024)
        if msg.decode()=='end':
            break
        seq=int(msg.decode().split(' ')[0])
        if last_ack==(seq-1)%SEQ_LENGTH:
            if random.random()<PACKET_LOSS_P:
                continue
            retmsg='ACK '+str(seq)
            client_socket.sendto(retmsg.encode(),addr)
            last_ack=seq
            
            if seq not in data_windows:
                data_windows.append(seq)
                print('recv data:',msg.decode().split(' ')[1],' seq=',seq,'accept')
            while len(data_windows)>WINDOW_SIZE:
                data_windows.pop(0)
        else:
            print('recv data:',msg.decode().split(' ')[1],' seq=',seq,'not accept')
            retmsg='ACK '+str(last_ack)
            client_socket.sendto(retmsg.encode(),addr)
                
_=input('end press enter to exit')
client_socket.close()   
    
    
    