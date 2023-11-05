import requests
from bs4 import BeautifulSoup


response=requests.get('http://www.hgrd.gov.cn/html/2022-10-17/3445.html')
response.encoding='utf-8'
html_content=response.text


soup=BeautifulSoup(html_content,'html.parser')

content = soup.find(id="endtext").getText()
f=open('./20da.txt','w',encoding='utf-8')
f.write(content)
# print(content)