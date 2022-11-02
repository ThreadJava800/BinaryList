#include "tree.h"

#if _DEBUG
FILE *logFile = fopen("logs.txt", "w");
int   onClose = atexit(closeLogfile);
#endif

void printElemT(FILE *file, Elem_t value) {
    fprintf(file, "%s", value);
}

int _treeCtor(Tree_t *tree, PrintFunction_t func) {
    CHECK(!tree, tree, TREE_NULL);

    tree->root      = nullptr;
    tree->printFunc = func;

    return TREE_OK;
}

void textDump(Tree_t *tree, int errCode) {

}

int treeDtor(Tree_t *tree) {
    CHECK(!tree, tree, TREE_NULL);

    free(tree);

    return TREE_OK;
}

#if _DEBUG
void closeLogfile(void) {
    if (logFile) fclose(logFile);
}
#endif