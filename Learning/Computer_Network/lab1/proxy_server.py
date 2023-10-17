import socket
import _thread
import os
import time
import requests

webset_is_prohibited=['jwc.hit.edu.cn']
fish_websit={'www.hit.edu.cn':'fuhua.love/fish'}

ip_is_prohibited=['127.0.0.1']


def Check_cache(a,b):##cache偷鸡
    if os.path.exists(a):
        print('cache hit!')
    return False

class Http_Requst():
    def __init__(self,msg):
        self.msg=msg.decode()
        self._parse()
        pass
    
    def _parse(self):
        i,j=self.msg.find('\r\n'),self.msg.find('\r\n\r\n')
        self.req_line=self.msg[:i]
        self.req_header=self.msg[i+2:j]
        self.req_data=self.msg[j+4:]
        #方法获取
        self.method=self.req_line.split(' ')[0]
        
        #网站域名+端口
        for line in self.req_header.split('\r\n'):
            if line.startswith('Host: '):
                self.host=line.split(' ')[1].split(':')[0]
                if len(line.split(' ')[1].split(':'))<2:
                    self.prot=80
                else:
                    self.prot=line.split(' ')[1].split(':')[1]
                
                break
        
        #url解析
        self.url=self.req_line.split(' ')[1]
        if '//' in self.url:
            self.path=self.url.split('//')[1].replace(self.host,'')
        else:
            self.path=self.url.replace(self.host,'')
        
        #scheme解析
        self.scheme=self.req_line.split(' ')[2]
        
            
def communicate(sock1, sock2,cache_path):
    try:
        while 1:
            data = sock1.recv(20*1024)
            with open(cache_path,'w') as f:
                f.write(data.decode())
                f.close()
            if not data:
                return
            sock2.sendall(data)
    except:
        pass

def check_cache(file_path,url):
    use_cache=False
    if os.path.exists(file_path+'_'):
        file_time=os.stat(file_path).st_mtime
        headers = {'If-Modified_Since':time.strftime('%a, %d %b %Y %H:%M:%S GMT', time.gmtime(file_time))}
        # print('url',url)
        try:
            if requests.get(url, headers=headers).status_code == 304:
                use_cache = True
        except Exception as e:
                print("An exception occurred:", str(e))
    return use_cache


       
def handle(client):
    timeout = 10
    client.settimeout(timeout)
    msg=client.recv(20*1024)
    requst=Http_Requst(msg)
    New_client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    
    #判断域名是否被禁止访问
    if requst.host in webset_is_prohibited:
        print('********************************')
        pass
    else:
        if requst.method=='CONNECT':
            pass    
        else:
            #重构请求行
            new_req_line=requst.method+' '+requst.path+' '+requst.scheme

            
            #fish
            if requst.host in fish_websit.keys():
                fish_msg=requst.scheme+' 302 Moved Temporarily\r\nLocation: http://'+fish_websit[requst.host]+'\r\n\r\n'
                client.sendall(fish_msg.encode())
            New_client.connect((requst.host,requst.prot))
            New_client.settimeout(timeout)
            #check cache
            file_name=requst.host+'_'+requst.path.replace('/','_')
            file_path='D:/code/Learning/Computer_Network\lab1/cache/'+file_name
            use_cache=False
            use_cache=Check_cache(file_path,requst.url)
            if use_cache:
                with open(file_path,'r') as f:
                    cached_msg=f.read()
                    print(cached_msg)
                    client.sendall(cached_msg.encode())
                    f.close()   
            else:
                send_msg=new_req_line+'\r\n'+requst.req_header+'\r\n\r\n'+requst.req_data
                New_client.sendall(send_msg.encode())
                communicate(New_client,client,file_path)
    New_client.close()
    client.close()

if __name__=='__main__':
    ip='127.0.0.1'
    port=8088
    s =socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((ip,port))
    s.listen(10)
    while True:
        conn,addr=s.accept()
        if addr[0] in ip_is_prohibited:
            pass
        else:
            _thread.start_new_thread(handle,(conn,))        