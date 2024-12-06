# University Management System

A menu-driven C program for managing university students, including functionalities for adding, modifying, searching, and displaying student information. The program also includes statistics and data manipulation features to streamline university administration.

## Features

### Core Functionalities
- **Add Students**: Add one or multiple students with details such as name, date of birth, department, and general score.
- **Display Students**: View students in various sorted orders:
  - By name (ascending/descending).
  - By general score (ascending/descending).
  - Students with passing scores.
- **Edit Students**: Modify a student's information.
- **Delete Students**: Remove a student from the system.
- **Search Students**:
  - By ID.
  - By name.
  - By department.
- **Statistics**:
  - Number of students with scores above a threshold.
  - Top three students.
  - Number of students in each department.
  - Pass rate per department.
  - Average general score per department.

### Data Management
- Predefined departments (`Mathematics`, `Physics`, `Chemistry`, `Economics`, `Computer Science`).
- Input validation and sorting mechanisms.
- Persistent data in memory for session-long operations.

## Requirements
- C Compiler (e.g., GCC).
- Basic understanding of C programming.

## How to Use
1. Clone or download the repository.
2. Compile the program using a C compiler:
   ```bash
   gcc -o university_system university_system.c
