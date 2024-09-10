// ********************
// IO
// ********************

char* string_new(int length);
void string_free(char** string);
int string_length(char buffer[]);

int read_line(char buffer[], int capacity);
int read_int();

int get_index_to_mark(int min, int max);
