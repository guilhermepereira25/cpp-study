#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
 	int x;
	int y;
} Point;

typedef struct QuadNode {
	struct QuadNode* nw;
	struct QuadNode* ne;
	struct QuadNode* sw;
	struct QuadNode* se;
	Point* point;
} QuadNode;

QuadNode* createQuadNode(Point* point) {
    QuadNode* node = (QuadNode*)malloc(sizeof(QuadNode));
    node->nw = NULL;
    node->ne = NULL;
    node->sw = NULL;
    node->se = NULL;
    node->point = point;
    return node;
}


// Função para inserir um ponto na Quadtree
void insert(QuadNode** root, Point* point, int xMin, int xMax, int yMin, int yMax) {
    if (*root == NULL) {
        *root = createQuadNode(point);
        return;
    }
    
    int xMid = (xMin + xMax) / 2;
    int yMid = (yMin + yMax) / 2;
    
    if (point->x <= xMid && point->y <= yMid) {
        insert(&((*root)->nw), point, xMin, xMid, yMin, yMid);
    } else if (point->x <= xMid && point->y > yMid) {
        insert(&((*root)->sw), point, xMin, xMid, yMid + 1, yMax);
    } else if (point->x > xMid && point->y <= yMid) {
        insert(&((*root)->ne), point, xMid + 1, xMax, yMin, yMid);
    } else {
        insert(&((*root)->se), point, xMid + 1, xMax, yMid + 1, yMax);
    }
}


QuadNode* search(QuadNode* root, int x, int y, int xMin, int xMax, int yMin, int yMax) {
    if (root == NULL || (root->point->x == x && root->point->y == y)) {
        return root;
    }
    
    int xMid = (xMin + xMax) / 2;
    int yMid = (yMin + yMax) / 2;
    
    if (x <= xMid && y <= yMid) {
        return search(root->nw, x, y, xMin, xMid, yMin, yMid);
    } else if (x <= xMid && y > yMid) {
        return search(root->sw, x, y, xMin, xMid, yMid + 1, yMax);
    } else if (x > xMid && y <= yMid) {
        return search(root->ne, x, y, xMid + 1, xMax, yMin, yMid);
    } else {
        return search(root->se, x, y, xMid + 1, xMax, yMid + 1, yMax);
    }
}


// Função para imprimir os pontos armazenados na Quadtree (em ordem)
void printPoints(QuadNode* root, int level) {
    if (root == NULL) {
        return;
    }

    for (int i=0; i < level; i++)
	printf("  ");

    // Imprimir as coordenadas do ponto no nó
    printf("(%d, %d)\n", root->point->x, root->point->y);

    printPoints(root->nw, level + 1);
    printPoints(root->ne, level + 1);
    printPoints(root->sw, level + 1);
    printPoints(root->se, level + 1);
}


// Função principal
int main() {
    QuadNode* root = NULL;
    
    // Inserir pontos de exemplo
    Point p1 = {3, 6};
    Point p2 = {2, 10};
    Point p3 = {5, 4};
    Point p4 = {7, 8};
    
    insert(&root, &p1, 0, 10, 0, 10);
    insert(&root, &p2, 0, 10, 0, 10);
    insert(&root, &p3, 0, 10, 0, 10);
    insert(&root, &p4, 0, 10, 0, 10);
    
    // Imprimir os pontos da Quadtree
    printf("Pontos armazenados na Quadtree:\n");
    printPoints(root, 0);

    int searchX = 3;
	int searchY = 11;

	QuadNode* foundNode = search(root, searchX, searchY, 0, 10, 0, 10);

	printf("Realizando busca no QuadTree. \n");

	if (foundNode != NULL) {
		printf("Ponto (%d, %d) encontrado na Quadtree.\n", searchX, searchY);
	} else {
        printf("Ponto (%d, %d) não encontrado na Quadtree.\n", searchX, searchY);
    }

    return 0;
}
