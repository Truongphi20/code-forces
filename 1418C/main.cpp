#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <map>
#include <algorithm> 

// Forward declartions
class Linker;
class LinkerNode;
class Node;

class Node
{
    public:
    Node* zero {nullptr};
    Node* one {nullptr};
    Node* two {nullptr};
    Node* parent {nullptr};
    Linker* subtree_linker {nullptr};
    LinkerNode* linker_node {nullptr};

    int skip_num;
    std::bitset<1> boss_level;
    std::string fighter;
    std::bitset<2> leaf_value;
    int tree_level;

    Node *previousSessonNode();
    friend std::ostream& operator<<(std::ostream& os, const Node& obj);


};

class LinkerNode
{
    public:

    Node* parent {nullptr};
    Linker* linker {nullptr}; 

    int skip_num;
    int tree_level;
    std::string linker_key;
};

class Linker
{
    public:
    Node* head_node {nullptr};
    int subtree_length;
    int min_skip_num = 0;
    int max_tree_level;

    void findMinSkipInSubtree();
    void travelNodes(Node *&node);
};

// Supplement methods
void Linker::findMinSkipInSubtree()
{ 
    if (this->min_skip_num != 0) return;
    min_skip_num = 1000;
    Node *current_node = this->head_node;
    travelNodes(current_node);
}

void Linker::travelNodes(Node *&node)
{
    if (node->tree_level == max_tree_level && node->skip_num < min_skip_num) 
    {
        this->min_skip_num = node->skip_num;
    }

    if (node->linker_node != nullptr && node->linker_node->skip_num < min_skip_num)
    {
        this->min_skip_num = node->linker_node->skip_num;
    }

    if (node->zero != nullptr) travelNodes(node->zero);
    if (node->one != nullptr) travelNodes(node->one);
    if (node->two != nullptr) travelNodes(node->two);
    
    return;
}

Node *Node::previousSessonNode()
{
    Node *traceback_node = parent;
    while(true)
    {
        if (traceback_node->leaf_value == 0 || traceback_node->leaf_value == 2) 
            return traceback_node;

        traceback_node = traceback_node->parent;
    }
}

std::ostream& operator<<(std::ostream& os, const Node& obj)
{
    os << "Node(skip_num  = "<< obj.skip_num << ",\n";
    os << "     boss_level= "<< obj.boss_level << ",\n";
    os << "     fighter   = "<< obj.fighter << ",\n";
    os << "     leaf_value= "<< obj.leaf_value << ",\n";
    os << "     tree_level= "<< obj.tree_level << ",\n";
    os << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const LinkerNode& obj)
{
    os << "LinkerNode(skip_num  = "<< obj.skip_num << ",\n";
    os << "           tree_level= "<< obj.tree_level << ",\n";
    os << "           linker_key= "<< obj.linker_key << ",\n";
    os << ")";
    return os;
}

class FightingTree
{
    public:
    FightingTree(std::vector<std::bitset<1>> boss_list):
        boss_list(boss_list),
        boss_number(static_cast<int>(boss_list.size()))
    {
        rootNode = new Node;
        rootNode->fighter = "";
        rootNode->boss_level = 0;
        rootNode->leaf_value = 0;
        rootNode->skip_num = 0;
        rootNode->tree_level = 0;

        std::vector<Node*> initial_node_list { rootNode };

        this->addTreeNodes(initial_node_list);

    }

    Node* rootNode;

    // ~FightingTree()
    // {
    //     clearTree(rootNode);
    // }

    void addTreeNodes(std::vector<Node*> &parent_nodes)
    {
        // Brake
        if (parent_nodes.empty()) return;
        int tree_level {parent_nodes[0]->tree_level};
        if (tree_level == this->boss_number){
            for (const auto &node: parent_nodes){
                if (node->leaf_value != 1) youngest_nodes.push_back(node);
            }
            return;
        }
        // Filter parent nodes
        // int remain_available_skip {this->getRemainSkip(tree_level+1)};
        // int min_skip {this->findMinSkip(parent_nodes)};
        // int threshold_skip {remain_available_skip + min_skip};

        // std::vector<Node*> filterd_parent_nodes;
        // for (Node *node: parent_nodes){
        //     if (node->skip_num <= threshold_skip) filterd_parent_nodes.push_back(node);
        // }
        // parent_nodes.clear();

        // Add new nodes
        std::vector<Node*> new_parent_nodes;
        for (Node *&node: parent_nodes)
        {
            // Check cache subtree
            std::vector<std::bitset<1>> remain_bosses(this->boss_list.begin() + tree_level, this->boss_list.end());
            std::string key_string = getStringKey(remain_bosses, node->fighter, node->leaf_value);
            if (this->linker_map.count(key_string) > 0)
            {
                Linker *subtree_linker = this->linker_map[key_string];
                LinkerNode* linker_node = new LinkerNode;
                linker_node->linker = subtree_linker;
                linker_node->parent = node;
                linker_node->linker_key = key_string;
                node->linker_node = linker_node;

                linker_node->tree_level = node->tree_level;
                this->linker_nodes.push_back(linker_node);
                continue;
            }
            else 
            {
                Linker *subtree_linker = new Linker;
                subtree_linker->head_node = node;
                subtree_linker->subtree_length = this->boss_number - tree_level + 1;
                subtree_linker->max_tree_level = boss_number;
                this->linker_map[key_string] = subtree_linker;
            }

            // Add nodes
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

        parent_nodes.clear();
        this->addTreeNodes(new_parent_nodes);

        // Add min_skip to LinkerNode nodes
        for (int index = this->linker_nodes.size() - 1; index >= 0 ; --index)
        {
            Linker *subtree_linker = linker_nodes[index]->linker;
            subtree_linker->findMinSkipInSubtree();
            linker_nodes[index]->skip_num = linker_nodes[index]->parent->skip_num 
                                                + subtree_linker->min_skip_num 
                                                - subtree_linker->head_node->skip_num;
        }
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
        for (LinkerNode *&node: linker_nodes) std::cout << *node << '\n';
    }

    template<typename T>
    int findMinSkip(std::vector<T*> &node_vector)
    {
        int min_skip {this->boss_number};
        for (T *&node: node_vector)
        {
            if (node->skip_num < min_skip) min_skip = node->skip_num;
        }
        return min_skip;
    }

    int getFinalMinSkip()
    {
        int min_node = this->findMinSkip<Node>(this->youngest_nodes);

        if (this->linker_nodes.size() > 0)
        {
            int min_link_node = this->findMinSkip<LinkerNode>(this->linker_nodes);
            min_node = std::min(min_node,min_link_node);
        }

        return min_node;
    }

    void clearTree(Node *&node)
    {
        if (node->zero != nullptr) clearTree(node->zero);
        if (node->one != nullptr) clearTree(node->one);
        if (node->two != nullptr) clearTree(node->two);
        if (node->linker_node != nullptr && node->linker_node->linker != nullptr) 
        {
            delete node->linker_node->linker;
            node->linker_node->linker = nullptr;
        }

        if (node->linker_node != nullptr) 
        {
            delete node->linker_node;
            node->linker_node = nullptr;
        }
        
        delete node;
        node = nullptr;
 
    }

    private:
    std::vector<std::bitset<1>> boss_list;
    int boss_number;
    std::vector<Node*> youngest_nodes;
    std::vector<LinkerNode*> linker_nodes;
    static std::map<std::string, Linker*> linker_map;

    int getRemainSkip(int tree_level)
    {
        int remainSkip {0};
        for (int index = tree_level - 1; index < boss_number; ++index)
        {
            if (this->boss_list[index] == 1) remainSkip += 1;
        }

        return remainSkip;
    }

    std::string getStringKey(const std::vector<std::bitset<1>>& bitsetVec, std::string fighter, std::bitset<2>& leafValue) {
        std::string keyword;
    
        for (const auto& bit : bitsetVec) {
            keyword += bit.test(0) ? '1' : '0';
        }

        keyword += fighter;
        keyword += leafValue.to_string();
    
        return keyword;
    }

};

std::map<std::string, Linker*> FightingTree::linker_map;

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
    //     FightingTree tree(boss_list);
    //     std::cout << tree.getFinalMinSkip() << '\n';

    //     if (i == test_case_num - 1) tree.clearTree(tree.rootNode);
    // }

    // Testing
    // int boss_number {4};
    std::vector<std::bitset<1>> boss_list{ 1,0,1,1,0,1,1,1,1,0,1,0,1,0 };
    // for (const std::bitset<1> bit: boss_list) std::cout << bit << '\n'; 
    FightingTree tree(boss_list);
    tree.printYoungestNodes();
    std::cout << tree.getFinalMinSkip() << '\n';

    

    return 0;
}