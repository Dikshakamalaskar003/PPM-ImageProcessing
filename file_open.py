# open ppm file
with open("matrix1_p3.ppm","r") as fp:
    magic=fp.readline()
    width,height=map(int,fp.readline().split())
    maxval = int(fp.readline().strip())
    print(magic,width,height,maxval)
    #pp = fp.read()
    #print(pp)
    #strore the remaining values in data
    data=list(map(int,fp.read().split()))

#convert the ppm file into greyscale
pixels_grey=[]
k=0
for i in range(height):
    row=[]
    for j in range(width):
        r,g,b=data[k],data[k+1],data[k+2]
        k+=3
        grey=int(0.3*r + 0.59*g + 0.11*b) #greysacle formula
        if grey > 150:
            row.append(1)
        else:
            row.append(0)
    pixels_grey.append(row)    
# #print(pixels_grey)    
rows=len(pixels_grey)
cols=len(pixels_grey[0])
horiz_threshold = int(0.3* cols)   # 30% of width 
#print continuous 1's in in list(horizontal)
row_line=[]
for idx,row in enumerate(pixels_grey):
    found=False
    for val in row:
        if val == 1:
            cont+=1
            if cont >= horiz_threshold:
                found=True
        else:
            cont=0; 
    if found:
        row_line.append(idx) #row_line conain all the row no with have continuous 1's

print("Detected horizontal line rows:", row_line)
print("Total horizontal lines (before merge):", len(row_line))

#mergeing the neighbour 1's line
min_gap = 5 # allow up to 2-pixel spacing between rows of same line
merged_lines_row = []
if row_line:
    start = row_line[0]
    prev = row_line[0]
    for r in row_line[1:]:
        if r - prev > min_gap:
            #merged_lines.append((start, prev))  # store as (start_row, end_row)
            merged_lines_row.append(start)
            start = r
        prev = r
    #merged_lines.append((start, prev))  # last group
    merged_lines_row.append(start)
print("Total Rows :", merged_lines_row)
print("Total merged lines:", len(merged_lines_row))

#---colunm part---
#print continuous 1's line in list (vertical)

col_line=[]
vert_threshold=int(0.1* rows)
for col in range(cols):
    cont=0
    found=False
    for row in range(rows):
        if pixels_grey[row][col] == 1:
            cont+=1
            if cont > vert_threshold:
                found=True
                
        else:
            cont=0
    if found:
        col_line.append(col)
print("Detected vertical line column:", col_line)
print("Total vertical lines (before merge):", len(col_line))

#mergeing the neighbour 1's line
min_gap = 5  
merged_lines_col = []
if col_line:
    start = col_line[0]
    prev = col_line[0]
    for r in col_line[1:]:
        if r - prev > min_gap:
            #merged_lines.append((start, prev))  # store as (start_row, end_row)
            merged_lines_col.append(start)
            start = r
        prev = r
    #merged_lines.append((start, prev))  # last group
    merged_lines_col.append(start)
print("Total Column :", merged_lines_col)
print("Total merged lines:", len(merged_lines_col))

# build the list of corners
corner=[]
for h in  merged_lines_row:
    for v in merged_lines_col:
        corner.append((v,h))
print(corner)        
for (i,j) in corner:
    idx = (h * width + v) * 3
    data[idx] = 255      # R
    data[idx + 1] = 0    # G
    data[idx + 2] = 0    # B

with open("matrix_with_corners_colour.ppm", "w") as fp:
    # Write header
    fp.write("P3\n")
    fp.write(f"{width} {height}\n")
    fp.write(f"{maxval}\n")

    # Write pixel data
    for i in range(0, len(data), 3):
        r = data[i]
        g = data[i + 1]
        b = data[i + 2]
        fp.write(f"{r} {g} {b}")

       
