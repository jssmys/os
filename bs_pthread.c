#include <stdio.h>
#include <pthread.h>

#define ARRAY_SIZE 10
#define SEARCH_ELEMENT 5

int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int result = -1;

void *left_half_search(void *arg) {
    
    for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
        if (array[i] == SEARCH_ELEMENT) {
            result = i;
            break;
        }
    }
    pthread_exit(NULL);
}

void *right_half_search(void *arg) {
    
    for (int i = ARRAY_SIZE / 2; i < ARRAY_SIZE; ++i) {
        if (array[i] == SEARCH_ELEMENT) {
            result = i;
            break;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_left, thread_right;

    
    if (pthread_create(&thread_left, NULL, left_half_search, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

   
    if (pthread_create(&thread_right, NULL, right_half_search, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    
    pthread_join(thread_left, NULL);
    pthread_join(thread_right, NULL);

    if (result != -1) {
        printf("Element %d found at index %d\n", SEARCH_ELEMENT, result);
    } else {
        printf("Element %d not found in the array\n", SEARCH_ELEMENT);
    }

    return 0;
}

