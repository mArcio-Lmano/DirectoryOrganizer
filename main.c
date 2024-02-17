#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <ctype.h>

// Define a struct to hold file information including extension and full path
struct FileInfo {
    char *extension;   // File extension (NULL if not present)
    char *full_path;         // Full path of the file
};



/// Function to check extension and return both extension and full path
struct FileInfo checkExtension(const char *full_path, const struct stat *path_stat) {
    struct FileInfo info;

    // Extract file extension
    char *file_extension = strrchr(full_path, '.');
    int extension_buffer_size = 0;
    if (file_extension != NULL){
        extension_buffer_size = strlen(file_extension);
    }
    
    char extension_buffer[extension_buffer_size];  // Buffer to store the extension

    if (file_extension != NULL) {
        // Copy file extension to a new buffer
        strcpy(extension_buffer, file_extension + 1);

        // Convert file extension to uppercase
        for (char *ptr = extension_buffer; *ptr != '\0'; ptr++) {
            *ptr = toupper(*ptr);
        }
        // Assign converted file extension to info struct
        info.extension = strdup(extension_buffer);
        if (info.extension == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    } else {
        // No file extension found
        info.extension = NULL;
    }
    // free(file_extension);

    // Allocate memory for full path and copy the content
    info.full_path = strdup(full_path);
    if (info.full_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Check if the entry is a directory
    if (S_ISDIR(path_stat->st_mode)) {
        printf("\t%s is a directory.\n", full_path);
    } 
    // Check if the entry is a regular file
    else if (S_ISREG(path_stat->st_mode)) {
        if (info.extension) {
            printf("\t%s is a regular file with extension: %s\n", info.full_path, info.extension);
        } else {
            printf("\t%s is a regular file with no extension.\n", info.full_path);
        }
    } 
    // If the entry is neither a directory nor a regular file
    else {
        printf("\t%s is neither a directory nor a regular file.\n", info.full_path);
    }
    return info;
}



int entriesCounter(const char *path) {
    int files_counter = 0;
    struct dirent *entry;
    DIR *dir = opendir(path);

    // Count all entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip current directory (".") and parent directory ("..")
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            files_counter++;
        }
    }
    // Close the directory
    closedir(dir);
    return files_counter;
}

int main(int argc, char **argv) {
    // Check if a directory path is provided as a command-line argument
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    DIR *dir;
    struct dirent *entry;
    char *path = argv[1];

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("Can't Open Dir");
        return 1;
    }

    printf("Files found:\n");

    // Allocate memory for the array
    int entries_counter = entriesCounter(path);
    printf("Entries Count: %i\n", entries_counter);

    struct FileInfo *files_information = (struct FileInfo *)malloc(entries_counter * sizeof(struct FileInfo));

    if (files_information == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Reset directory stream position to the beginning
    rewinddir(dir);

    // Iterate over each entry in the directory
    int file_index = 0;
    while ((entry = readdir(dir)) != NULL && file_index < entries_counter) {
        // Skip the current directory (".") and parent directory ("..")
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Build the full path of the entry
            char full_path[PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s%s", path, entry->d_name);

            // Allocate memory dynamically for full_path
            char *dynamic_full_path = strdup(full_path);
            if (dynamic_full_path == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }

            // Retrieve information about the entry
            struct stat path_stat;
            if (stat(dynamic_full_path, &path_stat) == -1) {
                perror("stat");
                free(dynamic_full_path); // Free dynamically allocated memory
                continue;
            }

            // Save file information
            files_information[file_index] = checkExtension(dynamic_full_path, &path_stat);
            file_index++;

            // Free dynamically allocated memory for full_path
            free(dynamic_full_path);
            // free(full_path);
        }
    }   

    printf("\n");
    for (int i = 0; i < file_index; ++i) {
        printf("File %d: extension = %s, full path = %s\n", i + 1, files_information[i].extension, files_information[i].full_path);
        free(files_information[i].extension);
        free(files_information[i].full_path);
    }

    free(files_information);

    // Close the directory
    closedir(dir);

    return 0;
}
