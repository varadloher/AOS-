/*write a cprogram to map a given file in memory and display the contents of mapped file in reverse*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void display_reverse(const char *mapped, size_t length) {
    // Print the contents in reverse order
    for (size_t i = length; i > 0; i--) {
        putchar(mapped[i - 1]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int fd;
    struct stat fileStat;

    // Open the file
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Get the file size
    if (fstat(fd, &fileStat) == -1) {
        perror("fstat");
        close(fd);
        return EXIT_FAILURE;
    }

    size_t length = fileStat.st_size;

    // Map the file to memory
    char *mapped = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return EXIT_FAILURE;
    }

    // Close the file descriptor as it's no longer needed
    close(fd);

    // Display the contents in reverse
    display_reverse(mapped, length);

    // Unmap the memory
    if (munmap(mapped, length) == -1) {
        perror("munmap");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
