#ifndef TREEMAP_h
#define TREEMAP_h

typedef struct TreeMap TreeMap;
typedef struct TreeNode TreeNode;

struct TreeNode {
    void* key;
    void * value;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

TreeMap * createTreeMap(int (*lower_than_int) (void* key1, void* key2));

void insertTreeMap(TreeMap * tree, void* key, void * value);

void eraseTreeMap(TreeMap * tree, void* key);

void * searchTreeMap(TreeMap * tree, void* key);

void * upperBound(TreeMap * tree, void* key);

void * firstTreeMap(TreeMap * tree);

void * nextTreeMap(TreeMap * tree);

void * backTreeMap(TreeMap * tree); //Go to the previous node with high value, next higher value after current

void * lastTreeMap (TreeMap * tree); //This function return the higher value (key) from tree.

void  imprimemeEnOrden(TreeNode * map );

#endif /* TREEMAP_h */
