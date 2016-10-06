#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int age = 10;
	int height = 72;

	// 1) Let's allocate some memory...
	char *stuff = malloc(1024);

	printf("I am %d years old.\n", age);
	printf("I am %d inches tall.\n", height);

	printf("This is a memory address: %p\n", stuff);

	// 2) ... and forget to free the memory back to the OS
	// free(stuff);


	return 0;
}
