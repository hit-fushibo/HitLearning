import os
import extmem

# 关系选择目录
select_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/select/'
# 关系投影目录
project_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/project/'
# NLJ目录
nlj_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/nlj/'
# hash-join目录
hash_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/hash/'
# sort-merge-join目录
sort_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/sort/res/'
sort_temp_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/sort/temp/'
sort_sorted_dir = 'Learning/Database_System/lab/lab2/relation_join/disk/sort/sorted/'


def relation_select(buf: extmem.Buf):
    '''
    R.A=40 or S.C=60
    '''
    if os.path.exists(select_dir):
        for file in os.listdir(select_dir):
            os.remove(select_dir+file)
    else:
        os.makedirs(select_dir)

    # R.A=40
    num = 0
    tmp_R = []
    for i in range(16):
        file = extmem.disk_dir+'r'+str(i)+'.blk'
        index = buf.readBlockFromDisk(file)
        for data in buf.data[index]:
            R_A = int(data.split(' ')[0])
            R_B = int(data.split(' ')[1])

            if R_A == 40:
                # print(R_A,R_B,i,file)
                tmp_R.append(str(R_A)+' '+str(R_B))
            if len(tmp_R) == 7:

                w_index = buf.getNewBlockBuffer()
                if w_index != -1:
                    print(1)
                    buf.data[w_index] = tmp_R
                    file_path = select_dir+'r'+str(num)+'.blk'
                    buf.writeBlockToDisk(w_index, file_path)
                    num += 1
                    tmp_R = []
                    buf.freeBlockInBuffer(w_index)
        buf.freeBlockInBuffer(index)
    if 0 < len(tmp_R) < 8:
        w_index = buf.getNewBlockBuffer()
        if w_index != -1:
            buf.data[w_index] = tmp_R
            file_path = select_dir+'r'+str(num)+'.blk'
            buf.writeBlockToDisk(w_index, file_path)
            num += 1
            tmp_R = []
            buf.freeBlockInBuffer(w_index)

    # S.C=60
    num = 0
    tmp_R = []
    for i in range(32):
        file = extmem.disk_dir+'s'+str(i)+'.blk'
        index = buf.readBlockFromDisk(file)
        for data in buf.data[index]:
            R_A = int(data.split(' ')[0])
            R_B = int(data.split(' ')[1])
            if R_A == 60:
                tmp_R.append(str(R_A)+' '+str(R_B))
            if len(tmp_R) == 7:
                w_index = buf.getNewBlockBuffer()
                if w_index != -1:
                    buf.data[w_index] = tmp_R
                    file_path = select_dir+'s'+str(num)+'.blk'
                    buf.writeBlockToDisk(w_index, file_path)
                    num += 1
                    tmp_R = []
                    buf.freeBlockInBuffer(w_index)
        buf.freeBlockInBuffer(index)
    if 0 < len(tmp_R) < 8:
        w_index = buf.getNewBlockBuffer()
        if w_index != -1:
            buf.data[w_index] = tmp_R
            file_path = select_dir+'s'+str(num)+'.blk'
            buf.writeBlockToDisk(w_index, file_path)
            num += 1
            tmp_R = []
            buf.freeBlockInBuffer(w_index)


def relation_projct(buf: extmem.Buf):
    '''
    对R.A投影
    '''
    if os.path.exists(project_dir):
        for file in os.listdir(project_dir):
            os.remove(project_dir+file)
    else:
        os.makedirs(project_dir)

    res = set()
    for i in range(16):
        file = extmem.disk_dir+'r'+str(i)+'.blk'
        index = buf.readBlockFromDisk(file)
        for data in buf.data[index]:
            A = data.split(' ')[0]
            res.add(A)
        buf.freeBlockInBuffer(index)
    i = 0
    res_list = []
    index = buf.getNewBlockBuffer()
    if index == -1:
        print('error1')
        return
    for data in res:
        res_list.append(data)
        if len(res_list) == 14:
            buf.data[index] = res_list
            buf.writeBlockToDisk(index, project_dir+'r'+str(i)+'.blk')
            buf.freeBlockInBuffer(index)
            index = buf.getNewBlockBuffer()
            res_list = []
            i += 1
    buf.freeBlockInBuffer(index)
    if len(res_list) > 0:
        index = buf.getNewBlockBuffer()
        buf.data[index] = res_list
        buf.writeBlockToDisk(index, project_dir+'r'+str(i)+'.blk')
        buf.freeBlockInBuffer(index)


'''
JOIN

R.A=S.C

'''


def Nested_Loop_Join(buf: extmem.Buf):

    if os.path.exists(nlj_dir):
        for file in os.listdir(nlj_dir):
            os.remove(nlj_dir)
    else:
        os.makedirs(nlj_dir)
    num = 0
    res = []
    for i in range(16):
        R_index = buf.readBlockFromDisk(extmem.disk_dir+'r'+str(i)+'.blk')
        R_data = []
        for data in buf.data[R_index]:
            A = data.split(' ')[0]
            B = data.split(' ')[1]
            R_data.append([A, B])
        buf.freeBlockInBuffer(R_index)
        for j in range(32):
            S_index = buf.readBlockFromDisk(extmem.disk_dir+'s'+str(j)+'.blk')
            for data in buf.data[S_index]:
                C = data.split(' ')[0]
                D = data.split(' ')[1]
                for i in range(len(R_data)):
                    if C == R_data[i][0]:
                        res.append(R_data[i][0]+' '+R_data[i][1]+' '+D)
                        if len(res) == 4:
                            w_index = buf.getNewBlockBuffer()
                            buf.data[w_index] = res
                            buf.writeBlockToDisk(
                                w_index, nlj_dir+'j'+str(num)+'.blk')
                            buf.freeBlockInBuffer(w_index)
                            res = []
                            num += 1
            buf.freeBlockInBuffer(S_index)

    if len(res) > 0:
        w_index = buf.getNewBlockBuffer()
        buf.data[w_index] = res
        buf.writeBlockToDisk(w_index, nlj_dir+'j'+str(num)+'.blk')
        buf.freeBlockInBuffer(w_index)


def Hash_Join(buf: extmem.Buf):

    if os.path.exists(hash_dir):
        for file in os.listdir(hash_dir):
            os.remove(hash_dir)
    else:
        os.makedirs(hash_dir)

    hash_num = 37

    hash_R = [[]]*hash_num

    num = 0
    # hash
    for i in range(16):
        R_index = buf.readBlockFromDisk(extmem.disk_dir+'r'+str(i)+'.blk')

        for data in buf.data[R_index]:
            A = data.split(' ')[0]
            hash_R[int(A) % hash_num].append(data)
        buf.freeBlockInBuffer(R_index)

    res = []
    for i in range(32):
        S_index = buf.readBlockFromDisk(extmem.disk_dir+'s'+str(i)+'.blk')
        for data in buf.data[S_index]:
            C = data.split(' ')[0]
            D = data.split(' ')[1]
            for R_data in hash_R[int(C) % hash_num]:
                A = R_data.split(' ')[0]
                if C == A:
                    res.append(R_data+' '+D)
                    if len(res) == 4:
                        w_index = buf.getNewBlockBuffer()
                        buf.data[w_index] = res
                        buf.writeBlockToDisk(
                            w_index, hash_dir+'j'+str(num)+'.blk')
                        buf.freeBlockInBuffer(w_index)
                        res = []
                        num += 1
        buf.freeBlockInBuffer(S_index)
    if len(res) > 0:
        w_index = buf.getNewBlockBuffer()
        buf.data[w_index] = res
        buf.writeBlockToDisk(w_index, hash_dir+'j'+str(num)+'.blk')
        buf.freeBlockInBuffer(w_index)


def Sort_Merge_Join(buf: extmem.Buf):
    '''
    归并排序
    '''
    if os.path.exists(sort_dir):
        for file in os.listdir(sort_dir):
            os.remove(sort_dir+file)
    else:
        os.makedirs(sort_dir)

    if os.path.exists(sort_temp_dir):
        for file in os.listdir(sort_temp_dir):
            os.remove(sort_temp_dir+file)
    else:
        os.makedirs(sort_temp_dir)

    if os.path.exists(sort_sorted_dir):
        for file in os.listdir(sort_sorted_dir):
            os.remove(sort_sorted_dir+file)
    else:
        os.makedirs(sort_sorted_dir)

    # R
    num = 16/8
    for i in range(int(num)):
        data = []
        for j in range(8):

            index = buf.readBlockFromDisk(
                extmem.disk_dir+'r'+str(i*8+j)+'.blk')
            data += buf.data[index]

        data = sorted(data, key=lambda a: int(a.split(' ')[0]))
        for j in range(8):
            buf.data[j] = data[j*7:j*7+7]
            buf.writeBlockToDisk(j, sort_temp_dir+'r'+str(i)+str(j)+'.blk')

    num1 = 0
    num2 = 0
    num_res = 0
    flag1 = 0
    flag2 = 0
    flag_res = 0
    index1 = 0
    index2 = 5
    index_res = 0
    while True:
        if num2 == 8 and flag2 == 0:
            # the second segment finish
            if not flag_res:
                index_res = buf.getNewBlockBuffer()

            # handle the remaining data in seg1
            for data in buf.data[index1]:
                buf.data[index_res].append(data)
                if len(buf.data[index_res]) == 7:
                    buf.writeBlockToDisk(
                        index_res, sort_sorted_dir+'r'+str(num_res)+'.blk')
                    num_res += 1
                    index_res = buf.getNewBlockBuffer()
            while True:
                if num1 == 8:
                    if buf.data[index_res]:
                        buf.writeBlockToDisk(
                            index_res, sort_sorted_dir+'r'+str(num_res)+'.blk')
                    break

                index1 = buf.readBlockFromDisk(
                    sort_temp_dir+'r'+str(0)+str(num1)+'.blk')
                num1 += 1
                for data in buf.data[index1]:
                    buf.data[index_res].append(data)
                    if len(buf.data[index_res]) == 7:
                        buf.writeBlockToDisk(
                            index_res, sort_sorted_dir+'r'+str(num_res)+'.blk')
                        num_res += 1
                        index_res = buf.getNewBlockBuffer()
                buf.freeBlockInBuffer(index1)

            break
        elif num1 == 8 and flag1 == 0:
            # the fiest segment finish
            if not flag_res:
                index_res = buf.getNewBlockBuffer()

            # handle the remaining data in seg2
            for data in buf.data[index2]:
                buf.data[index_res].append(data)
                if len(buf.data[index_res]) == 7:
                    buf.writeBlockToDisk(
                        index_res, sort_sorted_dir+'r'+str(num_res)+'.blk')
                    num_res += 1
                    index_res = buf.getNewBlockBuffer()
            while True:
                if num2 == 8:
                    if buf.data[index_res]:
                        buf.writeBlockToDisk(
                            index_res, sort_sorted_dir+'r'+str(num_res)+'.blk')
                    break
                index2 = buf.readBlockFromDisk(sort_temp_dir+'r'+str(1)+str(num2)+'.blk')
                num2 += 1
                print(buf.data[index2])
                for data in buf.data[index2]:
                    buf.data[index_res].append(data)
                    if len(buf.data[index_res]) == 7:
                        buf.writeBlockToDisk(
                            index_res, sort_sorted_dir+'r'+str(num_res)+'.blk')
                        num_res += 1
                        index_res = buf.getNewBlockBuffer()
                buf.freeBlockInBuffer(index2)
                
            break
        else:
            # load new block
            if not flag1:
                buf.freeBlockInBuffer(index1)
                file1 = sort_temp_dir+'r'+str(0)+str(num1)+'.blk'
                index1 = buf.readBlockFromDisk(file1)
                flag1 = 1
                num1 += 1
            if not flag2:
                buf.freeBlockInBuffer(index2)
                file2 = sort_temp_dir+'r'+str(1)+str(num2)+'.blk'
                index2 = buf.readBlockFromDisk(file2)
                flag2 = 1
                num2 += 1
            if not flag_res:
                index_res = buf.getNewBlockBuffer()
                flag_res = 1
            # select the smallest from data[index1] and data[index2]
            if int(buf.data[index1][0].split(' ')[0]) > int(buf.data[index2][0].split(' ')[0]):
                buf.data[index_res].append(buf.data[index2][0])
                # test if need load new block
                buf.data[index2].pop(0)
                if len(buf.data[index2]) == 0:
                    flag2 = 0
            else:
                buf.data[index_res].append(buf.data[index1][0])
                # test if need load new block
                buf.data[index1].pop(0)
                if len(buf.data[index1]) == 0:
                    flag1 = 0
            # output buffer full,write to disk
            if len(buf.data[index_res]) == 7:
                file_res = sort_sorted_dir+'r'+str(num_res)+'.blk'
                buf.writeBlockToDisk(index_res, file_res)
                num_res += 1
                flag_res = 0
    buf.data_occupy = [False]*8
    # S
    num = 32/8
    for i in range(int(num)):
        data = []
        for j in range(8):
            index = buf.readBlockFromDisk(
                extmem.disk_dir+'s'+str(i*8+j)+'.blk')
            data += buf.data[index]

        data = sorted(data, key=lambda a: int(a.split(' ')[0]))

        for j in range(8):
            buf.data[j] = data[j*7:j*7+7]
            # print(buf.data[j])
            buf.writeBlockToDisk(j, sort_temp_dir+'s'+str(i)+str(j)+'.blk')
    num_i = [0, 0, 0, 0]
    num_res = 0
    flag_i = [0, 0, 0, 0]
    flag_res = 0
    index_i = [0, 1, 2, 3]
    index_res = 0
    over_flag = [0]*4
    while True:
        if num_i[0] == 8 and flag_i[0] == 0:
            over_flag[0] = 1
        if num_i[1] == 8 and flag_i[1] == 0:
            over_flag[1] = 1
        if num_i[2] == 8 and flag_i[2] == 0:
            over_flag[2] = 1
        if num_i[3] == 8 and flag_i[3] == 0:
            over_flag[3] = 1
        if over_flag == [1, 1, 1, 1]:
            if buf.data[index_res] and flag_res == 1:
                file_res = sort_sorted_dir+'s'+str(num_res)+'.blk'
                buf.writeBlockToDisk(index_res, file_res)
            break

        if 1:
            # load new block
            for i in range(4):
                if not flag_i[i] and not over_flag[i]:
                    buf.freeBlockInBuffer(index_i[i])
                    file_i = sort_temp_dir+'s'+str(i)+str(num_i[i])+'.blk'
                    index_i[i] = buf.readBlockFromDisk(file_i)
                    flag_i[i] = 1
                    num_i[i] += 1
            if not flag_res:
                index_res = buf.getNewBlockBuffer()
                flag_res = 1
            # select the smallest
            min_v = 10e4
            min_t = []
            min_index = 0
            for i in range(4):
                if over_flag[i] == 0:
                    if int(buf.data[index_i[i]][0].split(' ')[0]) < min_v:
                        min_v = int(buf.data[index_i[i]][0].split(' ')[0])
                        min_t = buf.data[index_i[i]][0]
                        min_index = i
            buf.data[index_i[min_index]].pop(0)
            if not buf.data[index_i[min_index]]:
                flag_i[min_index] = 0
            buf.data[index_res].append(min_t)
            # output buffer full,write to disk
            if len(buf.data[index_res]) == 7:
                file_res = sort_sorted_dir+'s'+str(num_res)+'.blk'
                buf.writeBlockToDisk(index_res, file_res)
                num_res += 1
                flag_res = 0
    buf.data_occupy = [False]*8

    '''
    连接
    '''
    R_num = 0
    S_num = 0
    R_file = sort_sorted_dir+'r'+str(R_num)+'.blk'
    S_file = sort_sorted_dir+'s'+str(S_num)+'.blk'
    R_index = buf.readBlockFromDisk(R_file)
    S_index = buf.readBlockFromDisk(S_file)
    res_num = 0
    res_index = buf.getNewBlockBuffer()
    tumple_num = 4

    while 1:
        '''
        R找S
        '''
        if int(buf.data[R_index][0].split(' ')[0]) == int(buf.data[S_index][0].split(' ')[0]):
            # print(2)
            buf.data[res_index].append(
                buf.data[R_index][0]+' '+buf.data[S_index][0].split(' ')[1])
            if len(buf.data[res_index]) == tumple_num:
                # print(1)
                res_file = sort_dir+'j'+str(res_num)+'.blk'
                buf.writeBlockToDisk(res_index, res_file)
                res_num += 1
                res_index = buf.getNewBlockBuffer()
            temp_blk = -1
            temp_num = 1
            if len(buf.data[S_index]) == 1:
                if S_num+temp_num == 32:
                    pass
                else:
                    temp_blk = buf.readBlockFromDisk(
                        sort_sorted_dir+'s'+str(S_num+temp_num)+'.blk')
            else:
                flag = 0
                for i in range(1, len(buf.data[S_index])):
                    if int(buf.data[R_index][0].split(' ')[0]) == int(buf.data[S_index][i].split(' ')[0]):
                        buf.data[res_index].append(
                            buf.data[R_index][0]+' '+buf.data[S_index][i].split(' ')[1])
                        if len(buf.data[res_index]) == tumple_num:
                            # print(1)
                            res_file = sort_dir+'j'+str(res_num)+'.blk'
                            buf.writeBlockToDisk(res_index, res_file)
                            res_num += 1
                            res_index = buf.getNewBlockBuffer()
                    else:
                        flag = 1
                        break
                if flag == 0:
                    if S_num+temp_num == 32:
                        pass
                    else:
                        temp_blk = buf.readBlockFromDisk(
                            sort_sorted_dir+'s'+str(S_num+temp_num)+'.blk')

            if temp_blk != -1:
                flag = 0
                while 1:
                    for i in range(len(buf.data[temp_blk])):
                        if int(buf.data[R_index][0].split(' ')[0]) == int(buf.data[temp_blk][i].split(' ')[0]):
                            buf.data[res_index].append(
                                buf.data[R_index][0]+' '+buf.data[temp_blk][i].split(' ')[1])
                            if len(buf.data[res_index]) == tumple_num:
                                # print(1)
                                res_file = sort_dir+'j'+str(res_num)+'.blk'
                                buf.writeBlockToDisk(res_index, res_file)
                                res_num += 1
                                res_index = buf.getNewBlockBuffer()
                        else:
                            flag = 1
                            break
                    buf.freeBlockInBuffer(temp_blk)
                    if flag == 0:
                        temp_num += 1
                        if S_num+temp_num == 32:
                            pass
                        else:
                            temp_blk = buf.readBlockFromDisk(
                                sort_sorted_dir+'s'+str(S_num+temp_num)+'.blk')
                    else:
                        break

            buf.data[R_index].pop(0)
            if not buf.data[R_index]:
                buf.freeBlockInBuffer(R_index)
                R_num += 1
                if R_num == 16:
                    break
                R_file = sort_sorted_dir+'r'+str(R_num)+'.blk'
                R_index = buf.readBlockFromDisk(R_file)

        elif int(buf.data[R_index][0].split(' ')[0]) > int(buf.data[S_index][0].split(' ')[0]):
            
            buf.data[S_index].pop(0)
            if not buf.data[S_index]:
                buf.freeBlockInBuffer(S_index)
                S_num += 1
                if S_num == 32:
                    break
                S_file = sort_sorted_dir+'s'+str(S_num)+'.blk'
                S_index = buf.readBlockFromDisk(S_file)
        else:
            
            buf.data[R_index].pop(0)
            if not buf.data[R_index]:
                buf.freeBlockInBuffer(R_index)
                R_num += 1
                if R_num == 16:
                    break
                R_file = sort_sorted_dir+'r'+str(R_num)+'.blk'
                R_index = buf.readBlockFromDisk(R_file)
    if buf.data[res_index]:
        res_file = sort_dir+'j'+str(res_num)+'.blk'
        buf.writeBlockToDisk(res_index, res_file)
    buf.data_occupy = [False]*8


def main():
    buf = extmem.Buf()
    relation_select(buf)
    print('关系选择IO次数：', buf.io_num)
    buf.__init__()
    relation_projct(buf)
    print('关系投影IO次数：', buf.io_num)
    buf.__init__()
    Nested_Loop_Join(buf)
    print('nlj——IO次数：', buf.io_num)
    buf.__init__()
    Hash_Join(buf)
    print('hash——IO次数：', buf.io_num)
    buf.__init__()
    Sort_Merge_Join(buf)
    print('sort_merge——IO次数：', buf.io_num)


if __name__ == '__main__':
    main()
