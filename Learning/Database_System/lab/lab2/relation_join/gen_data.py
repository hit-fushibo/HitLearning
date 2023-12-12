from extmem import *

disk_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/relation/'

def generate_data():
    if os.path.exists(disk_dir):
        file_dir=disk_dir
        for file in os.listdir(file_dir):
            os.remove(file_dir + file)
    
    r=[]
    s=[]
    
    #R
    for i in range(16):
        ri=[]
        for j in range(7):
            rt=[]
            rt.append(random.randint(1,40))
            rt.append(random.randint(1,1000))
            while rt in ri:
                rt=[]
                rt.append(random.randint(1,40))
                rt.append(random.randint(1,1000))
            ri.append(rt)
        r.append(ri)
    
    #S
    for i in range(32):
        si=[]
        for j in range(7):
            st=[]
            st.append(random.randint(20,60))
            st.append(random.randint(1,1000))
            while st in si:
                st=[]
            st.append(random.randint(20,60))
            st.append(random.randint(1,1000))
            si.append(st)
        s.append(si)
        
    return r,s

def wirte_disk(r,s):
    #R
    for i in range(16):
        file='%s%s%d.blk'%(disk_dir,'r',i)
        lines=[]
        for j in range(7):
            line=str(r[i][j][0])+' '+str(r[i][j][1])+'\n'
            lines.append(line)
        lines[-1]=lines[-1][:-1]
        print(file)
        with open(file,'w') as f:
            f.writelines(lines)
        f.close()
    
    #S
    for i in range(32):
        file='%s%s%d.blk'%(disk_dir,'s',i)
        lines=[]
        for j in range(7):
            line=str(s[i][j][0])+' '+str(s[i][j][1])+'\n'
            lines.append(line)
        lines[-1]=lines[-1][:-1]
        with open(file,'w') as f:
            f.writelines(lines)
        f.close()
        
if __name__=='__main__':
    r,s=generate_data()
    wirte_disk(r,s)
    