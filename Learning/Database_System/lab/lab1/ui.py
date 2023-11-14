from os import name
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox, QTableWidgetItem
from PyQt5.uic import loadUi
from PyQt5.QtWidgets import QFileDialog

from utils_ui import *
from Ui_DB import *

class MyWindow(QMainWindow,Ui_MainWindow):
    def __init__(self,cursor,db):
        super().__init__()
        
        
        self.setupUi(self)
        self.setWindowTitle("schoolManage")
        self.cur=cursor
        self.db=db
        
        
        self.create_view.clicked.connect(self.Creat_view)
        self.having_test.clicked.connect(self.Having_test)
        
        
        self.school_query.clicked.connect(self.School_query)
        self.add_school.clicked.connect(self.Add_school)
        self.lib_query.clicked.connect(self.Lib_query)
        self.book_query.clicked.connect(self.Book_query)
        self.add_book.clicked.connect(self.Add_book)
        self.del_book.clicked.connect(self.Del_book)
        self.teacher_query.clicked.connect(self.Teacher_query)
        self.add_teacher.clicked.connect(self.Add_teacher)
        self.del_teacher.clicked.connect(self.Del_teacher)
        self.student_queery.clicked.connect(self.Student_query)
        self.add_student.clicked.connect(self.Add_student)
        self.del_student.clicked.connect(self.Del_student)
        self.class_query.clicked.connect(self.Class_query)
        self.add_class.clicked.connect(self.Add_class)
        self.del_class.clicked.connect(self.Del_class)
        self.classroom_query.clicked.connect(self.Classroom_query)
        self.add_classroom.clicked.connect(self.Add_classroom)
        self.del_classroom.clicked.connect(self.Del_classroom)
        self.course_query.clicked.connect(self.Course_query)
        self.add_course.clicked.connect(self.Add_course)
        self.del_course.clicked.connect(self.Del_course)
        self.free_cr_query.clicked.connect(self.Free_cr_query)
        self.selected_course_query.clicked.connect(self.Selected_course_query)
        self.free_course_query.clicked.connect(self.Free_course_query)
        self.select_course.clicked.connect(self.Select_course)
        self.drop_course.clicked.connect(self.Drop_course)
        self.borrowed_book_query.clicked.connect(self.Borrowed_book_query)
        self.free_book_query.clicked.connect(self.Free_book_query)
        self.borrow_book.clicked.connect(self.Borrow_book)
        self.return_book.clicked.connect(self.Return_book)
    
    def generate_html_table(self,id_list, name_list):
        if len(id_list) != len(name_list):
            return "Error: The length of the two lists must be the same."

        table_html = "<table border='1'>\n"
        table_html += "<tr><th>ID</th><th>Name</th></tr>\n"

        for i in range(len(id_list)):
            table_html += f"<tr><td>{id_list[i]}</td><td>{name_list[i]}</td></tr>\n"

        table_html += "</table>"

        return table_html
    
    def Close_db(self):
        self.db.close()
        
        
        
        
    def Having_test(self):
        err,r=having(self.cur,self.db)
        if not err:
            QMessageBox.information(self, 'Error', r, QMessageBox.Ok)   # type: ignore
        else:
            QMessageBox.information(self, '选课门数大于平均选课门数的学生', r, QMessageBox.Ok)   # type: ignore
    
    
    def Creat_view(self):
        id=self.add_school_id.toPlainText()
        err,msg=create_view(self.cur,self.db,id)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)   # type: ignore
        

    def School_query(self):
        err,schools=query_school(self.cur,self.db)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)   # type: ignore
        else:
            self.school_display.setHtml(self.generate_html_table(schools[0],schools[1]))
            
            
    def Add_school(self):
        id=self.add_school_id.toPlainText()
        name=self.add_school_name.toPlainText()
        err,msg=add_school(self.cur,self.db,id,name)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)   # type: ignore
    def Lib_query(self):
        err,schools=query_lib(self.cur,self.db)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)   # type: ignore
        else:
            self.lib_display.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Book_query(self):
        id=self.book_query_lib_id.toPlainText()
        err,schools=book_query(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)   # type: ignore
        else:
            self.books_desplay.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Add_book(self):
        id=self.book_query_lib_id.toPlainText()
        bid=self.add_book_id.toPlainText()
        bname=self.add_book_name.toPlainText()
        err,msg=add_book(self.cur,self.db,id,bid,bname)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)   # type: ignore
    def Del_book(self):
        id=self.book_query_lib_id.toPlainText()
        bid=self.add_book_id.toPlainText()
        err,msg=del_book(self.cur,self.db,id,bid)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)   # type: ignore

        
    def Teacher_query(self):
        id=self.school_id.toPlainText()
        err,schools=query_teachers(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.teacher_display.setHtml(self.generate_html_table(schools[0],schools[1]))
        
    def Add_teacher(self):
        sid=self.school_id.toPlainText()
        id=self.add_teacher_id.toPlainText()
        name=self.add_teacher_name.toPlainText()
        err,msg=add_teacher(self.cur,self.db,sid,id,name)  
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore
        
        
    def Del_teacher(self):
        id=self.add_teacher_id.toPlainText()
        err,msg=del_teacher(self.cur,self.db,id)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore
        
    def Student_query(self):
        id=self.school_id.toPlainText()
        err,schools=query_students(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.student_display.setHtml(self.generate_html_table(schools[0],schools[1]))
        
    def Add_student(self):
        sid=self.school_id.toPlainText()
        id=self.add_student_id.toPlainText()
        name=self.add_student_name.toPlainText()
        classid=self.add_student_name_2.toPlainText()
        err,msg=add_student(self.cur,self.db,sid,classid,id,name)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore
    def Del_student(self):
        id=self.add_student_id.toPlainText()
        err,msg=del_student(self.cur,self.db,id)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore
    def Class_query(self):
        id=self.school_id.toPlainText()
        err,schools=query_classes(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.class_display.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Add_class(self):
        id=self.school_id.toPlainText()
        cid=self.add_class_id.toPlainText()
        err,msg=add_class(self.cur,self.db,id,cid)  
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore
    
    def Del_class(self):
        cid=self.add_class_id.toPlainText()
        err,msg=del_class(self.cur,self.db,cid)  
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore

        
    def Classroom_query(self):
        id=self.school_id.toPlainText()
        err,schools=query_classrooms(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.classroom_display.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Add_classroom(self):
        id=self.school_id.toPlainText()
        cid=self.classroom_id.toPlainText()
        addr=self.classroom_addr.toPlainText()
        err,msg=add_classroom(self.cur,self.db,id,cid,addr)  
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore
        
    def Del_classroom(self):
        cid=self.classroom_id.toPlainText()
        err,msg=del_classroom(self.cur,self.db,cid)  
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore

    def Course_query(self):
        id=self.teacher_id.toPlainText()
        err,schools=query_course(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.course_display.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Add_course(self):
        id=self.teacher_id.toPlainText()
        cid=self.add_course_id.toPlainText()
        cname=self.add_course_name.toPlainText()
        crid=self.add_course_classroom.toPlainText()
        err,msg=add_course(self.cur,self.db,id,cid,cname,crid)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  

        

    def Del_course(self):
        id=self.teacher_id.toPlainText()
        cid=self.add_course_id.toPlainText()
        err,msg=del_course(self.cur,self.db,id,cid)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  

    def Free_cr_query(self):
        id=self.teacher_id.toPlainText()
        err,schools=free_classroom_query(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.free_classroom_display_2.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Selected_course_query(self):
        id=self.student_id.toPlainText()
        
        err,schools=query_selected_courses(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.selected_course_display.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Free_course_query(self):
        id=self.student_id.toPlainText()
        err,schools=free_courses_query(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.free_course_display.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Select_course(self):
        id=self.student_id.toPlainText()
        cid=self.student_id_2.toPlainText()
        err,msg=select_course(self.cur,self.db,id,cid)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore

    def Drop_course(self):
        id=self.student_id.toPlainText()
        cid=self.student_id_2.toPlainText()
        err,msg=drop_course(self.cur,self.db,id,cid)
        if not err:
            QMessageBox.information(self, 'Error', msg, QMessageBox.Ok)  # type: ignore

    def Borrowed_book_query(self):
        id=self.student_id.toPlainText()
        err,schools=query_borrow_books(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.borrowed_book_display.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Free_book_query(self):
        id=self.student_id.toPlainText()
        err,schools=fb_query(self.cur,self.db,id)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
        else:
            self.free_book_display.setHtml(self.generate_html_table(schools[0],schools[1]))

    def Borrow_book(self):
        id=self.student_id.toPlainText()
        bid=self.student_id_3.toPlainText()
        err,schools=borrow_book(self.cur,self.db,id,bid)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore
    def Return_book(self):
        id=self.student_id.toPlainText()
        bid=self.student_id_3.toPlainText()
        err,schools=return_book(self.cur,self.db,id,bid)
        if err==0:
            QMessageBox.information(self, 'Error', schools, QMessageBox.Ok)  # type: ignore


    
    
    


