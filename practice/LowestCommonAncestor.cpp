// System includes
#include <algorithm>

// Project includes
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ranges.h>

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

class Solution
{
    public: 
    // constructor
    Solution(){};

    ~Solution() = default;

    Solution(Solution& copy_constructor) = delete;
    Solution(Solution&& move_constructor) = delete;

    Solution operator=(Solution& copy_assignment) = delete;
    Solution operator=(Solution&& move_assignment) = delete;

    // find the lowest common acestor between p & q in a binary tree
    // param[in] TreeNode* root of tree
    // param[in] TreeNode* p element
    // param[in] TreeNode* q element
    // param[out] TreeNode* lowest common element
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        spdlog::debug("Function called. Value: {}", root->value);

        if(!root || root == p || root == q)
        {
            return root;
        }
        TreeNode* left_node = lowestCommonAncestor(root->left, p, q);
        TreeNode* right_node = lowestCommonAncestor(root->right, p, q);

        if(left_node && right_node)
        {
            return root;
        }

        return left_node ? left_node : right_node;
    }

};

int main()
{
    spdlog::set_level(spdlog::level::debug);

    Solution computer = Solution();
  	// construct the binary tree
  	//			   1
    //           /   \
    //          2     3
    //         / \   / \
    //        4  5  6   7 
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    TreeNode* lowest_common_node = computer.lowestCommonAncestor(root, root->left->left, root->left->right);
  	if(lowest_common_node == nullptr)
      	spdlog::info("No common ancestor found");
	else
      	spdlog::info("Lowest commonet element is: {}", lowest_common_node->value);
    return 0;
}