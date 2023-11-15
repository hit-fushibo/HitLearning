'''
没有ui的版本，命令行输入
'''


def having(cursor,db):
    sql='SELECT * FROM students WHERE ID IN(SELECT studentID FROM elective GROUP BY studentID HAVING COUNT(courseID) > (SELECT AVG(courseCount) FROM (SELECT COUNT(courseID) AS courseCount FROM elective GROUP BY studentID) AS subquery))'
    studentID_list=[]
    studentname_list=[]
    try:
        cursor.execute(sql)
        students=cursor.fetchall()
        for i in range(len(students)):
            studentID_list.append(students[i][0])
            studentname_list.append(students[i][1])
    except:
        print('having error! raw sql:',sql)
        return
    for i in range(len(studentID_list)):
        print(studentID_list[i],studentname_list[i])
    return
    

def create_view(cursor,db):
    sql='SELECT * FROM school'
    schoolsID_list=[]
    schoolsname_list=[]
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
        for i in range(len(schools)):
            schoolsID_list.append(schools[i][0])
            schoolsname_list.append(schools[i][1])
    except:
        print('error!create_view-query school. raw sql:',sql)
        return
    print('The departments that can generate views are as follows')
    for i in range(len(schoolsID_list)):
        print(schoolsID_list[i],schoolsname_list[i])
    
    school_id=input('Please enter the 3-digit ID of the department where you want to generate the view')
    '''
    Legal and Existence check
    '''
    if(len(school_id)!=3):
        print('error! The school ID must be 3 digits!')
        return
    if(school_id not in schoolsID_list):
        print('error! The school ID not exist!')
        return
    
    sql='CREATE VIEW '+school_id+'student_course_count AS SELECT s.id AS studentID, s.name AS studentName, COUNT(e.courseID) AS courseCount FROM students s JOIN in_school ins ON s.id = ins.studentID LEFT JOIN elective e ON s.id = e.studentID WHERE ins.schoolID = \''+school_id+'\' GROUP BY s.id, s.name'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error!create_view. raw sql:',sql)
        db.rollback()
        return
    return
    
'''
school_manage
'''
def query_school(cursor,db):
    sql='SELECT * FROM school'
    schools=None
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        print('query school error! raw sql:',sql)
        return
    print(schools)
        
    

def add_school(cursor,db):
    '''
    get id and name
    check null and illegality
    '''
    id=input('Please enter the school ID in three digits:')
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    name=input('Please enter the school name:')
    if(name==''):
        print('error! The school name cannot be empty!')
        return
    
    
    '''
    Check for duplicates
    '''
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if(cursor.execute(sql)!=0):
        
            print('repeat id')
            return  
    except:
        print('error! add_school-Check for duplicates-id.raw sql:',sql)
        return
    
    sql='SELECT * FROM school WHERE name=\''+name+'\''
    try:
        
        if(cursor.execute(sql)!=0):
            print('repeat name')  
            return
    except:
        print('error! add_school-Check for duplicates-name.raw sql:',sql)
        return
    
        
    '''
    update database
    '''
    sql='INSERT INTO school(ID,name) VALUES('+'\''+id+'\','+'\''+name+'\''+')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('add school error! raw sql:',sql)
        db.rollback()
    return



'''
teachers_manage
'''
def query_teachers(cursor,db):
    id=input('Please enter the three digit ID of the school you want to query:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('School with id ',id,' does not exist')
            return
    except:
        print('error! del_school-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    query_teacher
    '''
    sql='SELECT * FROM teachers WHERE ID IN(SELECT teacherID FROM teach WHERE schoolID=\''+id+'\')'
    try:
        cursor.execute(sql)
        teachers=cursor.fetchall()
    except:
        print('query teacher error! raw sql:',sql)
        return
    print(teachers)
    return

def add_teacher(cursor,db):
    '''
    get school_id
    '''
    id=input('Please enter the three digit ID of the school you want to add teacher:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('School with id ',id,' does not exist')
            return
    except:
        print('error! add_teacher-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get teacher ID and name
    '''
    teacher_ID=input('Please enter the ten ID of the teacher you want to add:')
    #legal and repeat check
    if(len(teacher_ID)!=10):
        print('error! The teacher ID must be 10 digits!')
        return
    sql='SELECT * FROM teachers WHERE ID=\''+teacher_ID+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('repeat id')
            return
    except:
        print('error! add_teacher-legal and repeat check. raw sql:',sql)
        return
    
    teacher_name=input('Please enter the name of the teacher you want to add:')
    
    
    '''
    insert into teachers table
    '''
    sql='INSERT INTO teachers(ID,name) VALUES('+'\''+teacher_ID+'\',\''+teacher_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        print('add teacher error! raw sql:',sql)
        db.rollback()
        return
    '''
    add teach relationship
    '''
    sql='INSERT INTO teach(teacherID,schoolID) VALUES(\''+teacher_ID+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('add teach relationship error! raw sql:',sql)
        db.rollback()
        return


def del_teacher(cursor,db,id=None):
    '''
    del by id
    
    teachers
    teach
    course
    teach_course
    elective
    '''
    
    '''
    get teacher id
    '''
    if(id==None):
        id=input('Please enter the 10 digit ID of the teacher you want to delete:')
    
        '''
        Legal and Existence check
        '''
        if(len(id)!=10):
            print('error! The teacher ID must be 10 digits!')
            return 
        sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
        try:
            if (cursor.execute(sql)==0):
                print('teacher with id ',id,' does not exist')
                return
        except:
            print('error! del_teacher-Legal and Existence check. raw sql:',sql)
            return
    
    '''
    get courseID that this teacher teach
    '''
    
    sql='SELECT courseID FROM teach_course WHERE teacherID=\''+id+'\''
    courseID_list=[]
    try:
        cursor.execute(sql)
        courseIDs=cursor.fetchall()
        for i in range(len(courseIDs)):
            courseID_list.append(courseIDs[i][0])
    except:
        print('error!del_teacher-get courseID that this teacher teach raw sql:',sql)
        return
    for i in range(len(courseID_list)):
        course_id=courseID_list[i]
        '''
        check is be selected
        '''
        sql='SELECT * FROM elective WHERE courseID=\''+course_id+'\''
        try:
            if (cursor.execute(sql)!=0):
                print('course with ID ',course_id,' is selected')
                return
        except:
            print('error! del_teacher-check is be selected. raw sql:',sql)
            return
        
        '''
        del teach_course courses
        '''
        sql='DELETE FROM teach_course WHERE courseID=\''+course_id+'\''
        try:
            cursor.execute(sql)
            
        except:
            print('error! del_teacher-del teach_course. raw sql:',sql)
            db.rollback()
            return
        
        sql='DELETE FROM courses WHERE ID=\''+course_id+'\''
        try:
            cursor.execute(sql)
        except:
            print('error! del_teacher-del course. raw sql:',sql)
            db.rollback()
            return
        return
    
    '''
    del teach
    '''
    sql='DELETE FROM teach WHERE teacherID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        print('error! del_teacher-del teach. raw sql:',sql)
        db.rollback()
        return
    '''
    del teachers
    '''
    sql='DELETE FROM teachers WHERE ID=\''+id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error! del_teacher-del teachers. raw sql:',sql)
        db.rollback()
        return
    
    return
    
    
    
    

'''
students_manage
'''
def query_students(cursor,db):
    id=input('Please enter the three digit ID of the school you want to query:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('School with id ',id,' does not exist')
            return
    except:
        print('error! del_school-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    query_teacher
    '''
    sql='SELECT * FROM students WHERE ID IN(SELECT studentID FROM in_school WHERE schoolID=\''+id+'\')'
    try:
        cursor.execute(sql)
        students=cursor.fetchall()
    except:
        print('query students error! raw sql:',sql)
        return
    print(students)
    return

def add_student(cursor,db):
    '''
    get school_id
    '''
    id=input('Please enter the three digit ID of the school you want to add student:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('School with id ',id,' does not exist')
            return
    except:
        print('error! add_student-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get class_id
    '''
    sql='SELECT classID FROM class_in_school WHERE schoolID=\''+id+'\''
    try:
        cursor.execute(sql)
        classes=cursor.fetchall()
    except:
        print('error! add_student-get classes. raw sql:',sql)
        return
    print('Please enter the 7 digit ID of the class you want to add student.\nThe available classes are as follows:')
    classes_list=[]
    for i in range(len(classes)):
        print(classes[i])
        classes_list.append(classes[i][0])
    class_id=input(':')
    if class_id not in classes_list:
        print('error! wrong input!')
        return
    
    '''
    get student ID and name
    '''
    student_ID=input('Please enter the ten ID of the student you want to add:')
    #legal and repeat check
    if(len(student_ID)!=10):
        print('error! The student ID must be 10 digits!')
        return
    sql='SELECT * FROM students WHERE ID=\''+student_ID+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('repeat id')
            return
    except:
        print('error! add_student-legal and repeat check. raw sql:',sql)
        return
    
    student_name=input('Please enter the name of the student you want to add:')
    
    
    '''
    insert into students table
    '''
    sql='INSERT INTO students(ID,name) VALUES('+'\''+student_ID+'\',\''+student_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        print('add student error! raw sql:',sql)
        db.rollback()
        return
    '''
    add in_class relationship
    '''
    sql='INSERT INTO in_class(studentID,classID) VALUES(\''+student_ID+'\',\''+class_id+'\')'
    try:
        cursor.execute(sql)
    except:
        print('add in_class relationship error! raw sql:',sql)
        db.rollback()
        return
    '''
    add in_school relationship
    '''
    sql='INSERT INTO in_school(studentID,schoolID) VALUES(\''+student_ID+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('add in_school relationship error! raw sql:',sql)
        db.rollback()
        return
    

def del_student(cursor,db,id=None):
    '''
    del by id
    
    students
    in_school
    in_class
    
    elective
    borrow_book
    borrow
    '''
    
    
    #get student id
    if(id==None):
        id=input('Please enter the 10 digit ID of the student you want to delete:')
    
        '''
        Legal and Existence check
        '''
        if(len(id)!=10):
            print('error! The student ID must be 10 digits!')
            return 
        sql='SELECT * FROM students WHERE ID=\''+id+'\''
        try:
            if (cursor.execute(sql)==0):
                print('student with id ',id,' does not exist')
                return
        except:
            print('error! del_student-Legal and Existence check. raw sql:',sql)
            return
    
    
    
    '''
    del elective
    '''
    sql='DELETE FROM elective WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        print('error! del_student-del elective. raw sql:',sql)
        db.rollback()
        return
    
    
    '''
    del borrow_book
    '''
    sql='DELETE FROM borrow_book WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        print('error! del_student-del borrow_book. raw sql:',sql)
        db.rollback()
        return
    
    
    '''
    del in_class
    '''
    sql='DELETE FROM in_class WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        print('error! del_student-del in_class. raw sql:',sql)
        db.rollback()
        return
    
    '''
    del in_school
    '''
    sql='DELETE FROM in_school WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        print('error! del_student-del in_school. raw sql:',sql)
        db.rollback()
        return
    
    '''
    del students
    '''
    sql='DELETE FROM students WHERE ID=\''+id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error! del_student-del students. raw sql:',sql)
        db.rollback()
        return
    

'''
classes_manage
'''
def query_classes(cursor,db):
    
    '''
    get school id
    '''
    id=input('Please enter the three digit ID of the school you want to add teacher:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('School with id ',id,' does not exist')
            return
    except:
        print('error! add_teacher-Legal and Existence check. raw sql:',sql)
        return
    
    
    '''
    query classes
    '''
    sql='SELECT * FROM classes WHERE ID IN(SELECT classID FROM class_in_school WHERE schoolID=\''+id+'\')'
    try:
        cursor.execute(sql)
        classes=cursor.fetchall()
    except:
        print('query class error! raw sql:',sql)
        return
    print(classes)
    return

def add_class(cursor,db):
    '''
    get school_id
    '''
    id=input('Please enter the three digit ID of the school you want to add class:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('School with id ',id,' does not exist')
            return
    except:
        print('error! add_class-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get class ID
    '''
    class_id=input('Please enter the 7 ID of the class you want to add:')
    #legal and repeat check
    if(len(class_id)!=7):
        print('error! The class ID must be 7 digits!')
        return
    sql='SELECT * FROM classes WHERE ID=\''+class_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('repeat id')
            return
    except:
        print('error! add_class-legal and repeat check. raw sql:',sql)
        return
    
    '''
    insert into classes table
    '''
    sql='INSERT INTO classes(ID) VALUES(\''+class_id+'\')'
    try:
        cursor.execute(sql)
        
    except:
        print('add classes error! raw sql:',sql)
        db.rollback()
        return

    '''
    insert into class_in_school relationship
    '''
    sql='INSERT INTO class_in_school(classID,schoolID) VALUES(\''+class_id+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('add class_in_school relationship error! raw sql:',sql)
        db.rollback()
        return

def del_class(cursor,db):
    '''
    get class ID
    '''
    class_id=input('Please enter the 7 ID of the class you want to add:')
    #legal and exist check
    if(len(class_id)!=7):
        print('error! The class ID must be 7 digits!')
        return
    sql='SELECT * FROM classes WHERE ID=\''+class_id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('class with id ',class_id,' does not exist')
            return
    except:
        print('error! del_class-legal and exist check. raw sql:',sql)
        return
    
    
    '''
    check if have student
    '''
    sql='SELECT * FROM in_class WHERE classID=\''+class_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('There are students in the class that cannot be deleted')
            return
    except:
        print('error! del_class-check if have student. raw sql:',sql)
        return
    
    '''
    del classes class_in_school
    '''
    sql='DELETE FROM class_in_school WHERE classID=\''+class_id+'\''
    try:
        cursor.execute(sql)
    except:
        print('error! del_class-del class_in_school. raw sql:',sql)
        db.rollback()
        return
    
    sql='DELETE FROM classes WHERE ID=\''+class_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error! del_class-del classes. raw sql:',sql)
        db.rollback()
        return
    return

'''
classrooms_manage
'''
def query_classrooms(cursor,db):
    
    '''
    get school id
    '''
    id=input('Please enter the three digit ID of the school you want to query:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('School with id ',id,' does not exist')
            return
    except:
        print('error! query_classrooms-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    query classroom
    '''
    sql='SELECT * FROM classrooms WHERE ID IN(SELECT classroomID FROM classroom_in_school WHERE schoolID=\''+id+'\')'
    try:
        cursor.execute(sql)
        classrooms=cursor.fetchall()
    except:
        print('query classroom error! raw sql:',sql)
        return
    print(classrooms)
    return



def add_classroom(cursor,db):
    '''
    get school_id
    '''
    id=input('Please enter the three digit ID of the school you want to add classroom:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        print('error! The school ID must be 3 digits!')
        return 
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('School with id ',id,' does not exist')
            return
    except:
        print('error! add_classroom-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get classroom ID and name
    '''
    classroom_id=input('Please enter the 5 ID of the classroom you want to add:')
    #legal and repeat check
    if(len(classroom_id)!=5):
        print('error! The classroom ID must be 5 digits!')
        return
    sql='SELECT * FROM classrooms WHERE ID=\''+classroom_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('repeat id')
            return
    except:
        print('error! add_classroom-legal and repeat check. raw sql:',sql)
        return
    classroom_name=input('Please enter the address of the classroom you want to add:')
    
    '''
    insert into classrooms table
    '''
    sql='INSERT INTO classrooms(ID,address) VALUES(\''+classroom_id+'\',\''+classroom_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        print('add classrooms error! raw sql:',sql)
        db.rollback()
        return

    '''
    insert into classroom_in_school relationship
    '''
    sql='INSERT INTO classroom_in_school(classroomID,schoolID) VALUES(\''+classroom_id+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('add classroom_in_school relationship error! raw sql:',sql)
        db.rollback()
        return

def del_classroom(cursor,db):
    '''
    get classroom ID
    '''
    
    classroom_id=input('Please enter the 5 ID of the class you want to add:')
    #legal and exist check
    if(len(classroom_id)!=5):
        print('error! The classroom ID must be 5 digits!')
        return
    sql='SELECT * FROM classrooms WHERE ID=\''+classroom_id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('classroom with id ',classroom_id,' does not exist')
            return
    except:
        print('error! del_classroom-legal and exist check. raw sql:',sql)
        return
    
    '''
    check is occupied
    '''
    sql='SELECT * FROM occupation WHERE classroomID=\''+classroom_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('Classroom occupied')
            return
    except:
        print('error! del_classroom-check is borrowed. raw sql:',sql)
        return
    
    '''
    del classroom_in_school classrooms
    '''
    sql='DELETE FROM classroom_in_school WHERE classroomID=\''+classroom_id+'\''
    try:
        cursor.execute(sql)
    except:
        print('error! del_classroom-del classroom_in_school. raw sql:',sql)
        db.rollback()
        return
    
    sql='DELETE FROM classrooms WHERE ID=\''+classroom_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error! del_classroom-del classrooms. raw sql:',sql)
        db.rollback()
        return
    return
    

'''
library_manage
'''
def query_books(cursor,db):
    '''
    get library ID
    '''
    id=input('Please enter the 5 digit ID of the library you want to query:')

    '''
    Legal and Existence check
    '''
    if(len(id)!=5):
        print('error! The library ID must be 3 digits!')
        return 
    sql='SELECT * FROM libraries WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('library with id ',id,' does not exist')
            return
    except:
        print('error! query_books-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    query books
    '''
    sql='SELECT * FROM books WHERE ID IN(SELECT bookID FROM store WHERE libraryID=\''+id+'\')'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
    except:
        print('query book error! raw sql:',sql)
        return
    print(books)
    return
    
def add_book(cursor,db):
    '''
    get library ID
    '''
    id=input('Please enter the 5 digit ID of the library you want to query:')

    '''
    Legal and Existence check
    '''
    if(len(id)!=5):
        print('error! The library ID must be 3 digits!')
        return 
    sql='SELECT * FROM libraries WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('library with id ',id,' does not exist')
            return
    except:
        print('error! query_books-Legal and Existence check. raw sql:',sql)
        return
    '''
    get book in books
    '''
    booksID_list=[]
    booksname_list=[]
    sql='SELECT * FROM books'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
        print(books)
        for i in range(len(books)):
            booksID_list.append(books[i][0])
            booksname_list.append(books[i][1])
    except:
        print('error! query_books-Legal and Existence check. raw sql:',sql)
        return
    print('There are already books in the stack as follows')
    for i in range(len(booksID_list)):
        print(booksID_list[i],booksname_list[i])
        
    
    '''
    get add bookID
    '''
    book_id=input('Please enter the 10 digit ID of the book you want to add:')
    #check
    if(len(book_id)!=10):
        print('error! The book ID must be 10 digits!')
        return
    
    '''
    check is a new book
    '''
    if(book_id not in booksID_list):
        book_name=input('new book name:')
        sql='INSERT INTO books(ID,name) VALUES(\''+book_id+'\',\''+book_name+'\')'
        try:
            cursor.execute(sql)
        except:
            print('error! add_book-check is a new book. raw sql:',sql)
            db.rollback()
            return
    '''
    insert into store
    '''
    sql='INSERT INTO store(bookID,libraryID) VALUES(\''+book_id+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error! add_book-insert into store. raw sql:',sql)
        db.rollback()
        return
    return
    
    
    
    
def del_book(cursor,db):
    '''
    get library ID
    '''
    id=input('Please enter the 5 digit ID of the library you want to delete book:')

    '''
    Legal and Existence check
    '''
    if(len(id)!=5):
        print('error! The library ID must be 3 digits!')
        return 
    sql='SELECT * FROM libraries WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('library with id ',id,' does not exist')
            return
    except:
        print('error! query_books-Legal and Existence check. raw sql:',sql)
        return
    '''
    get del book id 
    '''
    book_id=input('Please enter the 10 digit ID of the book you want to delete:')
    #check
    if(len(book_id)!=10):
        print('error! The book ID must be 10 digits!')
        return
    sql='SELECT * FROM store WHERE libraryID=\''+id+'\' AND bookID=\''+book_id+'\''
    try:
        if(cursor.execute(sql)==0):
            print('error! The book with ID '+book_id+' does not exist in the library with ID ',id)
            return
    except:
        print('error! del_book-check. raw sql:',sql)

    
    
    '''
    check is be borrowed
    '''
    sql='SELECT * FROM borrow_book WHERE bookID=\''+book_id+'\''
    try:
        if(cursor.execute(sql)!=0):
            print('error! The book with ID '+book_id+' is borrowed')
            return
    except:
        print('error! del_book-check is be borrowed. raw sql:',sql)
    
    '''
    del store
    '''
    sql='DELETE FROM store WHERE libraryID=\''+id+'\' AND bookID=\''+book_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error! del_book-del store. raw sql:',sql)
        db.rollback()    

'''
teacher course management
'''
def query_course(cursor,db):
    '''
    get teacher id
    '''
    id=input('Please enter the 10 digit ID of the teacher you want to query:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The teacher ID must be 10 digits!')
        return 
    sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('teacher with id ',id,' does not exist')
            return
    except:
        print('error! query_course-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    query courses
    '''
    sql='SELECT * FROM courses WHERE ID IN(SELECT courseID FROM teach_course WHERE teacherID=\''+id+'\' )'
    try:
        cursor.execute(sql)
        courses=cursor.fetchall()
    except:
        print('query course error! raw sql:',sql)
        return
    print(courses)
    return
    
    
    
    
    
def add_course(cursor,db):
    '''
    get teacher id
    '''
    id=input('Please enter the 10 digit ID of the teacher you want to add course:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The teacher ID must be 10 digits!')
        return 
    sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('teacher with id ',id,' does not exist')
            return
    except:
        print('error! query_course-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get new course ID and name
    '''
    course_id=input('Please enter the 5 digit ID of the course you want to add:')
    '''
    Legal and repeat check
    '''
    if(len(course_id)!=5):
        print('error! The course ID must be 5 digits!')
        return
    sql='SELECT * FROM courses WHERE ID=\''+course_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('repeat id')
            return
    except:
        print('error! add_course-Legal and Existence check. raw sql:',sql)
        return
    course_name=input('Please enter the name of the course you want to add:')
    sql='SELECT * FROM courses WHERE name=\''+course_name+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('repeat name')
            return
    except:
        print('error! add_course-Legal and Existence check-name. raw sql:',sql)
        return
    
    '''
    get classroom
    '''
    #get schoolID
    schoolid=''
    sql='SELECT schoolID FROM teach WHERE teacherID=\''+id+'\''
    try:
        cursor.execute(sql)
        school_id=cursor.fetchall()[0][0]
    except:
        print('error!add_course-get schoolID. raw sql:',sql)
        return
    #get classrooms
    classroomsID_list=[]
    classroomsname_list=[]
    sql='SELECT * FROM classrooms WHERE ID IN(SELECT classroomID FROM classroom_in_school WHERE schoolID=\''+school_id+'\') AND ID NOT IN (SELECT classroomID FROM occupation)'
    try:
        cursor.execute(sql)
        classrooms=cursor.fetchall()
        for i in range(len(classrooms)):
            classroomsID_list.append(classrooms[i][0])
            classroomsname_list.append(classrooms[i][1])
    except:
        print('query classroom error! raw sql:',sql)
        return
    print('The free classrooms are as follows')
    for i in range(len(classroomsID_list)):
        print(classroomsID_list[i],classroomsname_list[i])
    
    classroom_id=('Please enter the 5 digit ID number of the classroom that the course needs to occupy:')
    '''
    Legal and Existence check
    '''
    if(len(classroom_id)!=5):
        print('error! The classroom ID must be 5 digits!')
        return
    if(classroom_id not in classroomsID_list):
        print('error! The classroom ID not exist!')
        return
    
    
    
    '''
    insert into courses teach_course occupation
    '''
    sql='INSERT INTO courses(ID,name) VALUES(\''+course_id+'\',\''+course_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        print('add courses error! raw sql:',sql)
        db.rollback()
        return
    
    sql='INSERT INTO occupation(courseID,classroomID) VALUES(\''+course_id+'\',\''+classroom_id+'\')'
    try:
        cursor.execute(sql)
        
    except:
        print('add occupation relationship error! raw sql:',sql)
        db.rollback()
        return
    
    sql='INSERT INTO teach_course(teacherID,courseID) VALUES(\''+id+'\',\''+course_id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('add teach_course relationship error! raw sql:',sql)
        db.rollback()
        return

def del_course(cursor,db):
    '''
    get teacher id
    '''
    id=input('Please enter the 10 digit ID of the teacher you want to add course:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The teacher ID must be 10 digits!')
        return 
    sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('teacher with id ',id,' does not exist')
            return
    except:
        print('error! del_course-Legal and Existence check. raw sql:',sql)
        return
    
    
    '''
    get course id
    '''
    course_id=input('Please enter the 5 digit ID of the course you want to add:')
    '''
    Legal and exist check
    '''
    if(len(course_id)!=5):
        print('error! The course ID must be 5 digits!')
        return
    sql='SELECT * FROM courses WHERE ID=\''+course_id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('course with id ',id,' does not exist')
            return
    except:
        print('error! del_course-Legal and exist check1. raw sql:',sql)
        return
    sql='SELECT * FROM teach_course WHERE teacherID=\''+id+'\' AND courseID=\''+course_id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('Teachers with ID '+id+' do not teach courses with ID ',course_id)
            return
    except:
        print('error! del_course-Legal and exist check2. raw sql:',sql)
        return
    
    '''
    check is be selected
    '''
    sql='SELECT * FROM elective WHERE courseID=\''+course_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            print('course with ID ',course_id,' is selected')
            return
    except:
        print('error! del_course-check is be selected. raw sql:',sql)
        return
    
    '''
    del occupation teach_course courses
    '''
    sql='DELETE FROM occupation WHERE courseID=\''+course_id+'\''
    try:
        cursor.execute(sql)
        
    except:
        print('error! del_course-del occupation. raw sql:',sql)
        db.rollback()
        return
    
    sql='DELETE FROM teach_course WHERE courseID=\''+course_id+'\''
    try:
        cursor.execute(sql)
        
    except:
        print('error! del_course-del teach_course. raw sql:',sql)
        db.rollback()
        return
    
    sql='DELETE FROM courses WHERE ID=\''+course_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error! del_course-del course. raw sql:',sql)
        db.rollback()
        return
    return
    
    
    
    
    
'''
student affairs management
'''
#course
def query_selected_courses(cursor,db):
    '''
    get student id
    '''
    id=input('Please enter the 10 digit ID of the student you want to query:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The student ID must be 10 digits!')
        return 
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('student with id ',id,' does not exist')
            return
    except:
        print('error! query_selected_courses-Legal and Existence check. raw sql:',sql)
        return
    
    
    '''
    query
    '''
    sql='SELECT * FROM courses WHERE ID IN(SELECT courseID FROM elective WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        courses=cursor.fetchall()
    except:
        print('query selected courses error! raw sql:',sql)
        return
    print(courses)
    return

def select_course(cursor,db):
    '''
    get student id
    '''
    id=input('Please enter the 10 digit ID of the student you want to select course:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The student ID must be 10 digits!')
        return 
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('student with id ',id,' does not exist')
            return
    except:
        print('error! query_selected_courses-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get courseID that can be selected
    '''
    #get school_id
    school_id=''
    sql='SELECT schoolID FROM in_school WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        school_id=cursor.fetchall()[0][0]
    except:
        print('error!select_course-get courseID that can be selected. raw sql:',sql)
        return
    #get courses list
    coursesID_list=[]
    coursesname_list=[]
    sql='SELECT * FROM courses WHERE ID IN(SELECT courseID FROM teach_course WHERE teacherID IN(SELECT teacherID FROM teach WHERE schoolID=\''+school_id+'\' )) AND ID NOT IN(SELECT courseID FROM elective WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        courses=cursor.fetchall()
        for i in range(len(courses)):
            coursesID_list.append(courses[i][0])
            coursesname_list.append(courses[i][1])
    except:
        print('error!select_course-get courses list. raw sql:',sql)
        return
    print('The courses can be selected are as follows:')
    for i in range(len(coursesID_list)):
        print(coursesID_list[i],coursesname_list[i])    
    
    
    
    courses_id=input('Please enter the 5-digit ID of the course you want to select:')
    '''
    Legal and Existence check
    '''
    if(len(courses_id)!=5):
        print('error! The course ID must be 5 digits!')
        return 
    if(courses_id not in coursesID_list):
        print('error! The course ID not exist!')
        return
    
    '''
    insert into elective
    '''
    sql='INSERT INTO elective(studentID,courseID) VALUES(\''+id+'\',\''+courses_id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error!select course-insert into elective. raw sql:',sql)
        db.rollback()
        return
    return
    
    
    
    
def drop_course(cursor,db):
    '''
    get student id
    '''
    id=input('Please enter the 10 digit ID of the student you want to drop course:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The student ID must be 10 digits!')
        return 
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('student with id ',id,' does not exist')
            return
    except:
        print('error! drop_course-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get courseID that can be dropped
    '''
    
    coursesID_list=[]
    coursesname_list=[]
    sql='SELECT * FROM courses WHERE ID IN (SELECT courseID FROM elective WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        courses=cursor.fetchall()
        for i in range(len(courses)):
            coursesID_list.append(courses[i][0])
            coursesname_list.append(courses[i][1])
    except:
        print('error!drop_course-get courseID that can be dropped. raw sql:',sql)
        return
    print('The courses can be dropped are as follows:')
    for i in range(len(coursesID_list)):
        print(coursesID_list[i],coursesname_list[i])    
    
    
    
    courses_id=input('Please enter the 5-digit ID of the course you want to drop:')
    '''
    Legal and Existence check
    '''
    if(len(courses_id)!=5):
        print('error! The course ID must be 5 digits!')
        return 
    if(courses_id not in coursesID_list):
        print('error! The course ID not exist!')
        return
    
    '''
    del elective
    '''
    sql='DELETE FROM elective WHERE studentID=\''+id+'\' AND courseID=\''+courses_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('drop course_del elective error! raw sql:',sql)
        db.rollback()
        return
    return


#book
def query_borrow_books(cursor,db):
    '''
    get student id
    '''
    id=input('Please enter the 10 digit ID of the student you want to query:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The student ID must be 10 digits!')
        return 
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('student with id ',id,' does not exist')
            return
    except:
        print('error! query_borrow_books-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    query
    '''
    sql='SELECT * FROM books WHERE ID IN(SELECT bookID FROM borrow_book WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
    except:
        print('query borrow books error! raw sql:',sql)
        return
    print(books)
    return

def borrow_book(cursor,db):
    '''
    get student id
    '''
    id=input('Please enter the 10 digit ID of the student you want to borrow book:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The student ID must be 10 digits!')
        return 
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('student with id ',id,' does not exist')
            return
    except:
        print('error! borrow_book-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get bookID that can be borrowed
    '''
    #get school_id
    school_id=''
    sql='SELECT schoolID FROM in_school WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        school_id=cursor.fetchall()[0][0]
    except:
        print('error!borrow_book-get school_id. raw sql:',sql)
        return
    booksID_list=[]
    booksname_list=[]
    sql='SELECT * FROM books WHERE ID IN(SELECT bookID FROM store WHERE libraryID IN(SELECT libraryID FROM have_library WHERE schoolID=\''+school_id+'\' )) AND ID NOT IN(SELECT bookID FROM borrow_book WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
        for i in range(len(books)):
            booksID_list.append(books[i][0])
            booksname_list.append(books[i][1])
    except:
        print('error!borrow_book-get bookID that can be borrowed. raw sql:',sql)
        return
    print('The books can be selected are as follows:')
    for i in range(len(booksID_list)):
        print(booksID_list[i],booksname_list[i])
    
    book_id=input('Please enter the 10-digit ID of the book you want to borrow:')
    '''
    Legal and Existence check
    '''
    if(len(book_id)!=10):
        print('error! The book ID must be 10 digits!')
        return
    if(book_id not in booksID_list):
        print('error! The book ID not exist!')
        return
    
    '''
    insert into borrow_book
    '''
    sql='INSERT INTO borrow_book(studentID,bookID) VALUES(\''+id+'\',\''+book_id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error!borrow_book-insert into borrow_book. raw sql:',sql)
        db.rollback()
        return
    return
    

def return_book(cursor,db):
    '''
    get student id
    '''
    id=input('Please enter the 10 digit ID of the student you want to return book:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        print('error! The student ID must be 10 digits!')
        return 
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print('student with id ',id,' does not exist')
            return
    except:
        print('error! return_book-Legal and Existence check. raw sql:',sql)
        return
    
    '''
    get bookID that can be returned
    '''
    bookID_list=[]
    bookname_list=[]
    sql='SELECT * FROM books WHERE ID IN(SELECT bookID FROM borrow_book WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
        for i in range(len(books)):
            bookID_list.append(books[i][0])
            bookname_list.append(books[i][1])
    except:
        print('error!return_book-get bookID that can be returned. raw sql:',sql)
        return
    print('The books can be returned are as follows:')
    for i in range(len(bookID_list)):
        print(bookID_list[i],bookname_list[i])
    
    book_id=input('Please enter the 5-digit ID of the course you want to drop:')
    '''
    Legal and Existence check
    '''
    if(len(book_id)!=10):
        print('error! The book ID must be 10 digits!')
        return 
    if(book_id not in bookID_list):
        print('error! The book ID not exist!')
        return
    
    '''
    del borrow_book
    '''
    sql='DELETE FROM borrow_book WHERE bookID=\''+book_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print('error!return_book-del borrow_book. raw sql:',sql)
        db.rollback()
        return
    return
