import sys
print("Please input file name:")
name=input()
filename = name
txt = open(filename)
a=txt.readlines()
for i in range(len(a)):
        a[i]=a[i].strip()
txt.close()
char=[]
for i in range (len(a)):
	temp=True
	if len(a[i])!=0:
		for j in range(len(a[i])-1):
			if a[i][j]=="Mr." or a[i][j]=="Mrs." or a[i][j]=="Dr." or a[i][j]=="DR." or a[i][j]=="Miss" or a[i][j]=="MR." or a[i][j]=="MRS." or a[i][j]=="MISS":
				char.append(a[i][j+1])
				print("deepanjan")
			elif not(a[i][j].isupper()):
				temp=temp and False 
		j=len(a[i])-1
		if a[i][j]=="Mr." or a[i][j]=="Mrs." or a[i][j]=="Dr." or a[i][j]=="DR." or a[i][j]=="Miss" or a[i][j]=="MR." or a[i][j]=="MRS." or a[i][j]=="MISS":	
			char.append(a[i+1][0])
		if temp:
			char.append(a[i])
print(char)
