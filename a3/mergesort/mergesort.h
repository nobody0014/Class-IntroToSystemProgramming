#define MAX_NAME_LENGTH 30

typedef struct EntryStruct {
    int data;
    char *name;
} Entry;

void merge(Entry *output, Entry *L, int nL, Entry *R, int nR);
void merge_sort(Entry *entries, int n);
