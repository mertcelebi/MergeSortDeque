// Deque.h                                      Stan Eisenstat (02/26/13)
//
// Define the abstract data type for a Deque of string pointers.  The strings
// themselves are NOT stored.

// Define true and false

#include <stdbool.h>


// A variable of type Deque is a pointer to the struct used to implement the
// deque operations declared below.  Note that the declaration of that struct
// appears only in the file that implements these operations.  Thus the calling
// program does not know what fields have been defined and cannot access them;
// and the variable must be a pointer since the size of the struct is unknown.

typedef struct deque *Deque;


// The following functions are the only means of accessing a Deque data
// structure.  Each requires a pointer to a Deque variable in case it needs
// to modify the value of that variable (or more generally for consistency).
// Each returns the status of the operation, either true (= success) or false
// (= failure; e.g., an invalid argument, an inconsistent Deque object, or a
// NULL return from malloc() / realloc()).


// Set *D to a new object of type Deque.
// Returns true if successful, false otherwise.
int createD (Deque *d);


// Return true if the Deque *D is empty, false otherwise.  The value of *D may
//   change as a result.
int isEmptyD (Deque *d);


// Add the string pointer S to the tail of the Deque *D; the string itself is
//   not copied.  The value of *D may change as a result.
// Return true if successful,  false otherwise.
int addD (Deque *d, char *s);


// Remove the string pointer at the head of the Deque *D and store that value
//   in *S.  The value of *D may change as a result.
// Return true if successful, false otherwise (e.g., if *D is empty).
int remD (Deque *d, char **s);


// An alternate name for addD() when the Deque is used as a stack.
#define pushD(d,s)  addD(d,s)


// Remove the string pointer at the tail of the Deque *D and store that value
//   in *S.  The value of *D may change as a result.
// Return true if successful, false otherwise (e.g., if *D is empty).
int popD (Deque *d, char **s);


// Store the value of the string pointer at the head (= head of the queue)
//   of the Deque *D in *S.  The value of *D may change as a result.
// Return true if successful, false otherwise (e.g., if *D is empty).
int headD (Deque *d, char **s);


// Store the value of the string pointer at the tail (= top of the stack)
//   of the Deque *D in *S.  The value of *D may change as a result.
// Return true if successful, false otherwise (e.g., if *D is empty).
int topD (Deque *d, char **s);


// Destroy the Deque *D by freeing any storage that it uses (but not the the
//   blocks of storage to which the string pointers point) and set the value
//   of *D to NULL.
// Return true if successful, false otherwise.
int destroyD (Deque *d);
