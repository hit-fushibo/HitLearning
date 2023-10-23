import socket
import random
import select

WINDOW_SIZE=4
SEQ_LENGTH=10

MAX_TIME=3

PACKET_LOSS_P=0.2#不丢包

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


    
def GBN_recv_msg(client_recv_socket):
    last_ack = SEQ_LENGTH - 1
    data_windows = []
    while True:
        readable, writeable, errors = select.select([client_recv_socket, ], [], [], 1)
        if len(readable)>0:
            msg,addr=client_recv_socket.recvfrom(1024)
            if msg.decode()=='end':
                break
            seq=int(msg.decode().split(' ')[0])
            if last_ack==(seq-1)%SEQ_LENGTH:
                if random.random()<PACKET_LOSS_P:
                    continue
                retmsg='ACK '+str(seq)
                client_recv_socket.sendto(retmsg.encode(),addr)
                last_ack=seq
                
                if seq not in data_windows:
                    data_windows.append(seq)
                    print('recv data:',msg.decode().split(' ')[1],' seq=',seq,'accept')
                while len(data_windows)>WINDOW_SIZE:
                    data_windows.pop(0)
            else:
                print('recv data:',msg.decode().split(' ')[1],' seq=',seq,'not accept')
                retmsg='ACK '+str(last_ack)
                client_recv_socket.sendto(retmsg.encode(),addr)


def GBN_send_data(s,data_to_send,addr):
    time=0
    seq=0
    data_windows=[]
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
                s.sendto(data.get_data().encode(),addr)
                data.state=1
        
        readable, writeable, errors = select.select([s, ], [], [], 1)
        if len(readable)>0:
            time=0
            
            message,address=s.recvfrom(1024)
            print('ACK:'+message.decode())
            for i in range(len(data_windows)):
                if int(message.decode().split(' ')[1])==data_windows[i].seq:
                    print('move')
                    data_windows=data_windows[i+1:]
                    break
        else:
            time+=1

    s.sendto('end'.encode(),addr)
    
    
def GBN_send_and_recv(s,data_to_send,addr):
    send_time=0
    send_seq=0
    send_data_windows=[]
    recv_last_ack=SEQ_LENGTH-1
    recv_data_windows=[]
    send_wite=1
    recv_wite=1
    while send_wite or recv_wite:
        if send_time>MAX_TIME:
            print('time out resend')
            for data in send_data_windows:
                data.state=0
        while len(send_data_windows)<WINDOW_SIZE:
            d=data_to_send.next()
            if not d:
                break
            data=Data(d,seq=send_seq)
            send_data_windows.append(data)
            send_seq+=1
        if not send_data_windows:
            print('send over')
            s.sendto('end'.encode(),addr)
            send_wite=0
        if send_wite:
            for data in send_data_windows:
                if not data.state:
                    print('send:'+data.get_data())
                    s.sendto(data.get_data().encode(),addr)
                    data.state=1
        readable, writeable, errors = select.select([s, ], [], [], 1)
        if len(readable)>0:
            message,address=s.recvfrom(1024)
            if 'ACK' in message.decode():
                #确认信息
                print(message.decode())
                for i in range(len(send_data_windows)):
                    if int(message.decode().split(' ')[1])==send_data_windows[i].seq:
                        print('windows move')
                        send_data_windows=send_data_windows[i+1:]
                        break
            else:
                #发送信息
                if message.decode()=='end':
                    recv_wite=0
                    print('recv over')
                    continue
                seq=int(message.decode().split(' ')[0])
                if recv_last_ack==(seq-1)%SEQ_LENGTH:
                    retmsg='ACK '+str(seq)
                    s.sendto(retmsg.encode(),addr)
                    recv_last_ack=seq

                    if seq not in recv_data_windows:
                        recv_data_windows.append(seq)
                        print('recv data:',message.decode().split(' ')[1],'seq=',seq,'accept')
                    while len(recv_data_windows)>WINDOW_SIZE:
                        recv_data_windows.pop(0)
                else:
                    print('recv data:',message.decode().split(' ')[1],' seq=',seq,'not accept')
                    retmsg='ACK '+str(recv_last_ack)
                    s.sendto(retmsg.encode(),addr) 
        else:
            if send_wite:
                send_time+=1


def GBN_send_file(s,file_path,addr):
    with open(file_path,'r') as f:
        filedata=''
        for line in f.readlines():
            filedata+=line
        data_to_send=SendData(filedata)
        f.close()
    time=0
    seq=0
    data_windows=[]
    while True:
        if time>MAX_TIME:#超时
            # print('time out resend')
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
                # print('send:'+data.get_data())
                s.sendto(data.get_data().encode(),addr)
                data.state=1
        
        readable, writeable, errors = select.select([s, ], [], [], 1)
        if len(readable)>0:
            time=0
            
            message,address=s.recvfrom(1024)
            # print('ACK:'+message.decode())
            for i in range(len(data_windows)):
                if int(message.decode().split(' ')[1])==data_windows[i].seq:
                    # print('move')
                    data_windows=data_windows[i+1:]
                    break
        else:
            time+=1

    s.sendto('end'.encode(),addr)
        

def GBN_recv_file(s,save_path):
    last_ack = SEQ_LENGTH - 1
    data_windows = []
    filedata=''
    while True:
        readable, writeable, errors = select.select([s, ], [], [], 1)
        if len(readable)>0:
            msg,addr=s.recvfrom(1024)
            if msg.decode()=='end':
                break
            seq=int(msg.decode().split(' ')[0])
            if last_ack==(seq-1)%SEQ_LENGTH:
                retmsg='ACK '+str(seq)
                s.sendto(retmsg.encode(),addr)
                last_ack=seq
                
                if seq not in data_windows:
                    data_windows.append(seq)
                    # print('recv data:',msg.decode().split(' ')[1],' seq=',seq,'accept')
                    filedata+=msg.decode().split(' ')[1]
                while len(data_windows)>WINDOW_SIZE:
                    data_windows.pop(0)
            else:
                # print('recv data:',msg.decode().split(' ')[1],' seq=',seq,'not accept')
                retmsg='ACK '+str(last_ack)
                s.sendto(retmsg.encode(),addr)
    with open(save_path,'w') as f:
        f.write(filedata)
        f.close()
        
        
def SR_send(s,data_to_send,addr):
    times=[]
    seq=0
    data_windows=[]
    while True:
        for i in range(len(times)):
            if times[i]>MAX_TIME:
                print('seq:',data_windows[i].seq,'time out. resend')
                data_windows[i].state=0
        while len(data_windows)<WINDOW_SIZE:
            d=data_to_send.next()
            if not d:
                break
            data=Data(d,seq=seq)
            times.append(0)
            data_windows.append(data)
            seq+=1
        if not data_windows:
            break
        for data in data_windows:
            if not data.state:
                print('send:'+data.get_data())
                s.sendto(data.get_data().encode(),addr)
                data.state=1
        readable, writeable, errors = select.select([s, ], [], [], 1)
        if len(readable)>0:
            message,address=s.recvfrom(1024)
            ack=message.decode().split(' ')[1]
            for i in range(len(data_windows)):
                if int(ack)==data_windows[i].seq:
                    times[i]=-1
                    if i==0:
                        print('ACK:',ack,'recv move')
                        data_windows=data_windows[i+1:]
                        times=times[i+1:]
                        if times:
                            while times[0]==-1:
                                print('seq:',data_windows[0].seq,' is already ack. move')
                                data_windows=data_windows[1:]
                                times=times[1:]
                                if not data_windows or not times:
                                    break
                    else:
                        print('ACK:',ack,'recv but not move')
                    break
        else:
            for i in range(len(times)):
                if times[i]!=-1:
                    times[i]+=1
    s.sendto('end'.encode(),addr)
    
def SR_recv(s):
    start_seq=0
    data_windows=[]
    data_cache=[]
    while True:
        readable, writeable, errors = select.select([s, ], [], [], 1)
        if len(readable)>0:
            message,addr=s.recvfrom(1024)
            if message.decode()=='end':
                break
            seq=int(message.decode().split(' ')[0])
            data=message.decode().split(' ')[1]
            if seq==start_seq:
                if random.random()<PACKET_LOSS_P:
                    continue
                retmsg='ACK '+str(seq)
                s.sendto(retmsg.encode(),addr)
                start_seq=(seq+1)%SEQ_LENGTH
                if seq not in data_windows:
                    data_windows.append(seq)
                    print('recv data:',message.decode().split(' ')[1],' seq=',seq,'accept')
                while len(data_windows)>WINDOW_SIZE:
                    data_windows.pop(0)
                if data_cache:
                    while start_seq==data_cache[0][0]:
                        start_seq+=1
                        start_seq%=SEQ_LENGTH
                        seq=data_cache[0][0]
                        data=data_cache[0][1]
                        if seq not in data_windows:
                            data_windows.append(seq)
                            print('recv data from cache:',data,' seq=',seq,'accept')
                        while len(data_windows)>WINDOW_SIZE:
                            data_windows.pop(0)
                        
                        
                        data_cache=data_cache[1:]
                        if not data_cache:
                            break
                    
                #处理缓存
            else:
                for i in range(WINDOW_SIZE):
                    if seq == (i+start_seq)%SEQ_LENGTH:
                        print('recv data:',message.decode().split(' ')[1],' seq=',seq,'not accept but cached')
                        data_cache.append([seq,data])
                        retmsg='ACK '+str(seq)
                        s.sendto(retmsg.encode(),addr)
                        break
                
    pass