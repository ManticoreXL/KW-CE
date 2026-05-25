#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NUM 100
#define NUM_BLOCKS 1024
#define BLOCK_SIZE 32
#define MAX_FILE_NAME 100
#define FS_STAT "fs_state.dat"

// File entry
typedef struct
{
    char filename[MAX_FILE_NAME];
    int start_block;
    int size;
} FileEnt;

// File system structure
typedef struct
{
    int fat_table[NUM_BLOCKS];
    FileEnt directory[MAX_FILE_NUM];
    char data_area[NUM_BLOCKS * BLOCK_SIZE];
} FileSystem;

// File system instance
FileSystem myfat;

// Control APIs
int create_file(const char *filename);
int write_file(const char *filename, const char *data);
int read_file(const char *filename);
int delete_file(const char *filename);
void list_files(void);

// File system API
void save_file_system(void);
void load_file_system(void);
void execute_cmd(char *cmd, char *filename, char *data, int num);

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("USAGE: ./fat <COMMAND> <ARGS> ...\n");
        exit(1);
    }

    load_file_system();
    execute_cmd(argv[1], argv[2], argv[3], argc);
    save_file_system();
    exit(0);
}

int find_free_block()
{
    for (int i = 0; i < NUM_BLOCKS; i++)
    {
        if (myfat.fat_table[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

int create_file(const char *filename)
{
    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (strcmp(myfat.directory[i].filename, filename) == 0)
        {
            printf("File '%s' already exists.\n", filename);
            return -1;
        }
    }

    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (myfat.directory[i].filename[0] == '\0')
        {
            int free_block = find_free_block();
            if (free_block == -1)
            {
                printf("No free blocks available.\n");
                return -1;
            }
            myfat.fat_table[free_block] = 0xFFFF; // Mark as end of chain
            strcpy(myfat.directory[i].filename, filename);
            myfat.directory[i].start_block = free_block;
            myfat.directory[i].size = 0;
            printf("File '%s' created.\n", filename);
            return 0;
        }
    }
    printf("File system full. Cannot create more files.\n");
    return -1;
}

int write_file(const char *filename, const char *data)
{
    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (strcmp(myfat.directory[i].filename, filename) == 0)
        {
            int current_block = myfat.directory[i].start_block;
            if (current_block == -1)
            {
                printf("File '%s' not initialized. Use create command first.\n", filename);
                return -1;
            }

            int remaining_data = strlen(data);
            int data_offset = 0;
            while (remaining_data > 0)
            {
                int write_size = (remaining_data < BLOCK_SIZE) ? remaining_data : BLOCK_SIZE;
                memcpy(&myfat.data_area[current_block * BLOCK_SIZE], &data[data_offset], write_size);
                data_offset += write_size;
                remaining_data -= write_size;
                myfat.directory[i].size += write_size;

                if (remaining_data > 0)
                {
                    int next_block = find_free_block();
                    if (next_block == -1)
                    {
                        printf("No more free blocks available.\n");
                        return -1;
                    }
                    myfat.fat_table[current_block] = next_block;
                    myfat.fat_table[next_block] = 0xFFFF; // Mark as end of chain
                    current_block = next_block;
                }
            }
            printf("Data written to '%s'.\n", filename);
            return 0;
        }
    }
    printf("File '%s' not found.\n", filename);
    return -1;
}

int read_file(const char *filename)
{
    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (strcmp(myfat.directory[i].filename, filename) == 0)
        {
            int current_block = myfat.directory[i].start_block;
            if (current_block == -1)
            {
                printf("File '%s' not initialized. Use create command first.\n", filename);
                return -1;
            }

            int remaining_size = myfat.directory[i].size;
            printf("Content of '%s': ", filename);

            while (remaining_size > 0)
            {
                int read_size = (remaining_size < BLOCK_SIZE) ? remaining_size : BLOCK_SIZE;
                printf("%.*s", read_size, &myfat.data_area[current_block * BLOCK_SIZE]);
                remaining_size -= read_size;
                current_block = myfat.fat_table[current_block];
            }
            printf("\n");
            return 0;
        }
    }
    printf("File '%s' not found.\n", filename);
    return -1;
}

int delete_file(const char *filename)
{
    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (strcmp(myfat.directory[i].filename, filename) == 0)
        {
            int current_block = myfat.directory[i].start_block;

            while (current_block != 0xFFFF)
            {
                int next_block = myfat.fat_table[current_block];
                myfat.fat_table[current_block] = 0; // Release block
                current_block = next_block;
            }

            myfat.directory[i].filename[0] = '\0';
            printf("File '%s' deleted.\n", filename);
            return 0;
        }
    }
    printf("File '%s' not found.\n", filename);
    return -1;
}

void list_files(void)
{
    printf("Files in the file system:\n");
    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (myfat.directory[i].filename[0] != '\0')
        {
            printf("File: %s, Size: %d bytes\n", myfat.directory[i].filename, myfat.directory[i].size);
        }
    }
}

void save_file_system(void)
{
    FILE *f = fopen(FS_STAT, "wb");
    if (f == NULL)
    {
        printf("Error: Could not save file system state.\n");
        return;
    }
    fwrite(&myfat, sizeof(FileSystem), 1, f);
    fclose(f);
}

void load_file_system(void)
{
    FILE *f = fopen(FS_STAT, "rb");
    if (f == NULL)
    {
        printf("Error: No saved state found. Starting fresh.\n");
        memset(&myfat, 0, sizeof(FileSystem)); // Initialize to zero
        return;
    }
    fread(&myfat, sizeof(FileSystem), 1, f);
    fclose(f);
}

void execute_cmd(char *cmd, char *filename, char *data, int num)
{
    if (strcmp(cmd, "create") == 0)
    {
        if (num != 3)
            printf("USAGE: create <filename>\n");
        else
            create_file(filename);
    }
    else if (strcmp(cmd, "write") == 0)
    {
        if (num != 4)
            printf("USAGE: write <filename> <data>\n");
        else
            write_file(filename, data);
    }
    else if (strcmp(cmd, "read") == 0)
    {
        if (num != 3)
            printf("USAGE: read <filename>\n");
        else
            read_file(filename);
    }
    else if (strcmp(cmd, "delete") == 0)
    {
        if (num != 3)
            printf("USAGE: delete <filename>\n");
        else
            delete_file(filename);
    }
    else if (strcmp(cmd, "list") == 0)
    {
        list_files();
    }
    else
    {
        printf("Invalid command.\n");
    }
}
