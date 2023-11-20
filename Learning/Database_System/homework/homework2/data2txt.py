import pandas as pd

# 读取Excel文件
excel_file = 'Learning/Database_System/homework/homework2/data.xlsx'
xls = pd.ExcelFile(excel_file)

# 读取每个sheet并保存到不同的txt文件
for sheet_name in xls.sheet_names:
    df = xls.parse(sheet_name)
    txt_file = 'Learning/Database_System/homework/homework2/'+sheet_name + '.txt'
    df.to_csv(txt_file, sep='\t', index=False,header=False)

print("数据已保存到txt文件中")
