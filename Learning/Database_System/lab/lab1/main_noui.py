import pymysql
from utils_noui import *

system_control=[str(i) for i in range(12)]
help1_control=[str(i) for i in range(3)]
helpx_control=[str(i) for i in range(4)]
  
system_help='欢迎!\n0.退出\n1.院系管理\n2.院系老师管理\n3.院系学生管理\n4.图书馆管理\n5.老师课程管理\n6.学生选课管理\n7.学生借书管理\n8.创建视图\n9.having\n10.班级管理\n11.教室管理'
help1='0.退出\n1.查询已有院系\n2.添加院系'
help2='0.退出\n1.查询院系老师\n2.增加院系老师\n3.删除院系老师'
help3='0.退出\n1.查询院系学生\n2.增加院系学生\n3.删除院系学生'
help4='0.退出\n1.查询已有图书\n2.增加图书\n3.删除图书'
help5='0.退出\n1.查询已经开设的课\n2.开设新课\n3.删除课程'
help6='0.退出\n1.查询已选课程\n2.选课\n3.退课'
help7='0.退出\n1.查询已借图书\n2.借书\n3.还书'
help10='0.退出\n1.查询已有班级\n2.增加班级\n3.删除班级'
help11='0.退出\n1.查询已有教室\n2.增加教室\n3.删除教室'



host='localhost'
port=3306
user='root'
passwd='Fu213138487'
DataBase='db_lab1'
try:
    db=pymysql.connect(host=host,user=user,passwd=passwd,port=port,db=DataBase)
    cursor=db.cursor()
    print('connect success')
except:
    print('error can not connect database')
    exit(0)

control_flag='0'
while True:
    print(system_help)
    control_flag=input(':')
    while control_flag not in system_control:
        control_flag=input('Invalid input, please re-enter:')
    if(control_flag=='0'):
        break
    elif(control_flag=='1'):
        inflag='0'
        while True:
            print(help1)
            inflag=input(":")
            while inflag not in help1_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_school(cursor,db)
            elif inflag=='2':
                add_school(cursor,db)
        
        
    elif(control_flag=='2'):
        inflag='0'
        while True:
            print(help2)
            inflag=input(":")
            while inflag not in helpx_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_teachers(cursor,db)
            elif inflag=='2':
                add_teacher(cursor,db)
            elif inflag=='3':
                del_teacher(cursor,db)
    elif(control_flag=='3'):
        inflag='0'
        while True:
            print(help3)
            inflag=input(":")
            while inflag not in helpx_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_students(cursor,db)
            elif inflag=='2':
                add_student(cursor,db)
            elif inflag=='3':
                del_student(cursor,db)
    elif(control_flag=='4'):
        inflag='0'
        while True:
            print(help4)
            inflag=input(":")
            while inflag not in helpx_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_books(cursor,db)
            elif inflag=='2':
                add_book(cursor,db)
            elif inflag=='3':
                del_book(cursor,db)
    elif(control_flag=='5'):
        inflag='0'
        while True:
            print(help5)
            inflag=input(":")
            while inflag not in helpx_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_course(cursor,db)
            elif inflag=='2':
                add_course(cursor,db)
            elif inflag=='3':
                del_course(cursor,db)
    elif(control_flag=='6'):
        inflag='0'
        while True:
            print(help6)
            inflag=input(":")
            while inflag not in helpx_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_selected_courses(cursor,db)
            elif inflag=='2':
                select_course(cursor,db)
            elif inflag=='3':
                drop_course(cursor,db)
    elif(control_flag=='7'):
        inflag='0'
        while True:
            print(help7)
            inflag=input(":")
            while inflag not in helpx_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_borrow_books(cursor,db)
            elif inflag=='2':
                borrow_book(cursor,db)
            elif inflag=='3':
                return_book(cursor,db)
    elif(control_flag=='8'):
        create_view(cursor,db)
    elif(control_flag=='9'):
        having(cursor,db)
    elif(control_flag=='10'):
        inflag='0'
        while True:
            print(help10)
            inflag=input(":")
            while inflag not in helpx_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_classes(cursor,db)
            elif inflag=='2':
                add_class(cursor,db)
            elif inflag=='3':
                del_class(cursor,db)
    elif(control_flag=='11'):
        inflag='0'
        while True:
            print(help11)
            inflag=input(":")
            while inflag not in helpx_control:
                inflag=input('Invalid input, please re-enter:')
            if inflag=='0':break
            elif inflag=='1':
                query_classrooms(cursor,db)
            elif inflag=='2':
                add_classroom(cursor,db)
            elif inflag=='3':
                del_classroom(cursor,db)








db.close()