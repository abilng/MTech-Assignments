
#include "BSTree.h"



/*
 * Input: N/A
 * Output: Returns BSTree object properly initialized
 * Description: Constructor for BSTree class
 */
BSTree::BSTree()
{
    root = NULL;
}



/*
 * Input: N/A
 * Output: N/A
 * Description: Destructor for BSTree class
 */
BSTree::~BSTree()
{
    clear();
}



/*
 * Input: Data item to be inserted
 * Output: Inserts data item in BSTree implementation
 * Description: N/A
 */
void BSTree::insert(data val)
{
    BSTNode *x, *y, *z;
    z = new BSTNode();
    z->val = val;
    z->left = NULL;
    z->right = NULL;
    z->p = NULL;
    y = NULL;
    x = this->root;
    while(x != NULL)
    {
        y = x;
        if(z->val < x->val)
            x = x ->left;
        else
        	if(z->val > x->val)
        		x = x->right;
        	else
        		return;
    }
    z->p = y;
    if(y == NULL)
        this->root = z;
    else
    {
        if(z->val < y->val)
            y->left = z;
        else
            y->right = z;
    }
    z->left = NULL;
    z->right = NULL;
}



/*
 * Input: Data item to be deleted
 * Output: Deletes data item from BSTree implementation
 * Description: N/A
 */
bool BSTree::del(data val)
{
    BSTNode * delnode = lookup(val);
    if(delnode == NULL)
        return false;
    del(delnode);
    return true;
}



/*
 * Input: Data item to be searched
 * Output: Searches data item in BSTree implementation
 * Description: N/A
 */
bool BSTree::search(data val)
{
    if(lookup(val) != NULL)
        return true;
    return false;
}



/*
 * Input: N/A
 * Output: A BSTree with existing elements cleared
 * Description: N/A
 */
void BSTree::clear()
{
    clear(root);
    root = NULL;
}



/*
 * Input: N/A
 * Output: Existing elements of BSTree in in-order
 * Description: N/A
 */
void BSTree::display()
{
	traverse(root);
}



/*
 * Input: Item to be looked up for
 * Output: Pointer to the node containing the item
 * Description: N/A
 */
inline BSTNode* BSTree::lookup(data val)
{
    return lookup(val, root);
}



/*
 * Input: Data item to be looked up for and the pointer to the node search to start from (usually root)
 * Output: Pointer to the node holding the data item
 * Description: N/A
 */
BSTNode* BSTree::lookup(data val, BSTNode* ptr)
{
    while(ptr!= NULL)
    {
        if(ptr->val > val)
            ptr=ptr->left;
        else if(ptr->val < val)
            ptr=ptr->right;
        else
            return ptr;
    }
    return NULL;
}



/*
 * Input: Pointer to the node to be deleted
 * Output: BST with the item deleted
 * Description: N/A
 */
void BSTree::del(BSTNode* z)
{
    BSTNode * y;
    if(z->left == NULL)
        transplant(z,z->right);
    else if(z->right == NULL)
        transplant(z,z->left);
    else
    {
        y = minimum(z->right);
        if(y->p != z)
        {
            transplant(y,y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->p = y;
    }

}



/*
 * Input: N/A
 * Output: Pointer to the node containing the minimum item
 * Description: N/A
 */
BSTNode* BSTree::minimum()
{
    return minimum(root);
}



/*
 * Input: Pointer to a sub-tree
 * Output: Minimum of tree rooted at ptr
 * Description: N/A
 */
BSTNode * BSTree::minimum(BSTNode * ptr)
{
    while(ptr->left != NULL)
        ptr = ptr->left;
    return ptr;
}



/*
 * Input: Pointer to two sub-trees, u & v
 * Output: Replaces sub tree rooted at u with sub tree rooted at v
 * Description: N/A
 */
void BSTree::transplant(BSTNode* u,BSTNode* v)
{
    if(u == root)
        root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    if(v != NULL)
        v->p = u->p;
}



/*
 * Input: Pointer to a sub-tree
 * Output: Existing elements of BSTree in in-order
 * Description: N/A
 */
void BSTree::traverse(BSTNode* T)
{
    if(T == NULL) return;
    traverse(T->left);
    cout << T->val << " ";
    traverse(T->right);

}

void BSTree::clear(BSTNode * root)
{
	if(root == NULL)
		return;
	clear(root->left);
	clear(root->right);
	delete root;
}
