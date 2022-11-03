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

struct Node_t {
    Elem_t  value    = {};
    Node_t* left     = nullptr;
    Node_t* right    = nullptr;
    Node_t* previous = nullptr;

    PrintFunction_t printFunc = printElemT;
};

#if _DEBUG

#define CHECK(expression, node, errCode) { \
    if (expression) {                       \
        if (err) *err = errCode;             \
        textDump(node, errCode);              \
        exit(errCode);                         \
    }                                           \
}                                                \

#else

#define CHECK(expression, node, errCode) { \
    if (expression) {                       \
        if (err) *err = errCode;             \
        exit(errCode);                        \
    }                                          \
}                                               \

#endif

Node_t* nodeCtor(Elem_t value, Node_t *left, Node_t *right, Node_t *previous, PrintFunction_t printFunc, int *err = nullptr);                                                                                                 \

Node_t* addRightLeaf(Node_t *node, Elem_t value, int *err = nullptr);

Node_t* addLeftLeaf(Node_t *node, Elem_t value, int *err = nullptr);

void nodeDtor(Node_t *node, int *err = nullptr);

void printErrMsg(FILE* file, int errCode);

void dumpNode(FILE* file, Node_t *node);

void textDump(Node_t *node, int errCode = 1 << 0);

void closeLogfile(void);