import socket
import random
import select
import _thread
from util import *

#client send:10,9,8,7,6,5,4,3,2,1
send_data=['10','9','8','7','6','5','4','3','2','1']


client_socket=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
data_to_send=SendData(send_data)
client_socket.sendto('begin'.encode(),('127.0.0.1',6666))
GBN_send_and_recv(client_socket,data_to_send,('127.0.0.1',6666))
                
_=input('end press enter to exit')
client_socket.close()

    
    
    