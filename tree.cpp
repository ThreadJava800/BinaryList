#include "tree.h"

#if _DEBUG
FILE *logFile = fopen("logs.txt", "w");
int   onClose = atexit(closeLogfile);
#endif

void printElemT(FILE *file, Elem_t value) {
    fprintf(file, "%s", value);
}

Node_t* nodeCtor(Elem_t value, Node_t *left, Node_t *right, Node_t *previous,  PrintFunction_t printFunc, int *err) {
    Node_t *node = (Node_t*) calloc(1, sizeof(Node_t));
    CHECK(!node, node, NULL_PTR);

    node->value    = value;
    node->left     = left;
    node->right    = right;
    node->previous = previous;

    node->printFunc = printFunc;

    return node;
}

Node_t* addRightLeaf(Node_t *node, Elem_t value, int *err) {
    CHECK(!node, node, NULL_PTR);

    Node_t *childNode = nodeCtor(value, nullptr, nullptr, node, node->printFunc, err);
    CHECK(!childNode, childNode, NULL_PTR);

    node->right = childNode;

    return childNode;
}

Node_t* addLeftLeaf(Node_t *node, Elem_t value, int *err) {
    CHECK(!node, node, NULL_PTR);

    Node_t *childNode = nodeCtor(value, nullptr, nullptr, node, node->printFunc, err);
    CHECK(!childNode, childNode, NULL_PTR);

    node->left = childNode;

    return childNode;
}

void nodeDtor(Node_t *node, int *err) {
    if (!node) return;

    if (node->left) nodeDtor(node->left, err);
    if (node->right) nodeDtor(node->right, err);

    free(node);
}

void printErrMsg(FILE* file, int errCode) {
    switch (errCode) {
        case TREE_OK:
            break;
        case NULL_PTR:
            fprintf(file, "Assertion failed: NULL POINTER (%d)\n", errCode);
            break;
        case TREE_NULL:
            fprintf(file, "Assertion failed: Tree was null (%d)\n", errCode);
            break;
        default:
            fprintf(file, "Assertion failed: Unknown error: %d\n", errCode);
            break;
    }
}

void dumpNode(FILE* file, Node_t *node) {
    if (!node) return;

    fprintf(file, "(");

    if (node->left) dumpNode(file, node->left);
    //fprintf(file, ")");

    node->printFunc(logFile, node->value);

    if (node->right) dumpNode(file, node->right);
    fprintf(file, ")");
}

void textDump(Node_t *node, int errCode) {
    printErrMsg(logFile, errCode);
    dumpNode(logFile, node);
}

#if _DEBUG
void closeLogfile(void) {
    if (logFile) fclose(logFile);
}
#endif