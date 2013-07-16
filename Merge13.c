/* Program Name: Merge13.c
   Program Description: Merge13 is a program that reads lines from the 
   files specified, removes the trailing newlines if any, sorts them using 
   a binary merge sort, and writes the sorted lines to the standard output 
   followed by newlines. When more than one file is specified, all of the 
   lines in all of the files are sorted into one output stream. 
   When no files are specified, nothing is output.
   -----------
   Written by: Feridun Mert Celebi
   Date = 03/27/2013
*/

  #include <stdio.h>
	#include <stdlib.h>
   	#include <string.h>
	#include <limits.h>
	#include "/c/cs223/Hwk3/getLine.h"
	#include "/c/cs223/Hwk4/Deque.h"

	#define DIE(msg) exit (fprintf (stderr, "%s\n", msg)) //Prints out a single line of error message and exits
	
	//Function declarations
	void mergeSort(Deque *queue, int noLines, int POS, int LEN); //mergeSort function, dealing with the recursive calls.
	void merge(Deque *queue2, Deque *queue, int limit, int POS, int LEN); //sorts and merges the keys.
	void printSorted(Deque *queue); //Prints the sorted queue in order.

	int main (int argc, char *argv[]){
	
		int POS = 0, LEN = INT_MAX, index = 1, noLines = 0, length = 0;
		char *line, *s;
		FILE *fileRead;
		Deque queue;

		if (!createD (&queue)) DIE("createD() failed");
        
        if ((argc == 1) || ((argc == 2) && (argv[1][0] == '-'))) DIE("No files!"); //Case where no files are present/

        if (argv[1][0] == '-'){ //Determining POS and LEN

            if (argv[1][1] != '-'){

            	index = 2;
            	POS = -1 * strtol(argv[1], &s, 10);
            	if (*s == ',') LEN = strtol(s + 1, &s, 10); //Case where LEN is present.
            }

            else DIE("Invalid POS and/or LEN");
        }

        if (POS < 0 || LEN < 0) DIE("Invalid POS and/or LEN"); //Case of negative POS and LEN.

        for (; index < argc; index++){ //Read the files and the lines.
            
            fileRead = fopen(argv[index], "rt");
            if (!fileRead) DIE("Nonexistent file");

            while ((line = getLine(fileRead))){

            	noLines++;
                length = strlen(line) - 1;

                if (line[length] == '\n') line[length] = '\0';

                if (!addD (&queue, line)) DIE("addD() failed");
            }

            fclose(fileRead);
        }

        if (!LEN){ //Case where LEN is zero and we are comparing "" strings.

            printSorted(&queue);
            return EXIT_SUCCESS;
        }

		mergeSort(&queue, noLines, POS, LEN);
		printSorted(&queue);
		destroyD(&queue);
		
		return EXIT_SUCCESS;
	}

	//This function gets a pointer to a Deque.
	//Returns void and prints the sorted queue.
	void printSorted(Deque *queue){
		
		char *str = NULL;

		while (!isEmptyD(queue)){

			if (!remD(&(*queue), &str)) DIE("remD() failed");
			puts(str);
			free(str);
		}
	}

    //Recursively divides the list into two pieces until there is 1 or 0
    //elements. It gets a pointer to a Deque, the location of the 
    //last element (noLines). POS and LEN are necessary for determining the key.
    //Returns void.
	void mergeSort(Deque *queue, int noLines, int POS, int LEN){
		
		int index, middle = noLines / 2; //Middle is used as a splitter
		Deque queue2;
		char *str = NULL;

		if (middle != 0){ //Stops the recursive calls when there are 1 or 0 elements.
		
			if (!createD(&queue2)) DIE("createD() failed");

			for (index = 0; index < middle; index++){ //Create the first and second half of the queue

				if (!remD(queue, &str)) DIE("remD() failed");
				if (!addD(&queue2, str)) DIE("addD() failed");
			}

			mergeSort(&queue2, middle, POS, LEN); //First half
			mergeSort(queue, noLines - middle, POS, LEN); //Second half
			merge(&queue2, queue, noLines - middle, POS, LEN); //Actually merges the halfs
			
			destroyD(&queue2);
		}
	}

	//This is the actual sorting and merging method.
    //It gets a pointer to a Deque, the limit and the a pointer to a Deque
    //which helps with sorting (queue2). POS and LEN are 
    //necessary for determining the key. 
    //Returns void.
	void merge(Deque *queue2, Deque *queue, int limit, int POS, int LEN){

		int index = 1;
		char *strng = NULL, *strng2 = NULL;

		while ((index <= limit) && (!isEmptyD(queue2))){

			strng = NULL; 
			strng2 = NULL;
			
			if (!headD(queue, &strng)) DIE("headD() failed");
			if (!headD(queue2, &strng2)) DIE("headD() failed");
			
			if (strncmp(strng + POS, strng2 + POS, LEN) < 0){ //if strng is less than or equal to strng2
				
				if(!remD(queue, &strng)) DIE("remD() failed");
				if (!addD(queue, strng)) DIE("addD() failed");
				index++;
			}

			else{
				
				if(!remD(queue2, &strng2)) DIE("remD() failed");
				if (!addD(queue, strng2)) DIE("addD() failed");
			}
		}
		
		while (index <= limit){ //If first half is not empty, add everything to the actual queue.

			strng = NULL;
			
			if (!remD(queue, &strng)) DIE("remD() failed");
			if (!addD(queue, strng)) DIE("addD() failed");
			index++;
		}
		
		while (!isEmptyD(queue2)){ //If second half is not empty, add everything to the actual queue.

			strng = NULL;
			
			if (!remD(queue2, &strng)) DIE("remD() failed");
			if (!addD(queue, strng)) DIE("addD() failed");
		}
	}
