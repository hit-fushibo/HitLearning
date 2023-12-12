from operator import truediv
import os
import random

from numpy import true_divide

disk_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/relation/'
tuple_num, R_disk_num, S_disk_num = 7, 16, 32

buf_size, blk_size = 520, 64  # bite


class Buf:
    def __init__(self) -> None:
        self.io_num = 0
        self.bufSize = buf_size
        self.blkSize = blk_size
        self.numAllBlk = int(self.bufSize/self.blkSize)
        self.numFreeBlk = self.numAllBlk
        self.data = [[]] * self.numAllBlk
        self.data_occupy = [False]*self.numAllBlk

    def freeBlockInBuffer(self, index) -> bool:
        '''
        index:要释放的缓冲区块号
        '''
        if self.data_occupy[index]:
            self.numFreeBlk += 1
            self.data_occupy[index] = False
        return not self.data_occupy[index]

    def getNewBlockBuffer(self) -> int:
        '''
        找到空闲的缓冲块分配并返回块号
        '''
        for i in range(len(self.data_occupy)):
            if not self.data_occupy[i]:
                self.data_occupy[i] = True
                self.numFreeBlk -= 1
                self.data[i]=[]
                return i
        return -1
    # def freeBuffer(self)

    def readBlockFromDisk(self, addr) -> int:
        '''
        首先申请一块空闲缓冲块，从addr文件中读取内容并保存到缓冲块中，返回缓冲块号
        '''
        index = self.getNewBlockBuffer()
        if index != -1:
            with (open(addr, 'r')) as f:
                lines = f.readlines()
                for line in lines:
                    line=line.replace('\n','')
                    self.data[index].append(line)
                # print(self.data[index])
                self.io_num += 1
                f.close()
        return index

    def writeBlockToDisk(self, index, addr):
        # print(addr)
        with open(addr, 'w') as f:
            self.io_num += 1
            lines=[]
            # print(self.data[index])
            for line in self.data[index]:
                line=line+'\n'
                lines.append(line)
            lines[-1]=lines[-1][:-1]
            f.writelines(lines)
            self.data_occupy[index]=False
            self.numFreeBlk+=1
            f.close()
        return True
    
    def dropBlockOnDisk(self,addr):
        blk_path=disk_dir+addr+'.blk'
        if os.path.exists(blk_path):
            os.remove(blk_path)    
        return True
