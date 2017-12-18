#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

#include "gen.h"
#include "cyclicBuf.h"

int main()
{
	int memFd = shm_open("shared_memory", O_CREAT | O_RDWR, S_IRWXU);
	if (memFd == -1)
	{
		perror("Can't open file");
		return 1;
	}

	int res = ftruncate(memFd, sizeof(struct cyclic_buf));

	if (res < 0)
	{
		perror("Can't truncate file");
		return res;
	}

	struct cyclic_buf *mem = mmap(NULL, sizeof(struct cyclic_buf), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
	if (mem == (void *)-1)
	{
		perror("Can't mmap");
		return -1;
	}

	int pos = 1;
	uint64_t seed = pos;
	mem->pos = pos - 1;

	while (1){
		mem->pos++;
    generate((void *)mem->array[mem->pos % 512], seed);

		printf("%ld\n", seed);
		seed++;
	}

	return 0;
}
