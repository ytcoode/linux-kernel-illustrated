#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define KiB(n) ((size_t)n * 1024)
#define GiB(n) ((size_t)n * 1024 * 1024 * 1024)

int main(int argc, char **argv) {
  printf("pid: %d\n", getpid());

  // 分配10GiB虚拟内存
  size_t len = GiB(10);
  char *p = mmap(NULL, len, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (p == MAP_FAILED) {
    perror("mmap");
    return -1;
  }

  // 为10GiB虚拟内存分配对应的物理内存
  for (size_t i = 0; i < len; i += KiB(4)) {
    *(p + i) = 1;
  }
  printf("%p: %d\n", p, *p);

  // 等待测试
  sleep(1000);
  return 0;
}
