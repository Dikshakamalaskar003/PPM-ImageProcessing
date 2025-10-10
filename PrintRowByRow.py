pixels = [
    [0,0,0,0],
    [0,1,1,1],
    [0,0,0,0],
    [0,1,1,1],
    [0,0,0,0],
    [0,0,0,0]
]
# for row in pixels:
#     for value in row:
#        print(value, end=" ")
#     print()
#     print()
#     print()
#print col by col
cols=len(pixels[0])
count=0
rows=len(pixels)
for col in range(cols):
    for row in range(rows):
        print(pixels[row][col],end=" ")
    print() 
    count+=1
print(count)
#print how many row having continuous 1's sequence
# for i in pixels:
#     cont=0
#     found=False
#     for val in i:
#         if val==1:
#             cont+=1
#             if cont >= 3:
#                 found=True
#                 break
#         else:
#             cont=0
#     if found:
#         print("row",i," is horizontal line")    
#     #print how many column having continuous 1's sequence
#     for i in range((len(pixels[0]))):
#         cont=0
#         found=False
#         for j in range(len(pixels)):
#             if pixels[i][j] == 1:
#                 cont+=1
#                 if cont >= 3:
#                     found=True
#                     break
#             else:
#                 cont=0
#         #if found:
#          #   print("column", i ,"is vertical line"
# lines = [12, 15, 45, 100, 104, 108, 300, 450, 800, 804]
# #merge the close line by min_gap
# row_line=1 
# row_list=[]
# min_gap=5
# for i in range(1,len(lines)):
#     if lines[i]-lines[i-1] > min_gap:
#         row_line+=1  
#         row_list.append(lines[i])
          
# print("Row are :",row_line)
# print("Row list :",row_list)
