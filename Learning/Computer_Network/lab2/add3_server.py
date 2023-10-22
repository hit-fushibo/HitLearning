import socket

from util import *

send_data=['1','2','3','4','5','6','7','8','9','10']

server_socket=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server_socket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
server_socket.bind(('127.0.0.1',6666))
        

data_to_send=SendData(send_data)
client_addr=('127.0.0.1',6666)
while True:
    message,clientAddress=server_socket.recvfrom(2048)
    if message.decode()=='begin':
        client_addr=clientAddress
        break
SR_send(server_socket,data_to_send,client_addr)

_=input('send over press enter to exit')
server_socket.close()