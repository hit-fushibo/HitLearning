from socket import *
serverport=12000
serversocket=socket(AF_INET,SOCK_DGRAM)
serversocket.bind(('',serverport))
print('success')
while True:
    message,clientAddress=serversocket.recvfrom(2048)
    modifiedmessage=message.decode().upper()
    serversocket.sendto(modifiedmessage.encode(),clientAddress)