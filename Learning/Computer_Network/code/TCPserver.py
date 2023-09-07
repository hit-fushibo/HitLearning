from socket import *
serverport=12000
serversocket=socket(AF_INET,SOCK_STREAM)
serversocket.bind(('',serverport))
serversocket.listen(1)
print('sucess')
while True:
    connectionsocket,addr=serversocket.accept()
    sentence=connectionsocket.recv(1024).decode()
    connectionsocket.send(sentence.upper().encode())
    connectionsocket.close()