#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <map>

class Node
{
    public:
    Node* zero {nullptr};
    Node* one {nullptr};
    Node* two {nullptr};
    Node* parent {nullptr};

    int skip_num;
    std::bitset<1> boss_level;
    std::string fighter;
    std::bitset<2> leaf_value;

    Node *previousSessonNode()
    {
        Node *traceback_node = parent;
        while(true)
        {
            if (traceback_node->leaf_value == 0 || traceback_node->leaf_value == 2) return traceback_node;
            traceback_node = traceback_node->parent;
        }
    }

};

class FightingTree
{
    public:
    FightingTree(std::vector<std::bitset<1>> boss_list):
        boss_list(boss_list)
    {
        rootNode.fighter = "myfriend";
        rootNode.boss_level = boss_list[0];
        rootNode.leaf_value = 0;
        if (rootNode.boss_level == 0) 
            rootNode.skip_num = 0;
        else rootNode.skip_num = 1;

        rootNode.one = addTreeNodes(&rootNode, 0, 2);
        rootNode.zero = addTreeNodes(&rootNode, 1, 2);
    }

    Node *addTreeNodes(Node *parent_node, std::bitset<2> leaf_value, int tree_level)
    {
        // Brake
        if (tree_level > int(boss_list.size())) return nullptr;
        tree_level += 1;

        // Setting up parental stuffs
        Node *child_node = new Node;
        child_node->parent = parent_node;
        child_node->leaf_value = leaf_value;

        if (leaf_value == 1) child_node->two = addTreeNodes(child_node, 2, tree_level);
        if (leaf_value == 0 || leaf_value == 2)
        {
            child_node->zero = addTreeNodes(child_node, 0, tree_level);
            child_node->one = addTreeNodes(child_node, 1, tree_level);
        }

        // Setting up value of node
        child_node->boss_level = this->boss_list[tree_level-1];

        Node *privious_ss_node = child_node->previousSessonNode();
        if (privious_ss_node->fighter == "myfriend") child_node->fighter = "me";
        else if (privious_ss_node->fighter == "me") child_node->fighter = "myfriend";

        if (child_node->fighter == "myfriend" && child_node->boss_level == 1) {
            child_node->skip_num = parent_node->skip_num + 1;
        }

        return child_node;

    }

    private:
    std::vector<std::bitset<1>> boss_list;
    Node rootNode;

};








int main()
{
    // int test_case_num;
    // std::cin >> test_case_num;

    // for (int i=0; i<test_case_num; i++)
    // {
    //     // Read boss number
    //     int boss_number;
    //     std::cin >> boss_number;
        
    //     // Read list of boss
    //     std::vector<std::bitset<1>> boss_list;
    //     for (int i=0; i < boss_number; i++)
    //     {
    //         std::bitset<1> bit;
    //         std::cin >> bit;
    //         boss_list.push_back(bit);
    //     }

    //     // Handle bosses
    //     BossHandle(boss_number, boss_list);
    // }

    //// Testing
    // int boss_number {4};
    std::vector<std::bitset<1>> boss_list{ 1, 0, 0, 1 };
    // for (const std::bitset<1> bit: boss_list) std::cout << bit << '\n'; 
    FightingTree tree(boss_list);

    

    return 0;
}