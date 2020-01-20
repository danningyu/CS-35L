#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
  int fd = open("file.txt", O_RDONLY);
  if (fd < 0) {
    // exit(1);
    perror("open error! ");
  }

  char buf[40];
  int ret = read(fd, buf, 8);
  if (ret < 0) {
    perror("read error!");
  }
  // printf("%s\n", buf);
  write(1, buf, 8);
  write(1,"\n",1);
  read(fd, buf, 8);
  write(1, buf, 8);
  write(1, "\n",1);

  lseek(fd, 0, SEEK_SET);
  read(fd, buf, 8);
  write(1, buf, 8);
  write(1, "\n",1);

  lseek(fd, -2, SEEK_CUR);
  read(fd, buf, 8);
  write(1, buf, 8);
  write(1, "\n",1);

  struct stat st;
  fstat(fd, &st);
  printf("The size of this file is %d\n", st.st_size);


  close(fd);
  return 0;
}
