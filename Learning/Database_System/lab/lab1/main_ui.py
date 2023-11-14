import pymysql
from ui import *
import sys

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
    
app = QtWidgets.QApplication(sys.argv)
window = MyWindow(cursor,db)
window.show()

sys.exit(app.exec_())