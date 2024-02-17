# Directory Organizer

This is a simple C program designed to organize files within a directory based on their extensions. It scans a specified directory, identifies files, and categorizes them into folders based on their file extensions. Additionally, it moves files to their respective folders, creating new folders if necessary.

## Features

- **File Organization**: Files are categorized based on their extensions into separate folders.
- **Folder Creation**: New folders are created automatically for each unique file extension found.
- **File Movement**: Files are moved to their respective folders according to their extensions.
- **Memory Management**: Dynamic memory allocation for efficient resource usage.
- **Error Handling**: Proper error messages are displayed for failed operations.

## Usage

This project can be compiled using either a C compiler directly or using CMake. Here are the steps for both methods:

### Using C Compiler

1. Compile the program using any C compiler. For example:
    ```bash
    gcc -o directory_organizer directory_organizer.c
    ```

2. Run the compiled program with the target directory path as an argument. For example:
    ```bash
    ./directory_organizer /path/to/directory
    ```

3. The program will scan the specified directory, organize files into folders based on their extensions, and move files accordingly.

### Using CMake

1. Remove and create a build directory inside the project directory:
    ```bash
    rm -r build
    mkdir build
    cd build
    ```

2. Generate the build files using CMake:
    ```bash
    cmake ..
    ```

3. Build the project using make:
    ```bash
    make
    ```

4. Run the compiled program with the target directory path as an argument. For example:
    ```bash
    ./directory_organizer /path/to/directory
    ```

5. The program will scan the specified directory, organize files into folders based on their extensions, and move files accordingly.

## Example

Suppose you have a directory named "Files" containing various files:
```bash
Files/
├── document1.txt
├── image.jpg
├── presentation.pptx
├── hello_world.py
├── script.py
└── video.mp4
```

Running the program on this directory will result in the following organization:

```bash
Files/
├── TXT/
│   └── document1.txt
├── JPG/
│   └── image.jpg
├── PPTX/
│   └── presentation.pptx
├── PY/
│   ├── hello_world.py
│   └── script.py
└── MP4/
    └── video.mp4

```

The program should be tested for memory leaks;
Dont use the pogram with the directory `..` or `.` use absolute paths.
