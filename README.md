# PPM-Image-Project

# Matrix Grid Detection using PPM (No Libraries)

## Project Overview

This project detects **any matrix dimension (rows × columns)** from a **PPM (P3) image** and generates a **grid image** along with **corner detection**, **without using any external image processing libraries**.

The core advantage of this approach is **reduced computation**, achieved by converting the image into a **binary (0/1) representation** and working directly on raw pixel data.

---

## Key Features

- Automatically detects **any matrix size**
- Uses **pure Python only**
- No OpenCV, PIL, NumPy, or other libraries
- Works directly on **PPM (P3) image format**
- Converts image to **binary** for faster computation
- Detects:
  - Horizontal grid lines
  - Vertical grid lines
  - Corner intersection points
- Generates:
  - Binary grid image
  - Original image with **marked corners**
- Custom implementation of:
  - Line detection
  - Line merging
  - Line drawing algorithm

---

## Core Idea

1. Read raw PPM image file
2. Convert RGB image to grayscale
3. Apply threshold to create a binary image
4. Detect continuous horizontal and vertical lines
5. Merge nearby detected lines
6. Find intersections to identify corners
7. Draw grid lines using detected corners
8. Mark corners on original image
9. Write output images back to PPM format

---

## Why Binary Image?

- Uses only `0` and `1`
- Reduces pixel-level computation
- Faster line detection
- Ideal for structured images like matrices and tables

This makes the algorithm lightweight and efficient.

---

## Input & Output

### Input
- `Matrix2_P3.ppm`  
  PPM (P3) image containing a grid or matrix structure

### Output
- `grid2.ppm`  
  Binary image showing detected grid lines
- `matrix2_marked.ppm`  
  Original image with **yellow dots marking detected corners**

---

## Algorithm Details

### 1. PPM File Parsing
- Reads:
  - Magic number
  - Image width and height
  - Maximum color value
  - Raw RGB pixel data

### 2. Grayscale & Binary Conversion
- Converts RGB to grayscale
- Applies threshold:
  - `1` for bright pixels
  - `0` for dark pixels

### 3. Line Detection
- Horizontal lines:
  - Continuous `1`s across rows
- Vertical lines:
  - Continuous `1`s across columns

### 4. Line Merging
- Merges nearby detected lines
- Avoids multiple detections of thick grid lines

### 5. Corner Detection
- Intersection of merged horizontal and vertical lines
- Automatically adapts to matrix dimensions

### 6. Grid Drawing
- Custom line drawing algorithm
- No external graphics libraries used

### 7. Visualization
- Binary grid image generation
- Corner marking using colored dots

---

##  Advantages

-  No external dependencies
-  Low memory usage
-  Fast execution
-  Works for any matrix size
-  Educational low-level image processing

---

## Use Cases

- Matrix and table detection
- Grid recognition
- Image preprocessing
- Educational image processing projects
- Lightweight computer vision tasks

---

## ▶ How to Run

```bash
python matrix_grid_detector.py
