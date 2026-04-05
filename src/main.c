#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Node;

struct Edge {
    int weight;
    struct Node* dest;
    struct Edge* next;
};

struct Node {
    char name[50];
    struct Edge* edges;
    struct Node* next;
};

struct Node* head = NULL;

// ---------- FIND NODE ----------
struct Node* findNode(char name[]) {
    struct Node* temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// ---------- ADD NODE ----------
void addNode() {
    char name[50];
    printf("Enter location name: ");
    scanf("%s", name);

    if (findNode(name)) {
        printf("Location already exists.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->edges = NULL;
    newNode->next = head;
    head = newNode;

    printf("Location added.\n");
}

// ---------- ADD EDGE ----------
void addEdge() {
    char src[50], dest[50];
    int weight;

    printf("Enter source: ");
    scanf("%s", src);
    printf("Enter destination: ");
    scanf("%s", dest);
    printf("Enter distance: ");
    scanf("%d", &weight);

    struct Node* s = findNode(src);
    struct Node* d = findNode(dest);

    if (!s || !d) {
        printf("Invalid locations.\n");
        return;
    }

    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->dest = d;
    newEdge->weight = weight;
    newEdge->next = s->edges;
    s->edges = newEdge;

    printf("Road added.\n");
}

// ---------- DISPLAY ----------
void displayGraph() {
    struct Node* temp = head;
    while (temp) {
        printf("%s -> ", temp->name);
        struct Edge* e = temp->edges;
        while (e) {
            printf("%s(%d) ", e->dest->name, e->weight);
            e = e->next;
        }
        printf("\n");
        temp = temp->next;
    }
}

// ---------- DELETE EDGE ----------
void deleteEdge() {
    char src[50], dest[50];
    printf("Enter source: ");
    scanf("%s", src);
    printf("Enter destination: ");
    scanf("%s", dest);

    struct Node* s = findNode(src);
    if (!s) return;

    struct Edge *curr = s->edges, *prev = NULL;

    while (curr) {
        if (strcmp(curr->dest->name, dest) == 0) {
            if (prev) prev->next = curr->next;
            else s->edges = curr->next;
            free(curr);
            printf("Road deleted.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("Road not found.\n");
}

// ---------- DELETE NODE ----------
void deleteNode() {
    char name[50];
    printf("Enter location to delete: ");
    scanf("%s", name);

    struct Node *curr = head, *prev = NULL;

    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            if (prev) prev->next = curr->next;
            else head = curr->next;

            // free edges
            struct Edge* e = curr->edges;
            while (e) {
                struct Edge* temp = e;
                e = e->next;
                free(temp);
            }

            free(curr);
            printf("Location deleted.\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("Location not found.\n");
}

// ---------- UPDATE NODE ----------
void updateNode() {
    char oldName[50], newName[50];

    printf("Enter old name: ");
    scanf("%s", oldName);

    struct Node* node = findNode(oldName);
    if (!node) {
        printf("Not found.\n");
        return;
    }

    printf("Enter new name: ");
    scanf("%s", newName);
    strcpy(node->name, newName);

    printf("Updated.\n");
}

// ---------- UPDATE EDGE ----------
void updateEdge() {
    char src[50], dest[50];
    int weight;

    printf("Enter source: ");
    scanf("%s", src);
    printf("Enter destination: ");
    scanf("%s", dest);

    struct Node* s = findNode(src);
    if (!s) return;

    struct Edge* e = s->edges;
    while (e) {
        if (strcmp(e->dest->name, dest) == 0) {
            printf("Enter new distance: ");
            scanf("%d", &weight);
            e->weight = weight;
            printf("Updated.\n");
            return;
        }
        e = e->next;
    }

    printf("Road not found.\n");
}

// ---------- DIJKSTRA WITH PATH ----------
void shortestPath() {
    char start[50], end[50];

    printf("Enter source: ");
    scanf("%s", start);
    printf("Enter destination: ");
    scanf("%s", end);

    struct Node* nodes[100];
    int dist[100], visited[100], parent[100];
    int count = 0;

    struct Node* temp = head;
    while (temp) {
        nodes[count] = temp;
        dist[count] = INT_MAX;
        visited[count] = 0;
        parent[count] = -1;
        count++;
        temp = temp->next;
    }

    int s = -1, d = -1;

    for (int i = 0; i < count; i++) {
        if (strcmp(nodes[i]->name, start) == 0) s = i;
        if (strcmp(nodes[i]->name, end) == 0) d = i;
    }

    if (s == -1 || d == -1) {
        printf("Invalid locations.\n");
        return;
    }

    dist[s] = 0;

    for (int i = 0; i < count; i++) {
        int min = INT_MAX, u = -1;

        for (int j = 0; j < count; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1) break;

        visited[u] = 1;

        struct Edge* e = nodes[u]->edges;
        while (e) {
            for (int k = 0; k < count; k++) {
                if (nodes[k] == e->dest) {
                    if (dist[u] + e->weight < dist[k]) {
                        dist[k] = dist[u] + e->weight;
                        parent[k] = u;
                    }
                }
            }
            e = e->next;
        }
    }

    printf("Shortest Distance: %d\nPath: ", dist[d]);

    int path[100], idx = 0;
    for (int i = d; i != -1; i = parent[i])
        path[idx++] = i;

    for (int i = idx - 1; i >= 0; i--) {
        printf("%s", nodes[path[i]]->name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

// ---------- MAIN ----------
int main() {
    int choice;

    while (1) {
        printf("\n1.Add Location\n2.Add Road\n3.Delete Location\n4.Delete Road\n");
        printf("5.Update Location\n6.Update Road\n7.Display Map\n8.Shortest Path\n9.Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1: addNode(); break;
            case 2: addEdge(); break;
            case 3: deleteNode(); break;
            case 4: deleteEdge(); break;
            case 5: updateNode(); break;
            case 6: updateEdge(); break;
            case 7: displayGraph(); break;
            case 8: shortestPath(); break;
            case 9: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}
