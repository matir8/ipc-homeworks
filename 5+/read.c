#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#include "gen.h"
#include "cyclicBuf.h"

int main()
{
  int memFd = shm_open("shared_memory", O_RDONLY, 0);
  if (memFd == -1)
  {
    perror("Can't open file");
    return 1;
  }

  struct cyclic_buf *mem = mmap(NULL, sizeof(struct cyclic_buf), PROT_READ, MAP_SHARED, memFd, 0);

  if (mem == (void *)-1)
  {
    perror("Can't mmap");
    return -1;
  }

  uint64_t pos = mem->pos;
  printf("starting at %ld\n", pos);
  uint64_t curr = verify((void *)mem->array[pos % 512]);
  uint64_t prev = curr - 1;

  while (true)
  {
    if (mem->pos == pos)
    {
      sleep(1);
      continue;
    }

    curr = verify((void *)mem->array[pos % 512]);

    if (curr == -1)
    {
      printf("Error\n");
      break;
    }

    if (prev == curr - 1)
    {
      printf("Verified %ld\n", curr);
    }

    pos++;
    prev = curr;
  }

  return 0;
}
