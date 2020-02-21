#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>

typedef struct node {
	void* value;
	struct node* next;

} Node;

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("expected two arguments, had one\n");
        exit(0);
    }
    if(strlen(argv[1]) == 2 && argv[1][0] == '-') {
        if(argv[1][1] != 'q' && argv[1][1] != 'i' ) {
            printf("invalid sorting flag, expected -i or -q\n");
            exit(0);
        }

    }
    else {
        printf("\"%s\" is not a valid sort flag\n", argv[1]);
        exit(0);
    }
	int fd = open(argv[2], O_RDONLY);
	if(fd==-1) {
        printf("File \"%s\" does not exist or could not be opened\n", argv[2]);
        exit(0);
    }
    printf("works");
	return 0;
}
