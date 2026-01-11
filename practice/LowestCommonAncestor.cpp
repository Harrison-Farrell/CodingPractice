/*
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in
the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes p and q as the lowest node in T that has both p and q
as descendants (where we allow a node to be a descendant of itself).”

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of
itself according to the LCA definition.
*/

// System includes
#include <algorithm>

// Project includes
#include <spdlog/fmt/ranges.h>
#include <spdlog/spdlog.h>

// Definition for a binary tree node.
class TreeNode {
public:
  // constructor
  TreeNode(int x) : value(x), left(nullptr), right(nullptr) {};
  // values
  int value;
  TreeNode *left;
  TreeNode *right;
};

class Solution {
public:
  // constructor
  Solution() {};

  ~Solution() = default;

  Solution(Solution &copy_constructor) = delete;
  Solution(Solution &&move_constructor) = delete;

  Solution operator=(Solution &copy_assignment) = delete;
  Solution operator=(Solution &&move_assignment) = delete;

  // find the lowest common acestor between p & q in a binary tree
  // param[in] TreeNode* root of tree
  // param[in] TreeNode* p element
  // param[in] TreeNode* q element
  // param[out] TreeNode* lowest common element
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    spdlog::debug("Function called. Value: {}", root->value);

    if (!root || root == p || root == q) {
      return root;
    }
    TreeNode *left_node = lowestCommonAncestor(root->left, p, q);
    TreeNode *right_node = lowestCommonAncestor(root->right, p, q);

    if (left_node && right_node) {
      return root;
    }

    return left_node ? left_node : right_node;
  }
};

int main() {
  spdlog::set_level(spdlog::level::debug);

  Solution computer = Solution();
  // construct the binary tree
  //			   1
  //           /   \
    //          2     3
  //         / \   / \
    //        4  5  6   7
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);

  TreeNode *lowest_common_node =
      computer.lowestCommonAncestor(root, root->left->left, root->left->right);
  if (lowest_common_node == nullptr)
    spdlog::info("No common ancestor found");
  else
    spdlog::info("Lowest commonet element is: {}", lowest_common_node->value);
  return 0;
}