#include<stdio.h>
#include<stdlib.h>

struct tree;
typedef struct tree* Node;
typedef struct tree {
	char dirName[20];
	Node child;
	Node brother;
	Node parent;
}_tree;

Node createNewChild(Node, char[20]);
Node createNewBrother(Node, char[20]);
void printDirectory(Node);
Node findNode(Node, char[20]);
void printHelp();

int main() {
	_tree root;
	root.child = NULL;
	root.brother = NULL;
	root.parent = NULL;
	strcpy(root.dirName, "C:");
	Node current = &root;
	char input[5] = "\0";
	char name[20] = "\0";
	Node temp = NULL;
	while (1) {
		printf("Trenutni direktorij: %s\nZa pomoc unesite h\n", current->dirName);
		scanf(" %s", input);
		if (!strcmp(input, "md") && current->child == NULL) {		//md
			printf("Unesite ime direktorija\n");
			scanf("%s", name);
			current->child = createNewChild(current, name);
			

		}

		else if (!strcmp(input, "md") && current->child != NULL) {
			printf("Unesite ime direktorija\n");
			scanf("%s", name);
			current->child->brother = createNewBrother(current->child, name);
		}

		else if (!strcmp(input, "cd")) {						//cd
			temp = current->child;
			if (temp == NULL) {
				printf("Direktroij je prazan\n");
				break;
			}

			printf("U koji direktorij zelite uci?\n");
			scanf("%s", name);
			current = findNode(current, name);
		}

		else if (!strcmp(input, "cd-")) {							//cd-
			if (current->parent != NULL)
				current = current->parent;
			else
				printf("Ovo je pocetni direktorij\n");
		}

		else if (!strcmp(input, "dir"))								//dir
			printDirectory(current);

		else if (!strcmp(input, "exit"))							//izlaz
			break;

		else if (!strcmp(input, "h"))								//pomoc
			printHelp();

		else
			printf("Nepoznata naredba, za pomoc pritisnite h\n");
	}

	return 0;
}
Node createNode() {
	Node new = NULL;
	new = (Node)malloc(sizeof(Node));

	if (new == NULL) {
		printf("Greska pri alokaciji!\n");
		return;
	}

	return new;
}
Node createNewChild(Node n, char name[20]) {
	Node new = createNode();
	new->parent = n;
	new->brother = n->brother;
	new->child = NULL;
	strcpy(new->dirName, name);

	return new;
}

Node createNewBrother(Node n, char name[20]) {
	Node new = createNode();
	new->parent = n->parent;
	new->brother = NULL;
	new->child = NULL;
	n->brother = new;
	strcpy(new->dirName, name);

	return new;
}

void printDirectory(Node n) {
	
	n = n->child;

	if (n != NULL)
		while (n) {
			printf("%s\n", n->dirName);
			n = n->brother;
		}
	else
		printf("Direktorij je prazan\n");
}

Node findNode(Node n, char name[20]) {
	Node temp = n->child;
	if (!strcmp(temp, name)) {
		n = temp;
		return n;
	}
	else 
		while (temp = temp->brother)
			if (!strcmp(temp, name)) {
				n = temp;
				return n;
			}
		
		printf("Direktorij nije pronadjen\n");
		return n;

}

void printHelp() {
	printf("Naredbe:\nmd - novi direktorij\ncd - udji u direktorij\n"
		"cd- - izadji iz direktorija\ndir - ispisi sadrzaj direktorija\nexit - izadji iz programa\n"
		"h - pomoc");
}