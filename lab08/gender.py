import sys

def checkupper(a):
        ans = True
        for i in a:
                ans = ans and (ord(i) < 97 or ord(i) > 122)
        return ans

def checkname(a):
        ans = True
        for i in a :
                ans = ans and not( i in [':', ';', '-', '_', '.', '!', '?', '(', ')', ',', '#' ])
        return ans

f=open('kung_fu_panda.txt')
lines=f.readlines()

for i in range(len(lines)):
        lines[i] = lines[i].strip()
words = []
words.extend(lines)
for i in range(len(lines)):
        words[i] = lines[i].split()

chars = []

for i in range(len(words)):
        if len(words[i]) < 5:
                all_upper = True
                if lines[i].isupper() and checkname(lines[i]) and not(lines[i] in chars) :
                        chars.append(lines[i])


#purifying
chars_l = []
for i in chars:
        chars_l.append(i.lower())
words_l = []
for i in words:
        temp = []
        for j in i:
                temp.append(j.lower())
        words_l.append(temp)


#finding Dr. Mr. Mrs.

tags=['dr.', 'mr.', 'mrs.', 'ms.','miss']

for i in words_l:
        for  j in range(len(i)):
                if i[j] in tags and j != len(i)-1:
                        occurs = False
                        for k in chars_l:
                                if i[j+1] in k:
                                        occurs = True
                                        break
                                if not(occurs) and checkname(i[j+1]):
                                        chars_l.append(i[j+1])
                                if(tag=='mr.'):
                                        gender.append('m')
                                elif(tag=='mrs.' or tag=='ms.' or tag=='miss'):
                                        gender.append('f')
#counting
count = {}
for i in chars_l:
        count[i] = 0

for i in lines:
        for j in chars_l:
                if j in i.lower():
                        count[j]= count[j] + 1
title = 'Despicable me 2'

for i in chars_l:
        if count[i] < 5 or i == title.lower() or i == 'the end':
                count.pop(i)

print(count)

key_words_m=['he','his','him','man','father','brother','dude']
key_words_f=['she','her','girl','lady','wife','mother','sister','daughter']
keym=0
keyf=0
totm=0
totf=0
key=[0,0,0,0,0,0,0,0,0] #he,she,his,her,boy,guy,man,girl,woman
for k in vikas:
        if k in key_words_m:
                totm=totm+1
        elif k in key_words_f:
                totf=totf+1

gender=['undetermined']*len(chars_l)
for i in range(len(chars_l)):
        temp=0
        pre=""
        if gender[i]=='undetermined':
                for j in vikas:
                        if pre=='mr.' and j in chars_l[i]:
                                gender[i]='male'
                                keym=10000
                                break
                        elif (pre=="mrs." or pre=="miss") and j in chars_l[i] :
                                gender[i]='female'
                                keyf=10000
                                break
                        elif j in key_words_
for i in range(len(chars_l)):
	if gender[i]=='u':
		for j in range(len(words_l)):
			if chars_l[i] in words_l[j]:
				for x in words_l[j]:
					if x in key_words_m:
						keym=keym+1;
					elif x in key_words_f:
						keyf=keyf+1;
			for x in words_l[j+1]:
                                        if x in key_words_m:
                                                keym=keym+0.5;
                                        elif x in key_words_f:
                                                keyf=keyf+0.5;
			for x in words_l[j+2]:
                                        if x in key_words_m:
                                                keym=keym+0.25;
                                        elif x in key_words_f:
                                                keyf=keyf+0.25;
                for j in vikas:
                        if pre=='mr.' and j in chars_l[i]:
                                gender[i]='male'
                                keym=10000
                                break
                        elif (pre=="mrs." or pre=="miss") and j in chars_l[i] :
                                gender[i]='female'
                                keyf=10000
                                break
                        elif j in key_words_m and temp>=1:
                                keym+=temp*0.1
                                temp=0
                        elif j in key_words_f and temp>=1:
                                keyf+=temp*0.1
                                temp=0
                        elif j in chars_l[i]:
				temp+=1
			pre=j

			if (keyf*totm>keym*totf):
				gender[i]='f'
			elif (keyf*totm<keym*totf):
				gender[i]='m'	
			else :
				gender[i]='u'
for i in range (len(chars_l)):
	print(chars_l[i]+" , "+gender[i])
				
		
