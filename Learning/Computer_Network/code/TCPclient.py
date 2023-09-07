from socket import *
servername='localhost'
serverport=12000
clientsocket=socket(AF_INET,SOCK_STREAM)
clientsocket.connect((servername,serverport))
sentence=input('input:')
clientsocket.send(sentence.encode())
modifiedsentence=clientsocket.recv(1024)
print('from server:',modifiedsentence)
clientsocket.close()
