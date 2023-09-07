from socket import *
servername='localhost'
serverPort=12000
clientsocket=socket(AF_INET,SOCK_DGRAM)
message=input('Input message:')
clientsocket.sendto(message.encode(),(servername,serverPort))
modifiedmessage,serveraddress=clientsocket.recvfrom(2048)
print(modifiedmessage.decode())
clientsocket.close()