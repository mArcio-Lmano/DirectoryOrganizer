# Directory Organizer

This is a simple C program designed to organize files within a directory based on their extensions. It scans a specified directory, identifies files, and categorizes them into folders based on their file extensions. Additionally, it moves files to their respective folders, creating new folders if necessary.

## Features

- **File Organization**: Files are categorized based on their extensions into separate folders.
- **Folder Creation**: New folders are created automatically for each unique file extension found.
- **File Movement**: Files are moved to their respective folders according to their extensions.
- **Memory Management**: Dynamic memory allocation for efficient resource usage.
- **Error Handling**: Proper error messages are displayed for failed operations.

## Usage

1. Compile the program using any C compiler. For example:
    ```bash
    gcc -o directory_organizer directory_organizer.c
    ```

2. Run the compiled program with the target directory path as an argument. For example:
    ```bash
    ./directory_organizer /path/to/directory
    ```

3. The program will scan the specified directory, organize files into folders based on their extensions, and move files accordingly.
