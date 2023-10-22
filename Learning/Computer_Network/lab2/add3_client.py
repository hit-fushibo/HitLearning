import socket
from util import *

client_socket=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

client_socket.sendto('begin'.encode(),('127.0.0.1',6666))

SR_recv(client_socket)
_=input('end press enter to exit')
client_socket.close()