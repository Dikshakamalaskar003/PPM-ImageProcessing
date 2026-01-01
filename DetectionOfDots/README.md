# Dot Detection in PPM Image using C (No External Libraries)

## Project Overview

This project implements **bright dot detection** in a **PPM (P3) image** using **pure C**, without relying on any external image processing libraries.  
It detects connected bright regions (dots), filters noise using area thresholding, draws **bounding boxes** around valid dots, and generates a new annotated PPM image.

The solution works directly on raw pixel data and uses a **binary image representation** to reduce computation.

---

## Key Features

- Implemented in **C**
- No OpenCV, PIL, or image libraries
- Works with **PPM (P3) image format**
- Converts RGB image to **binary (0/1)**
- Uses **DFS flood-fill** for connected component detection
- Supports **8-direction connectivity**
- Filters small noisy regions using area threshold
- Draws **yellow bounding boxes** around detected dots
- Outputs a new PPM image with annotations

---

## Core Idea

1. Read raw PPM (P3) image
2. Convert RGB pixels to a binary brightness map
3. Traverse the image to find unvisited bright pixels
4. Use recursive DFS to group connected pixels
5. Track area and bounding box for each group
6. Ignore small regions (noise)
7. Draw bounding boxes on the original image
8. Save the final annotated image

---

## Why Binary Image?

- Simplifies image processing logic
- Reduces computational complexity
- Faster connected component analysis
- Suitable for structured dot detection

```c
if ((r + g + b) / 3 > 200)
    bright[i][j] = 1;
else
    bright[i][j] = 0;
