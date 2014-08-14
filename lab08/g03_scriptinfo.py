import sys
print("Please input file name:")
name=input()
filename = name
txt = open(filename)
a=txt.readlines()
for i in range(len(a)):
	a[i]=a[i].strip()
txt.close()
auth=0
count=0
for i in range(0,len(a)):
	if len(a[i])!=0:
		count=count+1
		if(count==1):
			print("title:"+a[i])
		elif(count==3):
			print("author:"+a[i])
			break


