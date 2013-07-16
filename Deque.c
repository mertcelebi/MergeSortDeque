/* Program Name: protoDeque.c
   Program Description: A complete implementation of the Deque ADT.
   -----------
   Written by: Feridun Mert Celebi
   Date = 03/27/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include "/c/cs223/Hwk4/Deque.h"

struct deque {

    Deque back;
    Deque front;
    char *node;
};

// Implementation of createD()
int createD (Deque (*d)){

    (*d) = malloc(sizeof (struct deque));

    if((*d) == NULL) return 0;
    
    else{

        (*d) -> front=(*d);
        (*d) -> back=(*d);
        (*d) -> node=NULL;
        return 1;
    }
}

// Implementation of isEmptyD()
int isEmptyD (Deque *d){

    if (*d == NULL) return 0;
    
    else if (((*d) -> front == (*d)) && ((*d) -> node == NULL)) return 1;
    
    else return 0;
}

// Implementation of addD()
int addD (Deque *d, char *s){

    Deque newdeque;

    if(isEmptyD(d)){

        (*d) -> node = s;
        return 1;
    }

    if (!(newdeque = malloc(sizeof(struct deque)))) return 0;
    
    else{

        newdeque -> node = s;
        newdeque -> front = (*d) -> front;
        newdeque -> back = (*d);
        (*d) -> front = newdeque;
        newdeque -> front -> back = newdeque;
        return 1;
    }
}

// Implementation of remD()
int remD (Deque *d, char **s){

    if ((isEmptyD(d)) || (*d == NULL)) return 0;
    
    if ((*d) -> front == (*d)){

        *s = (*d) -> node;
        (*d) -> node = NULL;
        return 1;
    } 

    *s = (*d) -> node;
    (*d) -> back -> front = (*d) -> front;
    (*d) -> front -> back = (*d) -> back;
  
    Deque fake;
    fake = *d; 
	(*d) = (*d) -> back;
	free(fake);
    
    return 1;
}

// Implementation of popD()
int popD (Deque *d, char **s){

    if ((isEmptyD(d)) || (*d == NULL)) return 0;
    
    if ((*d) -> back == (*d)){

        *s = (*d) -> node;
        (*d) -> node = NULL;
        return 1;
    }
    
    *s = (*d) -> front -> node;
    (*d) -> front -> front -> back = (*d);
    
    Deque fake;
    fake = (*d) -> front;
    (*d) -> front = (*d) -> front -> front;
    free(fake); 
    
    return 1;
}

// Implementation of headD()
int headD (Deque *d, char **s){

    if ((isEmptyD(d)) || (*d == NULL)) return 0;   
    
    *s = (*d) -> node; 
    
    return 1;	
}

// Implementation of topD()
int topD (Deque *d, char **s){

    if ((isEmptyD(d)) || (*d == NULL)) return 0;   
    
    *s = (*d) -> front -> node;
    
    return 1;   
}


// Implementation of destroyD()
int destroyD (Deque *d){

    char *fake;

    if (*d == NULL) return 0; 

    while (remD(d,&fake)) free(fake);
    
    free (*d);
    *d = NULL;

    return 1;
}
