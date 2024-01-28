#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // open()
    int file_descriptor = open("stdtext.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) {
        perror("Error opening file");
        exit(1);
    }
    printf("File opened successfully with file descriptor: %d\n", file_descriptor);
    close(file_descriptor);

    // creat()
    file_descriptor = creat("stdtext.txt", O_RDWR);
    if (file_descriptor == -1) {
        perror("Error creating file");
        exit(1);
    }
    printf("File created successfully with file descriptor: %d\n", file_descriptor);
    close(file_descriptor);

    // dup2()
    file_descriptor = open("stdtext.txt", O_RDONLY);
    int new_fd = dup2(file_descriptor, 100);
    printf("Original file descriptor: %d\n", file_descriptor);
    printf("Duplicated file descriptor: %d\n", new_fd);
    close(file_descriptor);
    close(new_fd);

    // dup()
    new_fd = dup(file_descriptor);
    printf("Original file descriptor: %d\n", file_descriptor);
    printf("Duplicated file descriptor: %d\n", new_fd);
    close(file_descriptor);
    close(new_fd);

    // write()
    file_descriptor = open("test.txt", O_CREAT | O_WRONLY, S_IWUSR);
    char write_buffer[] = "Hello, Writing to the file\n";
    ssize_t bytes_written = write(file_descriptor, write_buffer, sizeof(write_buffer) - 1);
    printf("Data Written Successfully!! Wrote %zd bytes to the file\n", bytes_written);
    close(file_descriptor);

    // read()
    file_descriptor = open("test.txt", O_RDONLY);
    char buffer[100];
    ssize_t bytes_read = read(file_descriptor, buffer, sizeof(buffer));
    printf("Read %zd bytes from the file:\n", bytes_read);
    write(STDOUT_FILENO, buffer, bytes_read);
    close(file_descriptor);

    // pipe()
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        exit(1);
    }
    printf("Pipe created with read descriptor: %d and write descriptor: %d\n", pipe_fd[0], pipe_fd[1]);
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    exit(0);
    return 0;
}