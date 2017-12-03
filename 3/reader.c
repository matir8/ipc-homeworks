#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    while (1) {
      read(fd, buf, MAX_BUF);
      write(STDOUT_FILENO, buf, strlen(buf));
    }
    // sleep(10);
    close(fd);

    return 0;
}