/*
In this problem, we are given the roots of a binary tree and two nodes from this tree. 
Our task is to find the lowest common ancestor (LCA) of these two nodes. 
The LCA of two nodes p and q is defined as the deepest node in the tree 
that has both p and q as descendants (with a node being allowed to be a descendant of itself).
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int value;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
 * };
 */

 class TreeNode 
 {
    public:
        int value; 
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
 };
 
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    
    if(!root) return nullptr;
    
    if(root == p || root == q){
        return root;
    }

    TreeNode* leftAns = lowestCommonAncestor(root->left, p, q);
    TreeNode* rightAns = lowestCommonAncestor(root->right, p, q);

    if(leftAns && rightAns) return root;
    else if(leftAns && !rightAns) return leftAns;
    else if(!leftAns && rightAns) return rightAns;
    else return nullptr;
}