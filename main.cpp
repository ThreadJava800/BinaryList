#include "tree.h"

int main() {
    Node_t *tree = nodeCtor("Test", nullptr, nullptr, nullptr, printElemT);

    addLeftLeaf(tree, "Left");
    addLeftLeaf(tree->left, "New Left");
    addRightLeaf(tree, "Right");
    addRightLeaf(tree->right, "New Right");
    addRightLeaf(tree->left, "Right Left");
    textDump(tree);

    nodeDtor(tree);

    return 0;
}