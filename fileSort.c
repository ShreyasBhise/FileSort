#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<ctype.h>

typedef struct node {
	void* value;
	struct node* next;

} Node;

void printList(Node* node, int type){
    printf("Type is: %s\n", (type == 1) ? "int" : "string");
	while(node!=NULL){
		printf("%s", (char *)(node->value));
		node = node->next;
		if(node != NULL)
		    printf(" -> ");
	}
	printf("\n");
	return;
}
void freeList(Node* node) {
    Node* ptr = NULL;
    while(node!= NULL) {
        ptr = node;
        node = node->next;
        free(ptr);
    }
}
int insertionSort(void* toSort, int (*comparator)(void*, void*)) {

    return -1;
}
int quickSort(void* toSort, int (*comparator)(void*, void*)) {

    return -1;
}
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
	if(fd == -1) {
        printf("File \"%s\" does not exist or could not be opened\n", argv[2]);
        exit(0);
    }
	char c;
	int n = 0;
	int type = 0; // type=0 is undeclared, type=1 is int, type=2 is string
	Node* root = NULL;
	char* str = (char*) malloc(1);
	int i = 0;
	while((n = read(fd, &c, 1)) != 0){ // while not end of file
		if(n == -1){
			// wait or something idk
			continue;
		}
		// Ignore all whitespace
		if(isspace(c)) continue;
		// Determine type of data
		if(type == 0){
			if(isdigit(c)) type = 1;
			if(isalpha(c)) type = 2;
		}
		//printf("'%c' %d\n", c, i);
		if(c == ','){
            Node* node = (Node*)malloc(sizeof(Node));
            node->value = (void *)malloc(strlen(str));
            if(i == 0) {
                strcpy(node->value, "");
            }
			else {
                strcpy(node->value, str);
            }
			node->next = root;
			root = node;
			i = 0;
			str = (char*) realloc(str, 1);
			continue;
		}
		str = (char *)realloc(str, i+1);
		str[i] = c;
		str[i+1] = '\0';
		i++;
		
	}
	if(i > 0) {
		Node* node = (Node*)malloc(sizeof(Node));
		node->value = (void *)malloc(strlen(str));
		strcpy(node->value, str);
		node->next = root;
		root = node;
		free(str);
	}

	printList(root, type);
	freeList(root);
	return 0;
}
