/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Tahmid Sajin, EE Username: tsajin, COE628 Section 2, 500 830 210
 *
 * Created on February 24, 2021, 8:35 AM
 */

#include  <stdio.h> /* printf */
#include  <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>


void * count(void *);
int globalNumber = 0;
//Create a mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    int i;
    pthread_t counterThread[5];


    //Create the 5 threads
    //Wait for all treads to finish
    
    for (int thread = 0; thread < 5; thread++) {
        if (pthread_create(&counterThread[i], NULL, &count, NULL))
            printf("There was an error creating the threads");
    }
    
    while (globalNumber < 50);
    for (int thread; thread < 5; thread++) {
        pthread_join(counterThread[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex1);

    return (0);
}

void * count(void * junk) {
    int loopCount = 0;
    int error;
    
    do {
        int tmp = globalNumber;
        printf("The counter is: %d\n Local counter is: %d\n Thread is: %d\n PID: %d\n\n", tmp, loopCount, pthread_self(), getpid());
        
        do{
            error = pthread_mutex_lock(&mutex1);
            
            if(error != 0) {
                printf("%d", error);
            }
                
        } while(error != 0);
        
        tmp = globalNumber;
        tmp++;
        
        sleep(rand()%2);
        
        globalNumber = tmp;        
        pthread_mutex_unlock(&mutex1);
        
        loopCount++;
    } while (loopCount < 10);
    
    return (0);
}


