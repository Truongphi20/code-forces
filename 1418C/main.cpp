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
    int tree_level;

    Node *previousSessonNode()
    {
        Node *traceback_node = parent;
        while(true)
        {
            if (traceback_node->leaf_value == 0 || traceback_node->leaf_value == 2) 
                return traceback_node;

            traceback_node = traceback_node->parent;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& obj)
    {
        os << "Node(skip_num  = "<< obj.skip_num << ",\n";
        os << "     boss_level= "<< obj.boss_level << ",\n";
        os << "     fighter   = "<< obj.fighter << ",\n";
        os << "     leaf_value= "<< obj.leaf_value << ",\n";
        os << "     tree_level= "<< obj.tree_level << ",\n";
        os << ")";
        return os;
    }

};

class FightingTree
{
    public:
    FightingTree(std::vector<std::bitset<1>> boss_list):
        boss_list(boss_list)
    {
        rootNode->fighter = "";
        rootNode->boss_level = 0;
        rootNode->leaf_value = 0;
        rootNode->skip_num = 0;
        rootNode->tree_level = 0;

        std::vector<Node*> initial_node_list { rootNode };

        this->addTreeNodes(initial_node_list);

    }

    ~FightingTree()
    {
        clearTree(&rootNode);
    }

    void addTreeNodes(std::vector<Node*> &parent_nodes)
    {
        // Brake
        int tree_level {parent_nodes[0]->tree_level};
        if (tree_level == this->boss_number){
            for (const auto &node: parent_nodes){
                if (node->leaf_value != 1) youngest_nodes.push_back(node);
            }
            return;
        }
        // Filter parent nodes
        int remain_available_skip {this->getRemainSkip(tree_level+1)};
        int min_skip {this->findMinSkip(parent_nodes)};
        int threshold_skip {remain_available_skip + min_skip};

        std::vector<Node*> filterd_parent_nodes;
        for (Node *node: parent_nodes){
            if (node->skip_num <= threshold_skip) filterd_parent_nodes.push_back(node);
        }
        parent_nodes.clear();

        // Add new nodes
        std::vector<Node*> new_parent_nodes;
        for (Node *node: filterd_parent_nodes)
        {
        if(node->leaf_value == 0 || node->leaf_value == 2)
        {
            Node* zero_node = this->addNode(node, 0);
            node->zero = zero_node;
            new_parent_nodes.push_back(zero_node);

            Node* one_node = this->addNode(node, 1);
            node->one = one_node;
            new_parent_nodes.push_back(one_node);
        }
        if(node->leaf_value == 1)
        {
            Node* two_node = this->addNode(node, 2);
            node->two = two_node;
            new_parent_nodes.push_back(two_node);
        }
       }

       this->addTreeNodes(new_parent_nodes);
       filterd_parent_nodes.clear();
    }

    Node* addNode(Node* node, std::bitset<2> leaf_value)
    {
        // Setup phylogenic
        Node *child_node = new Node;
        child_node->parent = node;

        // Setup values
        child_node->tree_level = node->tree_level + 1; 
        child_node->boss_level = this->boss_list[child_node->tree_level - 1];
        child_node->leaf_value = leaf_value;
        
        Node *privious_node = child_node->previousSessonNode();
        if (privious_node->fighter == "myfriend") child_node->fighter = "me";
        if (privious_node->fighter == "me") child_node->fighter = "myfriend";
        if (privious_node->fighter == "") child_node->fighter = "myfriend";

        
        if (child_node->fighter == "myfriend" && child_node->boss_level == 1){
            child_node->skip_num = node->skip_num + 1;
        }else{
            child_node->skip_num = node->skip_num;
        }

        return child_node;
    }

    std::vector<Node*> getChildrenNodes()
    {
        return youngest_nodes;
    }

    void printYoungestNodes()
    {
        for (Node *&node: youngest_nodes) std::cout << *node << '\n';
    }

    int findMinSkip(std::vector<Node*> &node_vector)
    {
        int min_skip {this->boss_number};
        for (Node *&node: node_vector)
        {
            if (node->skip_num < min_skip) min_skip = node->skip_num;
        }
        return min_skip;
    }

    int getFinalMinSkip()
    {
        return this->findMinSkip(this->youngest_nodes);
    }

    private:
    std::vector<std::bitset<1>> boss_list;
    int boss_number {static_cast<int>(boss_list.size())};
    Node *rootNode = new Node;
    std::vector<Node*> youngest_nodes;

    void clearTree(Node **node)
    {
        if ((*node)->zero != nullptr) clearTree(&(*node)->zero);
        if ((*node)->one != nullptr) clearTree(&(*node)->one);
        if ((*node)->two != nullptr) clearTree(&(*node)->two);
        
        delete *node;
        *node = nullptr;
 
    }

    int getRemainSkip(int tree_level)
    {
        int remainSkip {0};
        for (int index = tree_level - 1; index < boss_number; ++index)
        {
            if (this->boss_list[index] == 1) remainSkip += 1;
        }

        return remainSkip;
    }

};



int main()
{
    int test_case_num;
    std::cin >> test_case_num;

    for (int i=0; i<test_case_num; i++)
    {
        // Read boss number
        int boss_number;
        std::cin >> boss_number;
        
        // Read list of boss
        std::vector<std::bitset<1>> boss_list;
        for (int i=0; i < boss_number; i++)
        {
            std::bitset<1> bit;
            std::cin >> bit;
            boss_list.push_back(bit);
        }

        // Handle bosses
        FightingTree tree(boss_list);
        std::cout << tree.getFinalMinSkip() << '\n';
    }

    // // Testing
    // // int boss_number {4};
    // std::vector<std::bitset<1>> boss_list{ 1, 1, 1 };
    // // for (const std::bitset<1> bit: boss_list) std::cout << bit << '\n'; 
    // FightingTree tree(boss_list);
    // tree.printYoungestNodes();
    // std::cout << tree.getFinalMinSkip() << '\n';

    

    return 0;
}