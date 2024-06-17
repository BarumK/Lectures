#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function declarations
void insert(int element, int Queue[], int* n);
int delete_min(int Queue[], int* n);
int delete_max(int Queue[], int* n);
int delete_median(int Queue[], int* n);
int find_min(int Queue[], int n);
int find_max(int Queue[], int n);
int find_median(int Queue[], int n);

// main function
int main() {
    // variables
    int loopNum; // variable to decide how many times to iterate
    char operationType, target; // operation type and target
    int elementNum; // element to insert
    int queueSize = 0; // variable for expressing size of priority queue; it means numbers of elements in Queue
    int resultNum = 0; // variable for expressing size of result array; it means numbers of elements in resultPrint
    int* Queue; // priority queue array(Max heap); queue starts at index 1 due to heap structure
    int* temp; // temporary pointer to store the result of find operation
    int** resultPrint; // result array to print

    // get iteration times
    scanf("%d", &loopNum);

    //memory allocation
    Queue = (int*) malloc(sizeof(int) * (loopNum + 1));
    if (Queue == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    resultPrint = (int**) malloc(sizeof(int*) * loopNum);
    if (resultPrint == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // loop "loopNum" times
    for (int i = 0; i < loopNum; i++) {
        scanf(" %c", &operationType);
        if (operationType == 'I') { // Insert
            scanf(" %d", &elementNum);
            insert(elementNum, Queue, &queueSize);
        }
        else if (operationType == 'D') { // Delete
            scanf(" %c", &target);
            if (target == 'M') { // Delete minimun
                delete_min(Queue, &queueSize);
            }
            else if (target == 'X') { // Delete maximum
                delete_max(Queue, &queueSize);
            }
            else if (target == 'E') { // Delete median
                delete_median(Queue, &queueSize);
            }
            else printf("Invalid target\n");
        }
        else if(operationType == 'F') { // Find
            scanf(" %c", &target);
            if (target == 'M') { // Find minimum
                if (queueSize == 0) resultPrint[resultNum++] = NULL; // if Queue is empty, nothing is found
                else {
                    temp = (int*) malloc(sizeof(int));
                    if (temp == NULL) {
                        printf("Memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    *temp = find_min(Queue, queueSize);
                    resultPrint[resultNum++] = temp;
                }
            }
            else if (target == 'X') { // Find maximum
                if (queueSize == 0) resultPrint[resultNum++] = NULL; // if Queue is empty, nothing is found
                else {
                    temp = (int*) malloc(sizeof(int));
                    if (temp == NULL) {
                        printf("Memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    *temp = find_max(Queue, queueSize);
                    resultPrint[resultNum++] = temp;
                }
            }
            else if (target == 'E') { // Find median
                if (queueSize == 0) resultPrint[resultNum++] = NULL; // if Queue is empty, nothing is found
                else {
                    temp = (int*) malloc(sizeof(int));
                    if (temp == NULL) {
                        printf("Memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    *temp = find_median(Queue, queueSize);
                    resultPrint[resultNum++] = temp;
                }
            }
            else printf("Invalid target\n");
        }
        else printf("Invalid operation type\n");

        /* This part is for test
        if (queueSize > 0) {
            for (int i = 0; i < queueSize; i++) printf("%d ", Queue[i]);
        }
        printf("\n");
        */
    }

    // printing result
    for (int i = 0; i < resultNum; i++) {
        if (resultPrint[i] == NULL) printf("NULL\n"); // print NULL if nothing found
        else {
            printf("%d\n", *(resultPrint[i]));
            free(resultPrint[i]); // memory deallocation
        }
    }

    // memory deallocation
    free(Queue);
    free(resultPrint);

    return 0;
}


// functions
void insert(int element, int Queue[], int* n) { // Time complexity of O(n); due to shifting operations
    // variables initialization
    int i = (*n)++;

    // sorting priority Queue; assume Queue is already sorted before insert element
    // then we have to find appropriate position and shift elements to left

    for (; (i > 0) && (Queue[i - 1] > element); i--) { // if find appropriate position or i becomes 0, loop will stop
        Queue[i] = Queue[i - 1]; // shift elements to right
    }
    Queue[i] = element;
}

int delete_min(int Queue[], int* n) { // Time complexity of O(n); due to shifting operations
    // do nothing if Queue is empty
    if ((*n) == 0) return -1;

    // variables initialization
    int minValue = Queue[0];

    // shifting
    for (int i = 0; i < (*n) - 1; i++) { // start at the point of minimum element
        Queue[i] = Queue[i + 1]; // shifting value to the right
    }
    (*n)--; // decrease n
    
    return minValue;
}

int delete_max(int Queue[], int* n) { // Time complexity of O(1)
    // do nothing if Queue is empty
    if ((*n) == 0) return -1;

    // variables initialization
    int maxValue = Queue[--(*n)]; // decrease n

    return maxValue;
}

int delete_median(int Queue[], int* n) { // Time complexity of O(n); due to shifting operations
    // do nothing if Queue is empty
    if ((*n) == 0) return -1;

    // variables initialization
    int medianValue = Queue[((*n) - 1) / 2];

    // shifting
    for (int i = ((*n) - 1) / 2; i < (*n) - 1; i++) { // start at the point of median element
        Queue[i] = Queue[i + 1]; // shifting value to the right
    }
    (*n)--; // decrease n

    return medianValue;
}

int find_min(int Queue[], int n) { // Time complexity of O(1)
    return Queue[0];
}

int find_max(int Queue[], int n) { // Time complexity of O(1)
    return Queue[n - 1];
}

int find_median(int Queue[], int n) { // Time complexity of O(1)
    return Queue[(n - 1) / 2];
}