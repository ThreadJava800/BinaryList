#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifndef _DEBUG
#define _DEBUG 0
#endif

typedef char* Elem_t;

typedef void (*PrintFunction_t)(FILE *file, Elem_t value);

void printElemT(FILE *file, Elem_t value);

enum TreeErrors {
    TREE_OK   = 1 << 0,
    TREE_NULL = 1 << 1,
    NULL_PTR  = 1 << 2,
};

struct TreeElement_t {
    Elem_t         value    = {};
    TreeElement_t* left     = nullptr;
    TreeElement_t* right    = nullptr;
};

#if _DEBUG
struct TreeDebug_t {
    const char *createFunc = nullptr; 
    const char *createFile = nullptr; 
    const char *name       = nullptr;
    int         createLine = 0;
};
#endif

struct Tree_t {
    TreeElement_t   *root      = nullptr;
    PrintFunction_t  printFunc = printElemT;

    #if _DEBUG
    TreeDebug_t debugInfo  = {};
    #endif
};

#if _DEBUG

#define CHECK(expression, tree, errCode) { \
    if (expression) {                       \
        textDump(tree);                      \
        return errCode;                       \
    }                                          \
}                                               \

#else

#define CHECK(expression, tree, errCode) { \
    if (expression) {                       \
        return errCode;                      \
    }                                         \
}                                              \

#endif

int _treeCtor(Tree_t *tree, PrintFunction_t func = printElemT);

void textDump(Tree_t *tree, int errCode = 0);

int treeDtor(Tree_t *tree);

#if _DEBUG

    #define treeCtor(tree, ...) {                               \
        (tree)->debugInfo.createFunc = __PRETTY_FUNCTION__;      \
        (tree)->debugInfo.createFile = __FILE__;                  \
        (tree)->debugInfo.createLine = __LINE__;                   \
        (tree)->debugInfo.name = #tree;                             \
        _treeCtor(tree, ##__VA_ARGS__);                              \
    }                                                                 \

    void closeLogfile(void);

#else 

    #define stackCtor(tree, ...) {          \
        _treeCtor(tree, ##__VA_ARGS__);      \
    }                                         \

#endif