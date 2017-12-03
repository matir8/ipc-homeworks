#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_WRONLY);
    while(1) {
      char msg[] = "Hello from the other side of the pipe\n";
      write(fd, msg, strlen(msg));
      sleep(1);
    }
    close(fd);

    unlink(myfifo);
    return 0;
}