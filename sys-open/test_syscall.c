#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int handle;
    handle = open("mytest.txt", O_RDONLY);
    close(handle);
    return 0;
}
