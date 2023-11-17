import jieba
from collections import Counter
import matplotlib.pyplot as plt
import wordcloud

def load_stopwords(stopwords_dir):
    stopwords = []
    with open(stopwords_dir, "r", encoding="utf8") as file:
        for line in file.readlines():
            stopwords.append(line.strip())
    return stopwords

def count_elements_stop(lst,stopwords):
    count_dict = {}
    for element in lst:
        if element in stopwords:
            continue
        if element in count_dict:
            count_dict[element] += 1
        else:
            count_dict[element] = 1
    return count_dict

def find_top_words(file_name,stops):
    with open(file_name, 'r', encoding='utf8') as file:
        text = file.read()
        text = text.replace('\n', '')
        # print(text)
        words = jieba.lcut(text)
        words = count_elements_stop(words, stops)
        list =[]
        for key, value in Counter(words).most_common(100):
            list.append(key)
        return words,list

def calc_frequency(dicts,list_key):
    new_dict={}
    total_num=0
    for word in dicts.keys() :
        if word in list_key:
            new_dict[word]=dicts[word]
            total_num+=dicts[word]
    for word in new_dict.keys():
        new_dict[word]/=total_num
    return list_key,new_dict

if __name__=='__main__':
    stopword_path='Learning/Big_Data_Intelligence/lab3/stopwords.txt'
    file_20_path='Learning/Big_Data_Intelligence/lab3/20.txt'
    file_19_path='Learning/Big_Data_Intelligence/lab3/19.txt'
    
    stopwords=load_stopwords(stopword_path)
    
    
    file_20_word_dict,file_20_word_list=find_top_words(file_20_path,stopwords)
    file_19_word_dict,file_19_word_list=find_top_words(file_19_path,stopwords)
    
    key_20word_list=[word for word in file_20_word_list if word not in file_19_word_list]
    key_20word_list,frequency=calc_frequency(file_20_word_dict,key_20word_list)
    wc=wordcloud.WordCloud(font_path='STSONG.TTF').fit_words(frequency)
    
    plt.imshow(wc)
    plt.axis("off")
    plt.show()
