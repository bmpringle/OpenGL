#include "Node.cpp"

class Scene {
    public:
        Node root_node = Node("root", std::vector<float>(), std::vector<Node>());

        Node lookUpNode(char* name) {
            return root_node.lookUpNode(name);
        }
};