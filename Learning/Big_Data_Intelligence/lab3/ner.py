from LAC import LAC

file_20_path='Learning/Big_Data_Intelligence/lab3/20.txt'

with open(file_20_path, 'r', encoding='utf8') as file:
    text = file.read()
    text = text.replace('\n', '') #
    lac = LAC(mode='lac')
    lac_result = lac.run(text)
    ner_tag=['PER','LOC','ORG'] #
    result={}
    for(i,tag) in enumerate(lac_result[1]):#整个for循环的功能
        if tag in ner_tag:
            if lac_result[0][i] in result:
                result[lac_result[0][i]] += 1
            else:
                result[lac_result[0][i]] = 1
    print(result)
