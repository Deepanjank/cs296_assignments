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
for i in range(0,len(a)):
	if a[i]!="":
		til=i
		print(a[i])
		break
print(til)
for i in range (til+1,len(a)):
	if a[i]=="Written by" or a[i]=="By" or a[i]=="by":
		auth=i+2
		break
sys.stdout.write("title:"+a[til]+"\nauthor:"+a[auth]+"\n")


