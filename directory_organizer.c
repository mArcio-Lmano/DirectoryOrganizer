#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <ctype.h>

int isInTheArray(char *target, char *array[], const int length_array){
    for (int i=0; i<length_array; ++i){
        if (strcmp(target, array[i]) == 0){
            return 1;
        }
    }
    return 0;
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


// Define a struct to hold file information including extension and full path
struct FileInfo {
    char *extension;   // File extension (NULL if not present)
    char *full_path;    // Full path of the file
};

struct DirInfo{
    int number_files;
    struct FileInfo *files_info;
    int number_folders;
    char **extensions_folders;
};

struct DirInfo creatDirInfo(struct FileInfo *files_information, const int num_files){
    struct DirInfo info;
    info.number_files = num_files;
    info.files_info = files_information;
    printf("The following files were found: ");
    char *new_folder_buffer[num_files];
    int number_folders = 0;
    for (int i=0; i<num_files; ++i){
        struct FileInfo file = info.files_info[i];
        char *folder = file.extension;
        if (folder == NULL){
            continue;
        }
        int file_in_folder = isInTheArray(folder, new_folder_buffer, number_folders);
        if (!file_in_folder){
            new_folder_buffer[number_folders] = folder;
            number_folders++;

        }
        printf("\tExtension = %s, full path = %s\n", file.extension, file.full_path);
    }
    printf("\n");
    info.number_folders = number_folders;

    info.extensions_folders = (char **)malloc(number_folders * sizeof(char *));

    for (int i=0; i<number_folders; ++i){
        info.extensions_folders[i] = (char *)malloc((strlen(new_folder_buffer[i]) + 1) * sizeof(char));
        strcpy(info.extensions_folders[i], new_folder_buffer[i]);
    }
    

    return info;
}


/// Function to check extension and return both extension and full path
struct FileInfo creatFileInfo(const char *full_path, const struct stat *path_stat) {
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

    char *folder_to_be_created[entries_counter];
    int number_of_folder_to_be_created = 0;
    while ((entry = readdir(dir)) != NULL && file_index < entries_counter) {
        // Skip the current directory (".") and parent directory ("..")
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // snprintf(folder_to_be_created)


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
            files_information[file_index] = creatFileInfo(dynamic_full_path, &path_stat);
            if (files_information[file_index].extension == NULL){
                folder_to_be_created[number_of_folder_to_be_created] = strdup(entry->d_name);
                number_of_folder_to_be_created++;
            }
            file_index++;


            // Free dynamically allocated memory for full_path
            free(dynamic_full_path);
        }
    }   
    rewinddir(dir);
    struct DirInfo dir_info = creatDirInfo(files_information, entries_counter);
    // printDirInfo(dir_info);



    printf("Folders to be created: ");
    int folders_created = 0;
    for (int i=0; i<dir_info.number_folders; ++i){
        int directory_found = isInTheArray(dir_info.extensions_folders[i], folder_to_be_created, number_of_folder_to_be_created);
        if (!directory_found){
            printf("\t%s\t", dir_info.extensions_folders[i]);
            char full_path[PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, dir_info.extensions_folders[i]);
            mkdir(full_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);
        }
    }
    if (folders_created == 0){
        printf("\tNone\n");
    }

    for (int i=0; i<dir_info.number_files; i++){
        struct FileInfo file = dir_info.files_info[i];
        if (file.extension != NULL){
            char *file_name = strrchr(file.full_path, '/')+1;

            char new_path[PATH_MAX];
            snprintf(new_path, sizeof(new_path), "%s/%s/%s", path, file.extension, file_name);
            rename(file.full_path, new_path);
            printf("%s\n", new_path);
        }
    }
    
    /////////////////
    // Free Memory //
    /////////////////
    printf("\n");

    for (int i = 0; i < file_index; ++i) {
        // printf("File %d: extension = %s, full path = %s\n", i + 1, files_information[i].extension, files_information[i].full_path);
        free(files_information[i].extension);
        free(files_information[i].full_path);
    }
    free(files_information);
    for (int i = 0; i < dir_info.number_folders; ++i){
        free(dir_info.extensions_folders[i]);
    }
    free(dir_info.extensions_folders);
    // Close the directory
    closedir(dir);

    return 0;
}
