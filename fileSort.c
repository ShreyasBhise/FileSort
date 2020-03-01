#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<ctype.h>
#include<unistd.h>

typedef struct node {
	void* value;
	struct node* next;

} Node;

void printList(Node* toPrint, int type) {
    Node* ptr = toPrint;
    while(ptr != NULL) {
        if(type == 1)
            printf("%d\n", atoi((char*)(ptr->value)));
        if(type == 2)
            printf("%s\n", (char*)(ptr->value));
        ptr = ptr->next;
    }
    return;
}

/*void printList(Node* toPrint, int type){
    Node* node = toPrint;
    printf("Type is: %s\n", (type == 1) ? "int" : "string");
	while(node!=NULL){
		if(type==2){
			printf("%s", (char *)(node->value));
		} else {
			printf("%d", atoi((char *)(node->value)));
		}
		node = node->next;
		if(node != NULL)
		    printf(" -> ");
	}
	printf("\n");
	return;
} */
void freeList(Node* node) {
    Node* ptr = NULL;
    while(node!= NULL) {
        ptr = node;
        node = node->next;
        free(ptr->value);
        free(ptr);
    }
}

/*  Both comparator functions return
 *  1 if the second is greater, -1 if
 *  the first is greater, and 0 in the
 *  equal case
 */

int intComparator(void* in1, void* in2) {
	int x = atoi((char*)in1);
	int y = atoi((char*)in2);
	if(x > y) return -1;
	else if (x < y) return 1;
	return 0;
}

int stringComparator(void* in1, void* in2) {
	char* str1 = (char*)in1;
	char* str2 = (char*)in2;
	while(*str1 != '\0'  && *str2 != '\0') {
        if(*str1 == *str2) {
            str1++;
            str2++;
        }
        else if(*str1 < *str2)
            return 1;
        else
            return -1;
	}
	if(*str1 == '\0' && *str2 == '\0')
	    return 0;
	else if (*str1 == '\0')
	    return 1;
	return -1;
}

int insertionSort(void* toSort, int (*comparator)(void*, void*)) {
    Node* ptr1 = (Node*) toSort;
    Node* root = (Node*) toSort;
    if(ptr1 == NULL || ptr1->next == NULL) return -1;
    ptr1 = ptr1->next;
    while(ptr1 != NULL) {
        void* data = ptr1->value;
        int found = 0;
        Node* ptr2 =(Node*) toSort;
        while(ptr1 != ptr2) {
            if((*comparator)(ptr1->value, ptr2->value) >= 1 && found == 0) {
                data = ptr2->value;
                ptr2->value = ptr1->value;
                found = 1;
            }
            else if(found == 1){
                void* temp = data;
                data = ptr2->value;
                ptr2->value = temp;
            }
            ptr2 = ptr2->next;
        }
        ptr2->value = data;
        ptr1 = ptr1->next;
    }
    return 0;
}

int quickSort(void* toSort, int (*comparator)(void*, void*)) {
	Node* pivot = (Node*)toSort;
	if(pivot == NULL){
		return -1;
	}
	Node* curr = pivot->next;
	Node* ptr1 = NULL;
	Node* ptr2 = NULL;
	while(curr != NULL){
		Node* next = curr->next;
		if((*comparator)(curr->value, pivot->value) != -1){
			curr->next = ptr1;
			ptr1 = curr;
		} else {
			curr->next = ptr2;
			ptr2 = curr;
		}
		curr = next;
	}
	int x = quickSort((void*)ptr1, (*comparator));
	int y = quickSort((void*)ptr2, (*comparator));
	Node* temp = ptr1;
	void* data = pivot->value;
	if(temp == NULL){
		pivot->next = ptr2;
		return 0;
	}
	pivot->value = temp->value;
	while(temp->next != NULL){
		temp->value = temp->next->value;
		temp = temp->next;
	}
	temp->value = data;
	pivot->next = ptr1;
	temp->next = ptr2;
    return 0;
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
	int size = 10;
	char* str = (char*) malloc(size);
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
		if(c == ','){
            Node* node = (Node*)malloc(sizeof(Node));
            node->value = (void *)malloc(size);
			str[i]='\0';
            if(i == 0) {
                strcpy(node->value, "");
            }
			else {
                strcpy(node->value, str);
            }
			node->next = root;
			root = node;
			i = 0;
			size = 10;
			char* temp = (char *)malloc(size);
			char* temp2 = str;
			str = temp;
			free(temp2);
			continue;
		}
		if(i>=size-1){
			size = size*2;
			char* temp = (char *)malloc(size);
			strcpy(temp, str);
			char* temp2 = str;
			str = temp;
			free(temp2);
		}
		str[i] = c;
		i++;
		
	}
	if(i > 0) {
	    str[i] = '\0';
		Node* node = (Node*)malloc(sizeof(Node));
		node->value = (void *)malloc(size);
		strcpy(node->value, str);
		node->next = root;
		root = node;
	}
	//free(str);
	if(type == 0) {
	    printf("Warning: your file only contains empty tokens.\n");
	}
	int check = 5;
	char sortType = argv[1][1];
	if(type == 1) {
		if(sortType == 'i'){
			check = insertionSort((void *) root, intComparator);
		} else if (sortType == 'q'){
            check = quickSort((void *) root, intComparator);
		}
	} else if (type == 2) {
		if(sortType == 'i'){
            check = insertionSort((void *) root, stringComparator);
		} else if (sortType == 'q') {
            check = quickSort((void * ) root, stringComparator);
		}
	}
    (type != 0) ? printList(root, type) : printList(root, 2);
	freeList(root);
	return 0;
}
