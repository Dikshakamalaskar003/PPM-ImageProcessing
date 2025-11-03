# open ppm file
with open("Matrix2_P3.ppm","r") as fp:
    magic=fp.readline()
    width,height=map(int,fp.readline().split())
    maxval = int(fp.readline().strip())
    print(magic,width,height,maxval)
    #pp = fp.read()
    #print(pp)
    #strore the remaining values in data
    data=list(map(int,fp.read().split())) #ppm data

#convert the ppm file into greyscale
pixels_grey=[]
k=0
for i in range(height):
    row=[]
    for j in range(width):
        r,g,b=data[k],data[k+1],data[k+2]
        k+=3
        grey=int(r+g+b)/3;        
        #grey=int(0.3*r + 0.59*g + 0.11*b) #greysacle formula
        if grey > 150:
            row.append(1)
        else:
            row.append(0)
    pixels_grey.append(row)    #pixel_greycontain 1/0 data
# #print(pixels_grey)    
rows=len(pixels_grey)
cols=len(pixels_grey[0])
horiz_threshold = int(1/9* cols)   # 30% of width 
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
min_gap = 30# allow up to 2-pixel spacing between rows of same line
merged_lines_row = []
if row_line:
    start = row_line[0]
    prev = row_line[0]
    for r in row_line:
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
vert_threshold=int(1/9* rows)
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
min_gap = 30
merged_lines_col = []
if col_line:
    start = col_line[0]
    prev = col_line[0]
    for r in col_line:
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

    
image=[[0 for _ in range(width)] for _ in range(height)]
def draw_pixel(img, x, y, value=1):
    if 0 <= x < width and 0 <= y < height:
        img[y][x] = value
def draw_line(img, x1, y1, x2, y2, value=1):
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)
    x, y = x1, y1
    sx = 1 if x2 > x1 else -1
    sy = 1 if y2 > y1 else -1
    if dx > dy:
        err = dx // 2
        while x != x2:
            draw_pixel(img, x, y, value)
            err -= dy
            if err < 0:
                y += sy
                err += dx
            x += sx
    else:
        err = dy // 2
        while y != y2:
            draw_pixel(img, x, y, value)
            err -= dx
            if err < 0:
                x += sx
                err += dy
            y += sy
    draw_pixel(img, x, y, value)
cols = len(merged_lines_col)
rows = len(merged_lines_row)

# Reshape to 2D
corner_2d = [corner[i*cols:(i+1)*cols] for i in range(rows)]

# Now this works:
for r in range(rows):
    for c in range(cols - 1):
        x1, y1 = corner_2d[r][c]
        x2, y2 = corner_2d[r][c+1]
        draw_line(image, x1, y1, x2, y2)
# cols = len(merged_lines_col)
# rows = len(merged_lines_row)

# for r in range(rows):
#     for c in range(cols - 1):
#         x11, y11 = corner[r * cols + c]
#         x22, y22 = corner[r * cols + (c + 1)]
#         draw_line(image, x11, y11, x22, y22)

for r in range(rows - 1):
    for c in range(cols):
        x1, y1 = corner_2d[r][c]
        x2, y2 = corner_2d[r+1][c]
        draw_line(image, x1, y1, x2, y2)


with open("grid2.ppm", "w") as f:
    f.write("P3\n")
    f.write(f"{width} {height}\n255\n")
    for row in image:
        for val in row:
            f.write(f"{val*255} {val*255} {val*255} ")  # 0 or 255
        f.write("\n")

#marking corner with colour


# --- Step 4: Build color image again for marking ---
img = []
k = 0
for i in range(height):
    row = []
    for j in range(width):
        r, g, b = data[k], data[k + 1], data[k + 2]
        k += 3
        row.append([r, g, b])  # mutable list for editing
    img.append(row)


# --- Step 5: Function to draw yellow dot (visible corner mark) ---
def draw_dot(img, x, y, radius=4, color=(255, 255, 0)):
    
    for yy in range(y-radius,y+radius+1):
        for xx in range(x-radius,x+radius+1):
                if(xx-x)**2 +(yy-y)**2 <= radius**2:
                    img[yy][xx] = list(color)


#Draw yellow dots for each corner 
for (x, y) in corner:
    draw_dot(img, x, y, radius=5, color=(255, 255, 0))

print("Marked all corners on image")


# --- Step 7: Write the new PPM image ---
with open("matrix2_marked.ppm", "w") as f:
    f.write("P3\n")
    f.write(f"{width} {height}\n255\n")
    for row in img:
        for r, g, b in row:
            f.write(f"{r} {g} {b} ")
        f.write("\n")

print("Output saved as Matrix3_marked.ppm")

