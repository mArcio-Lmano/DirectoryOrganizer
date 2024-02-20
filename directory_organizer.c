#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <ctype.h>

// Function to check if a string exists in an array of strings
int isInArray(const char *target, char *array[], const int length_array) {
    for (int i = 0; i < length_array; ++i) {
        if (strcmp(target, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Struct to hold file information including extension and full path
struct FileInfo {
    char *extension;   // File extension (NULL if not present)
    char *full_path;   // Full path of the file
};

// Struct to hold directory information
struct DirInfo {
    int number_files;
    struct FileInfo *files_info;
    int number_folders;
    char **extensions_folders;
};

// Function to count the number of entries (files and directories) within a directory
int countEntries(const char *path) {
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

// Function to create directory information
struct DirInfo createDirInfo(struct FileInfo *files_information, const int num_files) {
    struct DirInfo info;
    info.number_files = num_files;
    info.files_info = files_information;

    printf("\nThe following files were found:");

    int num_of_files = 0;
    char *new_folder_buffer[num_files];
    int num_folders = 0;

    // Iterate through files and extract extensions
    for (int i = 0; i < num_files; ++i) {
        struct FileInfo file = info.files_info[i];
        char *folder = file.extension;

        if (folder == NULL) {
            continue;
        }

        int file_in_folder = isInArray(folder, new_folder_buffer, num_folders);

        if (!file_in_folder) {
            new_folder_buffer[num_folders] = folder;
            num_folders++;
        }
        num_of_files++;
        printf("\n\tExtension = %s, full path = %s", file.extension, file.full_path);
    }

    if (num_of_files == 0) {
        printf("\tNone");
    }
    info.number_folders = num_folders;

    info.extensions_folders = (char **)malloc(num_folders * sizeof(char *));

    for (int i = 0; i < num_folders; ++i) {
        info.extensions_folders[i] = (char *)malloc((strlen(new_folder_buffer[i]) + 1) * sizeof(char));
        strcpy(info.extensions_folders[i], new_folder_buffer[i]);
    }

    return info;
}

// Function to create file information
struct FileInfo createFileInfo(const char *full_path, const struct stat *path_stat) {
    struct FileInfo info;

    // Extract file extension
    char *file_extension = strrchr(full_path, '.');
    int extension_buffer_size = 0;

    if (file_extension != NULL) {
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

    // Allocate memory for full path and copy the content
    info.full_path = strdup(full_path);
    if (info.full_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Check if the entry is a directory
    if (S_ISDIR(path_stat->st_mode)) {
        printf("\t%s is a directory.\n", full_path);
    } else if (S_ISREG(path_stat->st_mode)) { // Check if the entry is a regular file
        if (info.extension) {
            printf("\t%s is a regular file with extension: %s\n", info.full_path, info.extension);
        } else {
            printf("\t%s is a regular file with no extension.\n", info.full_path);
        }
    } else { // If the entry is neither a directory nor a regular file
        printf("\t%s is neither a directory nor a regular file.\n", info.full_path);
    }

    return info;
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

    // Count the number of entries in the directory
    int entries_count = countEntries(path);
    printf("Entries Count: %i\n", entries_count);

    // Allocate memory for storing file information
    struct FileInfo *files_information = (struct FileInfo *)malloc(entries_count * sizeof(struct FileInfo));
    if (files_information == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Iterate over each entry in the directory
    int file_index = 0;

    char *folders_to_create[entries_count];
    int num_folders_to_create = 0;

    while ((entry = readdir(dir)) != NULL && file_index < entries_count) {
        // Skip the current directory (".") and parent directory ("..")
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Build the full path of the entry
            char full_path[PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

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
                // Free dynamically allocated memory
                free(dynamic_full_path);
                continue;
            }

            // Save file information
            files_information[file_index] = createFileInfo(dynamic_full_path, &path_stat);

            // If it's a directory, add it to the list of folders to create
            if (files_information[file_index].extension == NULL) {
                folders_to_create[num_folders_to_create] = strdup(entry->d_name);
                num_folders_to_create++;
            }
            file_index++;

            // Free dynamically allocated memory for full_path
            free(dynamic_full_path);
        }
    }


    // Reset directory stream position to the beginning
    rewinddir(dir);

    // Create directory information
    struct DirInfo dir_info = createDirInfo(files_information, entries_count);

    printf("\n\nFolders to be created: ");
    int folders_created = 0;

    // Create folders based on extensions
    for (int i = 0; i < dir_info.number_folders; ++i) {
        int directory_found = isInArray(dir_info.extensions_folders[i], folders_to_create, num_folders_to_create);
        if (!directory_found) {
            printf("\t%s\t", dir_info.extensions_folders[i]);
            char full_path[PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, dir_info.extensions_folders[i]);
            mkdir(full_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);
            folders_created++;
        }
    }
    if (folders_created == 0) {
        printf("\tNone\n");
    }
    printf("\nDo you wish to move the files? [Y/n]\n");
    char user_answer;
    scanf(" %c", &user_answer); 
    
    if (user_answer == 'Y' || user_answer == 'y') {
        printf("\nFiles moved:");
        int number_of_files_moved = 0;
        // Move files into folders based on their extensions
        for (int i = 0; i < dir_info.number_files; i++) {
            struct FileInfo file = dir_info.files_info[i];
            if (file.extension != NULL) {
                char *file_name = strrchr(file.full_path, '/') + 1;
                char new_path[PATH_MAX];
                snprintf(new_path, sizeof(new_path), "%s/%s/%s", path, file.extension, file_name);
                rename(file.full_path, new_path);
                printf("\n\t%s ====> %s", file.full_path, new_path);
                number_of_files_moved++;
            }
        }
        if (number_of_files_moved == 0){
            printf("\tNone\n");
        }
    } else if (user_answer == 'N' || user_answer == 'n') {
        return 0;
    } else {
        // Invalid input
        printf("Invalid input\n");
        return 1;
    }

    // Close the directory
    closedir(dir);

    // Free dynamically allocated memory
    printf("\n");
    for (int i = 0; i < file_index; ++i) {
        free(files_information[i].extension);
        free(files_information[i].full_path);
    }
    free(files_information);
    for (int i = 0; i < dir_info.number_folders; ++i) {
        free(dir_info.extensions_folders[i]);
    }
    for (int i = 0; i < num_folders_to_create; ++i) {
        free(folders_to_create[i]);
    }
    free(dir_info.extensions_folders);

    return 0;
}
