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

// Both comparator functions return
// 1 if the second is greater, -1 if
// the first is greater, and 0 in the
// equal case

int intComparator(void* in1, void* in2) {
	int x = atoi((char*)in1);
	int y = atoi((char*)in2);
	if(x>y) return -1;
	else if (x<y) return 1;
	return 0;
}

int stringComparator(void* in1, void* in2) {
	char* str1 = (char*)in1;
	char* str2 = (char*)in2;
	return 0;
}

int insertionSort(void* toSort, int (*comparator)(void*, void*)) {
	Node* oldroot = (Node*)toSort;
	Node* newroot = NULL;
	if(oldroot==NULL) return -1;
	while(oldroot!=NULL){
		Node* nextNode = oldroot->next;
		int added = 0;
		Node* temp = newroot;
		Node* prev = NULL;
		while(temp!=NULL){
			if((*comparator)(oldroot->value, temp->value)!=-1){
				if(prev!=NULL){
					prev->next = oldroot;
				} else {
					newroot = oldroot;	
				}
				oldroot->next = temp;
				added = 1;
				break;
			} else {
				prev = temp;
				temp = temp->next;
			}
		}
		if(added==0){
			temp = oldroot;
			temp->next = NULL;
		}
		oldroot = nextNode;
	}
	printList(newroot, 1);
    return 0;
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
	int check = 5;
	char srt = argv[1][1];
	if(type==1) {
		int (*comparator)(void*, void*) = &intComparator;
		if(srt=='i'){
			check = insertionSort((void *)root, (*comparator));
		} else if (srt=='q'){

		}
	} else if (type==2) {
		int (*comparator)(void*, void*) = &stringComparator;
		if(srt=='i'){

		} else if (srt=='q') {

		}
	}		
	printList(root, type);
	if(type==1){
		printf("%d -  %d -> %d\n", atoi((char *)(root->next->value)), atoi((char *)(root->next->next->value)), intComparator(root->next->value, root->next->next->value));
	}
	freeList(root);
	return 0;
}
