#include <stdbool.h>
#include <pthread.h>

#ifndef C_STRUCTS_H
#define C_STRUCTS_H

//####################
// COMMON
//####################
typedef struct Error {
  int code;
  char* message;
} Error;


Error* error(int code, char* message);
void error_free(Error** error);

typedef struct Result {
  void* ok;
  Error* error;
} Result;

Result success(void* value);
Result fail(int code, char* message);

#define ERR_MALLOC_FAILED "malloc failed"

#define ERR_RWLOCK_INIT_FAILED "rwlock init failed"
#define ERR_RWLOCK_DESTROY_FAILED "rwlock destroy failed"
#define ERR_RDLOCK_FAILED "rdlock failed"
#define ERR_WRLOCK_FAILED "wrlock failed"
#define ERR_RWLOCK_UNLOCK_FAILED "rwlock unlock failed"

#define ERR_AT_CAPACITY "at capacity"
#define ERR_INVALID_INDEX "invalid index"
#define ERR_INVALID_POSITION "invalid position"

typedef void (*FreeFn)(void** const);
typedef bool (*PredicateFn)(void* const);
typedef char* (*ToStringFn)(void* const);


//####################
// ARRAY
//####################
typedef struct Array {
  pthread_rwlock_t lock;
  int capacity;
  int size;
  void* elements[];
} Array;

bool array_index_valid(Array* const array, int index);
bool array_has_capacity(Array* const array);

Result array_new(int capacity);
int array_clear(Array* const array, FreeFn const free_element);
int array_free(Array** const array, FreeFn const free_element);

int array_append(Array* const array, void* const element);
int array_prepend(Array* const array, void* const element);
int array_set(Array* const array, int index, void* const element);

Result array_get(Array* const array, int index);
Result array_remove(Array* const array, int index);

typedef void (*ArrayEachFn)(void* const);
int array_for_each(Array* const array, ArrayEachFn const each);

typedef void* (*ArrayMapFn)(void* const);
Result array_map(Array* const array, ArrayMapFn const map);

Result array_to_string(Array* const array, ToStringFn const to_string);


//####################
// MATRIX
//####################
typedef struct Position {
  int row;
  int column;
} Position;

Position position_new(int row, int column);
char* position_to_string(Position* position);

typedef struct Grid {
  pthread_rwlock_t lock;
  int rows;
  int columns;
  int capacity;
  int size;
  void* elements[];
} Grid;

bool grid_position_valid(Grid* const grid, Position* const position);
bool grid_has_capacity(Grid* const grid);

Result grid_new(int rows, int columns);
int grid_clear(Grid* const grid, FreeFn const free_element);
int grid_free(Grid** const grid, FreeFn const free_element);

int grid_set(Grid* const grid, Position* const position, void* const element);

Result grid_get(Grid* const grid, Position* const position);
Result grid_remove(Grid* const grid, Position* const position);

typedef void (*GridEachFn)(void* const);
int grid_for_each(Grid* const grid, GridEachFn const each);

typedef void* (*GridMapFn)(void* const);
Result grid_map(Grid* const grid, GridMapFn const map);

Result grid_to_string(Grid* const grid, ToStringFn const to_string);


//####################
// LINKED LIST
//####################
typedef struct Node {
  void* value;
  struct Node* next;
  struct Node* previous;
} Node;

Result node_new(void* const value);
int node_free(Node** const node, FreeFn const free_value);

typedef struct LinkedList {
  pthread_rwlock_t lock;
  struct Node* head;
  struct Node* tail;
} LinkedList;

int linked_list_size(LinkedList* const list);

Result linked_list_new();
int linked_list_clear(LinkedList* const list, FreeFn const free_value);
int linked_list_free(LinkedList** const list, FreeFn const free_value);

int linked_list_append(LinkedList* const list, void* const value);
int linked_list_prepend(LinkedList* const list, void* const value);

int linked_list_insert_before(LinkedList* const list, Node* const node, void* const value);
int linked_list_insert_after(LinkedList* const list, Node* const node, void* const value);

Result linked_list_remove_head(LinkedList* const list);
Result linked_list_remove_tail(LinkedList* const list);
Result linked_list_remove(LinkedList* const list, Node* node);

Result linked_list_find(LinkedList* const list, PredicateFn const predicate);

#endif
