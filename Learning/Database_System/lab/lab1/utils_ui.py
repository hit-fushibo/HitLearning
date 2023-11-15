'''
有ui的版本
'''

def having(cursor,db):
    sql='SELECT * FROM students WHERE ID IN(SELECT studentID FROM elective GROUP BY studentID HAVING COUNT(courseID) > (SELECT AVG(courseCount) FROM (SELECT COUNT(courseID) AS courseCount FROM elective GROUP BY studentID) AS subquery))'
    studentID_list=[]
    studentname_list=[]
    rtstr=''
    try:
        cursor.execute(sql)
        students=cursor.fetchall()
        # print(students)
        for i in range(len(students)):
            rtstr=rtstr+students[i][0]+' '+students[i][1]+','
            # studentID_list.append()
            # studentname_list.append()
    except:
        # print()
        return 0,'having error! raw sql:'+sql
    return 1,rtstr[:-1]
    
    

def create_view(cursor,db,school_id):
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
        # print()
        return 0,'error!create_view-query school. raw sql:'+sql
    '''
    Legal and Existence check
    '''
    if(len(school_id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    if(school_id not in schoolsID_list):
        # print()
        return 0,'error! The school ID not exist!'
    
    sql='CREATE VIEW '+school_id+'student_course_count AS SELECT s.id AS studentID, s.name AS studentName, COUNT(e.courseID) AS courseCount FROM students s JOIN in_school ins ON s.id = ins.studentID LEFT JOIN elective e ON s.id = e.studentID WHERE ins.schoolID = \''+school_id+'\' GROUP BY s.id, s.name'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print('error!create_view. raw sql:',sql)
        db.rollback()
        return 0,'error!create_view. raw sql:'+sql
    return 1,1


def query_school(cursor,db):
    sql='SELECT * FROM school'
    schools=None
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        return 0,'query school error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]



def add_school(cursor,db,id,name):
    '''
    get id and name
    check null and illegality
    '''
    if(len(id)!=3):
        return 0,'error! The school ID must be 3 digits!'
    if(name==''):
        return 0,'error! The school name cannot be empty!'
    
    '''
    Check for duplicates
    '''
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if(cursor.execute(sql)!=0):
        
            # print('repeat id')
            return  0,'repeat id'
    except:
        # print('error! add_school-Check for duplicates-id.raw sql:',sql)
        return 0,'error! add_school-Check for duplicates-id.raw sql:'+sql
    
    sql='SELECT * FROM school WHERE name=\''+name+'\''
    try:
        
        if(cursor.execute(sql)!=0):
            # print('repeat name')  
            return 0,'repeat name'
    except:
        # print('error! add_school-Check for duplicates-name.raw sql:',sql)
        return 0,'error! add_school-Check for duplicates-name.raw sql:'+sql
    
        
    '''
    update database
    '''
    sql='INSERT INTO school(ID,name) VALUES('+'\''+id+'\','+'\''+name+'\''+')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print('add school error! raw sql:',sql)
        db.rollback()
        return 0,'add school error! raw sql:'+sql
    return 1,1

'''
teachers_manage
'''
def query_teachers(cursor,db,id):
    # id=input('Please enter the three digit ID of the school you want to query:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'School with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! del_school-Legal and Existence check. raw sql:'+sql
    
    '''
    query_teacher
    '''
    sql='SELECT * FROM teachers WHERE ID IN(SELECT teacherID FROM teach WHERE schoolID=\''+id+'\')'
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        print()
        return 0,'query teacher error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]

def add_teacher(cursor,db,id,teacher_ID,teacher_name):
    '''
    get school_id
    '''
    # id=input('Please enter the three digit ID of the school you want to add teacher:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print('School with id ',id,' does not exist')
            return 0,'School with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! add_teacher-Legal and Existence check. raw sql:'+sql
    
    '''
    get teacher ID and name
    '''
    # teacher_ID=input('Please enter the ten ID of the teacher you want to add:')
    #legal and repeat check
    if(len(teacher_ID)!=10):
        # print()
        return 0,'error! The teacher ID must be 10 digits!'
    sql='SELECT * FROM teachers WHERE ID=\''+teacher_ID+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print()
            return 0,'repeat id'
    except:
        # print('error! add_teacher-legal and repeat check. raw sql:',sql)
        return 0,'error! add_teacher-legal and repeat check. raw sql:'+sql
    
    # teacher_name=input('Please enter the name of the teacher you want to add:')
    
    
    '''
    insert into teachers table
    '''
    sql='INSERT INTO teachers(ID,name) VALUES('+'\''+teacher_ID+'\',\''+teacher_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        # print('add teacher error! raw sql:',sql)
        db.rollback()
        return 0,'add teacher error! raw sql:'+sql
    '''
    add teach relationship
    '''
    sql='INSERT INTO teach(teacherID,schoolID) VALUES(\''+teacher_ID+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print('add teach relationship error! raw sql:',sql)
        db.rollback()
        return 0,'add teach relationship error! raw sql:'+sql
    return 1,1


def del_teacher(cursor,db,id):
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
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The teacher ID must be 10 digits!'
    sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print('teacher with id ',id,' does not exist')
            return 0,'teacher with id '+id+' does not exist'
    except:
        # print('error! del_teacher-Legal and Existence check. raw sql:',sql)
        return 0,'error! del_teacher-Legal and Existence check. raw sql:'+sql
    
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
        # print('error!del_teacher-get courseID that this teacher teach raw sql:',sql)
        return 0,'error!del_teacher-get courseID that this teacher teach raw sql:'+sql
    for i in range(len(courseID_list)):
        course_id=courseID_list[i]
        '''
        check is be selected
        '''
        sql='SELECT * FROM elective WHERE courseID=\''+course_id+'\''
        try:
            if (cursor.execute(sql)!=0):
                # print('course with ID ',course_id,' is selected')
                return 0,'course with ID '+course_id+' is selected'
        except:
            # print()
            return 0,'error! del_teacher-check is be selected. raw sql:'+sql
        
        '''
        del teach_course courses
        '''
        sql='DELETE FROM teach_course WHERE courseID=\''+course_id+'\''
        try:
            cursor.execute(sql)
            
        except:
            # print()
            db.rollback()
            return 0,'error! del_teacher-del teach_course. raw sql:'+sql
        
        sql='DELETE FROM courses WHERE ID=\''+course_id+'\''
        try:
            cursor.execute(sql)
        except:
            # print()
            db.rollback()
            return 0,'error! del_teacher-del course. raw sql:'+sql
        
    
    '''
    del teach
    '''
    sql='DELETE FROM teach WHERE teacherID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        # print('error! del_teacher-del teach. raw sql:',sql)
        db.rollback()
        return 0,'error! del_teacher-del teach. raw sql:'+sql
    '''
    del teachers
    '''
    sql='DELETE FROM teachers WHERE ID=\''+id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'error! del_teacher-del teachers. raw sql:'+sql
    
    return 1,1
    
    
    
    

'''
students_manage
'''
def query_students(cursor,db,id):
    # id=input('Please enter the three digit ID of the school you want to query:')
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'School with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! del_school-Legal and Existence check. raw sql:'+sql
    
    '''
    query_teacher
    '''
    sql='SELECT * FROM students WHERE ID IN(SELECT studentID FROM in_school WHERE schoolID=\''+id+'\')'
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        # print('query students error! raw sql:',sql)
        return 0,'query students error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]
    
    
def add_student(cursor,db,id,class_id,student_ID,student_name):
   
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'School with id '+id+' does not exist'
    except:
        # print('error! add_student-Legal and Existence check. raw sql:',sql)
        return 0,'error! add_student-Legal and Existence check. raw sql:'+sql
    
    '''
    get class_id
    '''
    sql='SELECT classID FROM class_in_school WHERE schoolID=\''+id+'\''
    try:
        cursor.execute(sql)
        classes=cursor.fetchall()
    except:
        # print('error! add_student-get classes. raw sql:',sql)
        return 0,'error! add_student-get classes. raw sql:'+sql
    # print('Please enter the 7 digit ID of the class you want to add student.\nThe available classes are as follows:')
    classes_list=[]
    for i in range(len(classes)):
        print(classes[i])
        classes_list.append(classes[i][0])
    # class_id=input(':')
    if class_id not in classes_list:
        return 0,'error! wrong input!'
    
    '''
    get student ID and name
    '''
    # student_ID=input('Please enter the ten ID of the student you want to add:')
    #legal and repeat check
    if(len(student_ID)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+student_ID+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print()
            return 0,'repeat id'
    except:
        # print()
        return 0,'error! add_student-legal and repeat check. raw sql:'+sql
    
    # student_name=input('Please enter the name of the student you want to add:')
    
    
    '''
    insert into students table
    '''
    sql='INSERT INTO students(ID,name) VALUES('+'\''+student_ID+'\',\''+student_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'add student error! raw sql:'+sql
    '''
    add in_class relationship
    '''
    sql='INSERT INTO in_class(studentID,classID) VALUES(\''+student_ID+'\',\''+class_id+'\')'
    try:
        cursor.execute(sql)
    except:
        # print()
        db.rollback()
        return 0,'add in_class relationship error! raw sql:'+sql
    '''
    add in_school relationship
    '''
    sql='INSERT INTO in_school(studentID,schoolID) VALUES(\''+student_ID+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'add in_school relationship error! raw sql:'+sql
    return 1,1



def del_student(cursor,db,id):
    '''
    del by id
    
    students
    in_school
    in_class
    
    elective
    borrow_book
    borrow
    '''
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! del_student-Legal and Existence check. raw sql:'+sql
    
    
    
    '''
    del elective
    '''
    sql='DELETE FROM elective WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'error! del_student-del elective. raw sql:'+sql
    
    
    '''
    del borrow_book
    '''
    sql='DELETE FROM borrow_book WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'error! del_student-del borrow_book. raw sql:'+sql
    
    
    '''
    del in_class
    '''
    sql='DELETE FROM in_class WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'error! del_student-del in_class. raw sql:'+sql
    
    '''
    del in_school
    '''
    sql='DELETE FROM in_school WHERE studentID=\''+id+'\''
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'error! del_student-del in_school. raw sql:'+sql
    
    '''
    del students
    '''
    sql='DELETE FROM students WHERE ID=\''+id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'error! del_student-del students. raw sql:'+sql
    return 1,1
    

'''
classes_manage
'''
def query_classes(cursor,db,id):
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'School with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! add_teacher-Legal and Existence check. raw sql:'+sql
    
    
    '''
    query classes
    '''
    sql='SELECT * FROM classes WHERE ID IN(SELECT classID FROM class_in_school WHERE schoolID=\''+id+'\')'
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        print()
        return 0,'query class error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]

def add_class(cursor,db,id,class_id,class_name):

    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'School with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! add_class-Legal and Existence check. raw sql:'+sql
    
    #legal and repeat check
    if(len(class_id)!=7):
        # print()
        return 0,'error! The class ID must be 7 digits!'
    sql='SELECT * FROM classes WHERE ID=\''+class_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print()
            return 0,'repeat id'
    except:
        # print()
        return 0,'error! add_class-legal and repeat check. raw sql:'+sql
    
    '''
    insert into classes table
    '''
    sql='INSERT INTO classes(ID,name) VALUES(\''+class_id+'\',\''+class_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'add classes error! raw sql:'+sql

    '''
    insert into class_in_school relationship
    '''
    sql='INSERT INTO class_in_school(classID,schoolID) VALUES(\''+class_id+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'add class_in_school relationship error! raw sql:'+sql
    return 1,1

def del_class(cursor,db,class_id):

   #legal and exist check
    if(len(class_id)!=7):
        # print()
        return 0,'error! The class ID must be 7 digits!'
    sql='SELECT * FROM classes WHERE ID=\''+class_id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'class with id '+class_id+' does not exist'
    except:
        # print()
        return 0,'error! del_class-legal and exist check. raw sql:'+sql
    
    
    '''
    check if have student
    '''
    sql='SELECT * FROM in_class WHERE classID=\''+class_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print()
            return 0,'There are students in the class that cannot be deleted'
    except:
        # print('error! del_class-check if have student. raw sql:',sql)
        return 0,'error! del_class-check if have student. raw sql:'+sql
    
    '''
    del classes class_in_school
    '''
    sql='DELETE FROM class_in_school WHERE classID=\''+class_id+'\''
    try:
        cursor.execute(sql)
    except:
        # print()
        db.rollback()
        return 0,'error! del_class-del class_in_school. raw sql:'+sql
    
    sql='DELETE FROM classes WHERE ID=\''+class_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'error! del_class-del classes. raw sql:'+sql
    return 1,1

'''
classrooms_manage
'''
def query_classrooms(cursor,db,id):
    
   
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'School with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! del_school-Legal and Existence check. raw sql:'+sql
    
    '''
    query classroom
    '''
    sql='SELECT * FROM classrooms WHERE ID IN(SELECT classroomID FROM classroom_in_school WHERE schoolID=\''+id+'\')'
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        # print()
        return 0,'query classroom error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]



def add_classroom(cursor,db,id,classroom_id,classroom_name):
    '''
    Legal and Existence check
    '''
    if(len(id)!=3):
        # print()
        return 0,'error! The school ID must be 3 digits!'
    sql='SELECT * FROM school WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'School with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! del_school-Legal and Existence check. raw sql:'+sql
    
    '''
    get classroom ID and name
    '''
    # classroom_id=input('Please enter the 5 ID of the classroom you want to add:')
    #legal and repeat check
    if(len(classroom_id)!=5):
        # print()
        return 0,'error! The classroom ID must be 5 digits!'
    sql='SELECT * FROM classrooms WHERE ID=\''+classroom_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print()
            return 0,'repeat id'
    except:
        # print()
        return 0,'error! add_classroom-legal and repeat check. raw sql:'+sql
    # classroom_name=input('Please enter the address of the classroom you want to add:')
    
    '''
    insert into classrooms table
    '''
    sql='INSERT INTO classrooms(ID,address) VALUES(\''+classroom_id+'\',\''+classroom_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'add classrooms error! raw sql:'+sql

    '''
    insert into classroom_in_school relationship
    '''
    sql='INSERT INTO classroom_in_school(classroomID,schoolID) VALUES(\''+classroom_id+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'add classroom_in_school relationship error! raw sql:'+sql
    return 1,1

def del_classroom(cursor,db,classroom_id):
    #legal and exist check
    if(len(classroom_id)!=5):
        # print('error! The teacher ID must be 10 digits!')
        return 0,'error! The classroom ID must be 5 digits!'
    sql='SELECT * FROM classrooms WHERE ID=\''+classroom_id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'classroom with id '+classroom_id+' does not exist'
    except:
        # print()
        return 0,'error! del_classroom-legal and exist check. raw sql:'+sql
    
    '''
    check is occupied
    '''
    sql='SELECT * FROM occupation WHERE classroomID=\''+classroom_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print()
            return 0,'Classroom occupied'
    except:
        # print()
        return 0,'error! del_classroom-check is occupied. raw sql:'+sql
    
    '''
    del classroom_in_school classrooms
    '''
    sql='DELETE FROM classroom_in_school WHERE classroomID=\''+classroom_id+'\''
    try:
        cursor.execute(sql)
    except:
        # print()
        db.rollback()
        return 0,'error! del_classroom-del classroom_in_school. raw sql:'+sql
    
    sql='DELETE FROM classrooms WHERE ID=\''+classroom_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print('error! del_classroom-del classrooms. raw sql:',sql)
        db.rollback()
        return 0,'error! del_classroom-del classrooms. raw sql:'+sql
    return 1,1


def query_lib(cursor,db):
    sql='SELECT * FROM libraries'
    schools=None
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        return 0,'query school error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]

def book_query(cursor,db,id):
    '''
    Legal and Existence check
    '''
    if(len(id)!=5):
        # print()
        return 0,'error! The library ID must be 5 digits!'
    sql='SELECT * FROM libraries WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print('library with id ',id,' does not exist')
            return 0,'library with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_books-Legal and Existence check. raw sql:'+sql
    
    '''
    query books
    '''
    sql='SELECT * FROM books WHERE ID IN(SELECT bookID FROM store WHERE libraryID=\''+id+'\')'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
    except:
        # print()
        return 0,'query book error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(books)):
        schools_id.append(books[i][0])
        schools_name.append(books[i][1])
    return 1,[schools_id,schools_name]

def add_book(cursor,db,id,book_id,book_name):
    '''
    Legal and Existence check
    '''
    if(len(id)!=5):
        # print()
        return 0,'error! The library ID must be 5 digits!'
    sql='SELECT * FROM libraries WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            print()
            return 0,'library with id '+id+' does not exist'
    except:
        # print('error! query_books-Legal and Existence check. raw sql:',sql)
        return 0,'error! query_books-Legal and Existence check. raw sql:'+sql
    #check
    if(len(book_id)!=10):
        # print()
        return 0,'error! The book ID must be 10 digits!'
    '''
    get book in books
    '''
    booksID_list=[]
    booksname_list=[]
    sql='SELECT * FROM books'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
        for i in range(len(books)):
            booksID_list.append(books[i][0])
            booksname_list.append(books[i][1])
    except:
        # print()
        return 0,'error! query_books-get book in books. raw sql:'+sql
    
    '''
    check is a new book
    '''
    if(book_id not in booksID_list):
        sql='INSERT INTO books(ID,name) VALUES(\''+book_id+'\',\''+book_name+'\')'
        try:
            cursor.execute(sql)
        except:
            # print()
            db.rollback()
            return 0,'error! add_book-check is a new book. raw sql:'+sql
    '''
    insert into store
    '''
    sql='INSERT INTO store(bookID,libraryID) VALUES(\''+book_id+'\',\''+id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'error! add_book-insert into store. raw sql:'+sql
    return 1,1

def del_book(cursor,db,id,book_id):
    
    '''
    Legal and Existence check
    '''
    if(len(id)!=5):
        # print()
        return 0,'error! The library ID must be 3 digits!'
    sql='SELECT * FROM libraries WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'library with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_books-Legal and Existence check. raw sql:'+sql
    '''
    get del book id 
    '''
    #check
    if(len(book_id)!=10):
        # print()
        return 0,'error! The book ID must be 10 digits!'
    sql='SELECT * FROM store WHERE libraryID=\''+id+'\' AND bookID=\''+book_id+'\''
    try:
        if(cursor.execute(sql)==0):
            # print('error! The book with ID '+book_id+' does not exist in the library with ID ',id)
            return 0,'error! The book with ID '+book_id+' does not exist in the library with ID '+id
    except:
        # print('error! del_book-check. raw sql:',sql)
        return 0,'error! del_book-check. raw sql:'+sql

    
    
    '''
    check is be borrowed
    '''
    sql='SELECT * FROM borrow_book WHERE bookID=\''+book_id+'\''
    try:
        if(cursor.execute(sql)!=0):
            # print('error! The book with ID '+book_id+' is borrowed')
            return 0,'error! The book with ID '+book_id+' is borrowed'
    except:
        # print('error! del_book-check is be borrowed. raw sql:',sql)
        return 0,'error! del_book-check is be borrowed. raw sql:'+sql
    '''
    del store
    '''
    sql='DELETE FROM store WHERE libraryID=\''+id+'\' AND bookID=\''+book_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback() 
        return 0,'error! del_book-del store. raw sql:'+sql
    return 1,1
'''
teacher course management
'''
def query_course(cursor,db,id):
   
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The teacher ID must be 10 digits!'
    sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'teacher with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_course-Legal and Existence check. raw sql:'+sql
    
    '''
    query courses
    '''
    sql='SELECT * FROM courses WHERE ID IN(SELECT courseID FROM teach_course WHERE teacherID=\''+id+'\' )'
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        # print()
        return 0,'query course error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]
    
    
    
    
    
def add_course(cursor,db,id,course_id,course_name,classroom_id):
   
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The teacher ID must be 10 digits!'
    sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print('teacher with id ',id,' does not exist')
            return 0,'teacher with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_course-Legal and Existence check. raw sql:'+sql
    
    '''
    get new course ID and name
    '''
    # course_id=input('Please enter the 5 digit ID of the course you want to add:')
    '''
    Legal and repeat check
    '''
    if(len(course_id)!=5):
        # print()
        return 0,'error! The course ID must be 5 digits!'
    sql='SELECT * FROM courses WHERE ID=\''+course_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print()
            return 0,'repeat id'
    except:
        # print()
        return 0,'error! add_course-Legal and Existence check. raw sql:'+sql
    # course_name=input('Please enter the name of the course you want to add:')
    sql='SELECT * FROM courses WHERE name=\''+course_name+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print()
            return 0,'repeat name'
    except:
        # print()
        return 0,'error! add_course-Legal and Existence check-name. raw sql:'+sql
    
    '''
    get classroom
    '''
    #get schoolID
    school_id=''
    sql='SELECT schoolID FROM teach WHERE teacherID=\''+id+'\''
    try:
        cursor.execute(sql)
        school_id=cursor.fetchall()[0][0]
    except:
        # print()
        return 0,'error!add_course-get schoolID. raw sql:'+sql
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
        # print()
        return 0,'query classroom error! raw sql:'+sql
    # print('The free classrooms are as follows')
    # for i in range(len(classroomsID_list)):
    #     print(classroomsID_list[i],classroomsname_list[i])
    
    # classroom_id=('Please enter the 5 digit ID number of the classroom that the course needs to occupy:')
    '''
    Legal and Existence check
    '''
    if(len(classroom_id)!=5):
        # print()
        return 0,'error! The classroom ID must be 5 digits!'
    if(classroom_id not in classroomsID_list):
        # print()
        return 0,'error! The classroom ID not exist!'
    
    
    
    '''
    insert into courses teach_course occupation
    '''
    sql='INSERT INTO courses(ID,name) VALUES(\''+course_id+'\',\''+course_name+'\')'
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'add courses error! raw sql:'+sql
    
    sql='INSERT INTO occupation(courseID,classroomID) VALUES(\''+course_id+'\',\''+classroom_id+'\')'
    try:
        cursor.execute(sql)
        
    except:
        # print('add occupation relationship error! raw sql:',sql)
        db.rollback()
        return 0,'add occupation relationship error! raw sql:'+sql
    
    sql='INSERT INTO teach_course(teacherID,courseID) VALUES(\''+id+'\',\''+course_id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'add teach_course relationship error! raw sql:'+sql
    return 1,1
    
def del_course(cursor,db,id,course_id):
   
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The teacher ID must be 10 digits!'
    sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print('teacher with id ',id,' does not exist')
            return 0,'teacher with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_course-Legal and Existence check. raw sql:'+sql

    
    
    '''
    get course id
    '''
    # course_id=input('Please enter the 5 digit ID of the course you want to add:')
    '''
    Legal and exist check
    '''
    if(len(course_id)!=5):
        # print()
        return 0,'error! The course ID must be 5 digits!'
    sql='SELECT * FROM courses WHERE ID=\''+course_id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'course with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! del_course-Legal and exist check1. raw sql:'+sql
    sql='SELECT * FROM teach_course WHERE teacherID=\''+id+'\' AND courseID=\''+course_id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'Teachers with ID '+id+' do not teach courses with ID '+course_id
    except:
        # print()
        return 0,'error! del_course-Legal and exist check2. raw sql:'+sql
    
    '''
    check is be selected
    '''
    sql='SELECT * FROM elective WHERE courseID=\''+course_id+'\''
    try:
        if (cursor.execute(sql)!=0):
            # print('course with ID ',course_id,' is selected')
            return 0,'course with ID '+course_id+' is selected'
    except:
        print('error! del_course-check is be selected. raw sql:',sql)
        return 0,'error! del_course-check is be selected. raw sql:'+sql
    
    '''
    del occupation teach_course courses
    '''
    sql='DELETE FROM occupation WHERE courseID=\''+course_id+'\''
    try:
        cursor.execute(sql)
        
    except:
        # print('error! del_course-del occupation. raw sql:',sql)
        db.rollback()
        return 0,'error! del_course-del occupation. raw sql:'+sql
    
    sql='DELETE FROM teach_course WHERE courseID=\''+course_id+'\''
    try:
        cursor.execute(sql)
        
    except:
        # print()
        db.rollback()
        return 0,'error! del_course-del teach_course. raw sql:'+sql
    
    sql='DELETE FROM courses WHERE ID=\''+course_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print('error! del_course-del course. raw sql:',sql)
        db.rollback()
        return 0,'error! del_course-del course. raw sql:'+sql
    return 1,1
    
def free_classroom_query(cursor,db,id):
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The teacher ID must be 10 digits!'
    sql='SELECT * FROM teachers WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print('teacher with id ',id,' does not exist')
            return 0,'teacher with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_course-Legal and Existence check. raw sql:'+sql
    #get schoolID
    schoolid=''
    sql='SELECT schoolID FROM teach WHERE teacherID=\''+id+'\''
    try:
        cursor.execute(sql)
        school_id=cursor.fetchall()[0][0]
    except:
        # print()
        return 0,'error!fcr_q-get schoolID. raw sql:'+sql
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
        # print()
        return 0,'query classroom error! raw sql:'+sql
    return 1,[classroomsID_list,classroomsname_list]
    
    
'''
student affairs management
'''
#course
def query_selected_courses(cursor,db,id):    
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_selected_courses-Legal and Existence check. raw sql:'+sql
    
    
    '''
    query
    '''
    sql='SELECT * FROM courses WHERE ID IN(SELECT courseID FROM elective WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        # print()
        return 0,'query selected courses error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]

def select_course(cursor,db,id,courses_id):
        
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_selected_courses-Legal and Existence check. raw sql:'+sql

    
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
        # print()
        return 0,'error!select_course-get courseID that can be selected. raw sql:'+sql
    #get courses list
    coursesID_list=[]
    coursesname_list=[]
    sql='SELECT * FROM courses WHERE ID IN(SELECT courseID FROM teach_course WHERE teacherID IN(SELECT teacherID FROM teach WHERE schoolID=\''+school_id+'\' )) AND ID NOT IN(SELECT courseID FROM elective WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        courses=cursor.fetchall()
        # print(courses)
        for i in range(len(courses)):
            coursesID_list.append(courses[i][0])
            coursesname_list.append(courses[i][1])
    except:
        # print()
        return 0,'error!select_course-get courses list. raw sql:'+sql
    # print('The courses can be selected are as follows:')
    # print(coursesID_list)
    # print(coursesname_list)
    # return
    # for i in range(len(coursesID_list)):
    #     print(coursesID_list[i],coursesname_list[i])    
    
    
    
    # courses_id=input('Please enter the 5-digit ID of the course you want to select:')
    '''
    Legal and Existence check
    '''
    if(len(courses_id)!=5):
        # print()
        return 0,'error! The course ID must be 5 digits!'
    if(courses_id not in coursesID_list):
        # print()
        return 0,'error! The course ID not exist!'
    
    '''
    insert into elective
    '''
    sql='INSERT INTO elective(studentID,courseID) VALUES(\''+id+'\',\''+courses_id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print()
        db.rollback()
        return 0,'error!select course-insert into elective. raw sql:'+sql
    return 1,1
    
    
    
    
def drop_course(cursor,db,id,courses_id):
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_selected_courses-Legal and Existence check. raw sql:'+sql
    
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
        # print()
        return 0,'error!drop_course-get courseID that can be dropped. raw sql:'+sql
    # print('The courses can be dropped are as follows:')
    # for i in range(len(coursesID_list)):
        # print(coursesID_list[i],coursesname_list[i])    
    
    
    
    # courses_id=input('Please enter the 5-digit ID of the course you want to drop:')
    '''
    Legal and Existence check
    '''
    if(len(courses_id)!=5):
        # print()
        return 0,'error! The course ID must be 5 digits!'
    if(courses_id not in coursesID_list):
        # print()
        return 0,'error! The course ID not exist!'
    
    '''
    del elective
    '''
    sql='DELETE FROM elective WHERE studentID=\''+id+'\' AND courseID=\''+courses_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        print()
        db.rollback()
        return 0,'drop course_del elective error! raw sql:'+sql
    return 1,1


def free_courses_query(cursor,db,id):
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! fc_query-Legal and Existence check. raw sql:'+sql

    
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
        # print()
        return 0,'error!fc_query-get courseID that can be selected. raw sql:'+sql
    #get courses list
    coursesID_list=[]
    coursesname_list=[]
    sql='SELECT * FROM courses WHERE ID IN(SELECT courseID FROM teach_course WHERE teacherID IN(SELECT teacherID FROM teach WHERE schoolID=\''+school_id+'\' )) AND ID NOT IN(SELECT courseID FROM elective WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        courses=cursor.fetchall()
        # print(courses)
        for i in range(len(courses)):
            coursesID_list.append(courses[i][0])
            coursesname_list.append(courses[i][1])
    except:
        # print()
        return 0,'error!fc_query-get courses list. raw sql:'+sql
    return 1,[coursesID_list,coursesname_list]

#book
def query_borrow_books(cursor,db,id):
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_selected_courses-Legal and Existence check. raw sql:'+sql

    
    '''
    query
    '''
    sql='SELECT * FROM books WHERE ID IN(SELECT bookID FROM borrow_book WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        schools=cursor.fetchall()
    except:
        # print()
        return 0,'query borrow books error! raw sql:'+sql
    schools_id=[]
    schools_name=[]
    for i in range(len(schools)):
        schools_id.append(schools[i][0])
        schools_name.append(schools[i][1])
    return 1,[schools_id,schools_name]

def borrow_book(cursor,db,id,book_id):
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_selected_courses-Legal and Existence check. raw sql:'+sql

    
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
        # print()
        return 0,'error!borrow_book-get school_id. raw sql:'+sql
    booksID_list=[]
    booksname_list=[]
    sql='SELECT * FROM books WHERE ID IN(SELECT bookID FROM store WHERE libraryID IN(SELECT libraryID FROM have_library WHERE schoolID=\''+school_id+'\' )) AND ID NOT IN(SELECT bookID FROM borrow_book WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
        # print(courses)
        for i in range(len(books)):
            booksID_list.append(books[i][0])
            booksname_list.append(books[i][1])
    except:
        # print()
        return 0,'error!borrow_book-get bookID that can be borrowed. raw sql:'+sql
    # print('The books can be selected are as follows:')
    # for i in range(len(booksID_list)):
    #     print(booksID_list[i],booksname_list[i])
    
    # book_id=input('Please enter the 10-digit ID of the book you want to borrow:')
    '''
    Legal and Existence check
    '''
    if(len(book_id)!=10):
        # print()
        return 0,'error! The book ID must be 10 digits!'
    if(book_id not in booksID_list):
        # print()
        return 0,'error! The book ID not exist!'
    
    '''
    insert into borrow_book
    '''
    sql='INSERT INTO borrow_book(studentID,bookID) VALUES(\''+id+'\',\''+book_id+'\')'
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'error!borrow_book-insert into borrow_book. raw sql:'+sql
    return 1,1
    

def return_book(cursor,db,id,book_id):
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_selected_courses-Legal and Existence check. raw sql:'+sql
    
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
        # print()
        return 0,'error!return_book-get bookID that can be returned. raw sql:'+sql
    # print('The books can be returned are as follows:')
    # for i in range(len(bookID_list)):
        # print(bookID_list[i],bookname_list[i])
    
    # book_id=input('Please enter the 5-digit ID of the course you want to drop:')
    '''
    Legal and Existence check
    '''
    if(len(book_id)!=10):
        # print()
        return 0,'error! The book ID must be 10 digits!'
    if(book_id not in bookID_list):
        # print()
        return 0,'error! The book ID not exist!'
    
    '''
    del borrow_book
    '''
    sql='DELETE FROM borrow_book WHERE bookID=\''+book_id+'\''
    try:
        cursor.execute(sql)
        db.commit()
    except:
        # print()
        db.rollback()
        return 0,'error!return_book-del borrow_book. raw sql:'+sql
    return 1,1

def fb_query(cursor,db,id):
    '''
    Legal and Existence check
    '''
    if(len(id)!=10):
        # print()
        return 0,'error! The student ID must be 10 digits!'
    sql='SELECT * FROM students WHERE ID=\''+id+'\''
    try:
        if (cursor.execute(sql)==0):
            # print()
            return 0,'student with id '+id+' does not exist'
    except:
        # print()
        return 0,'error! query_selected_courses-Legal and Existence check. raw sql:'+sql

    
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
        # print()
        return 0,'error!borrow_book-get school_id. raw sql:'+sql
    booksID_list=[]
    booksname_list=[]
    sql='SELECT * FROM books WHERE ID IN(SELECT bookID FROM store WHERE libraryID IN(SELECT libraryID FROM have_library WHERE schoolID=\''+school_id+'\' )) AND ID NOT IN(SELECT bookID FROM borrow_book WHERE studentID=\''+id+'\')'
    try:
        cursor.execute(sql)
        books=cursor.fetchall()
        # print(courses)
        for i in range(len(books)):
            booksID_list.append(books[i][0])
            booksname_list.append(books[i][1])
    except:
        # print()
        return 0,'error!borrow_book-get bookID that can be borrowed. raw sql:'+sql
    return 1,[booksID_list,booksname_list]