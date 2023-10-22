import socket
from util import *

send_file_path='D:/code/Learning/Computer_Network/lab2/send_data.txt'

server_socket=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server_socket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
server_socket.bind(('127.0.0.1',6666))

client_addr=('127.0.0.1',6666)
while True:
    message,clientAddress=server_socket.recvfrom(2048)
    if message.decode()=='begin':
        client_addr=clientAddress
        break
GBN_send_file(server_socket,send_file_path,client_addr)

_=input('send over press enter to exit')
server_socket.close()