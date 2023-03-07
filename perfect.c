//Nodar Chabashvili

#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>

//declaring functions
void print_perfect(int low, int high);
static int is_perfect(uint64_t num);
void* print_perfect_thread(void *thrd);

//declaring global variables for functions
int gl_low = 1;
int gl_high = 10000;
int thread_numbers = 0;

int main(int argc, char *argv[]) {

    //declaring variables
    char ch;
    int low = 1;
    int high = 10000;
    int thrd = 0;
    int v = 0;

    //reading arguments from terminal
    while ((ch = getopt(argc, argv, "s:e:t:v")) != -1) {
       
        if (ch == 's') {
            if (optarg != NULL) {
                low = atoi(optarg);
            }
        }
        if (ch == 'e') {
            if (optarg != NULL) {
                high = atoi(optarg);
            }
        }
        if (ch == 't') {
            if (optarg != NULL) {
                thrd = atoi(optarg);
            }
        }
        if (ch == 'v') {
            v = 1;
        }
    }

    gl_low = low;
    gl_high = high;
    thread_numbers = thrd;

    pthread_t thread_ids[thrd];
    // if there was t then multi thread the problem
    if (thrd > 0) {
        pthread_t newthread;

        //create as many threads as user wants and computer can handle
        for (int i = 0; i < thrd; i++) {
            // if we got argument v then print whats happening
            if (v) {
                int segment = (gl_high - gl_low) / thread_numbers;
                if (thread_numbers == i + 1) {
                    printf("perfect: t%d searching [%d, %d]\n", i, gl_low + (segment * i), gl_high);
                } else {
                    printf("perfect: t%d searching [%d, %d]\n", i, gl_low + (segment * i), gl_low + (segment * (i + 1)));
                }
            }
            // declaring num in heap to pass to threads
            int *num = (int*)malloc(sizeof(int));
            *num = i;
            //making threads
            pthread_create(&newthread, NULL, print_perfect_thread, num);
            //storing ids in array
            thread_ids[i] = newthread;
        }
        void* val;
        for (int i = 0; i < thrd; i++) {
            //making the main thread wait for others
            pthread_join(thread_ids[i], &val);
            printf("perfect: t%d finishing\n", i);
        }
    } else {
        // if -t is not present then just print 
        print_perfect(low, high);
    }
    
    return 0;
} 

// function from HW
static int is_perfect(uint64_t num) {
    uint64_t i, sum;
    if (num < 2) {
        return 0;
    }
    
    for (i = 2, sum = 1; i * i <= num; i++) {
        if (num % i == 0) {
            sum += (i * i == num) ? i : i + num / i;
        }
    }
    return (sum == num);
}

//print perfect numbers
void print_perfect(int low, int high) {
    for (int i = 0; i < high - low; i++) {
        if (is_perfect(low + i)) {
            printf("%d\n", low + i);
        }
    } 
}


void* print_perfect_thread(void *num){
    int *number = (int*) num;
    int n = *number;
    //creating segments deppending on how many threads we have
    int segment = (gl_high - gl_low) / thread_numbers;
    //printing perfect numbers in those segments that tread is responsible
    if (thread_numbers == n + 1) {
        print_perfect(gl_low + (segment * n), gl_high);
    } else {
        print_perfect(gl_low + (segment * n), gl_low + (segment * (n + 1)));
    }
}
