#define malloc(size) mymalloc(size, __FILE__, __LINE__) //__FILE__ represents current file, __LINE__ current line macro
#define free(ptr) myfree(ptr, __FILE__, __LINE__)
void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);
