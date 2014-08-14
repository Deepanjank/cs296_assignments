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
	if len(a[i])==0:
		count=count+1
count=0
for i in range(0,len(a)):
	i=i-count
	if len(a[i])==0:
		print(i)
		a.pop(i)
		count=count+1
sys.stdout.write("title:"+a[0]+"\nauthor:"+a[2]+"\n")


