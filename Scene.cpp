#include "Node.cpp"

class Scene {
    public:
        Node root_node;
        float aspectRatio = 1;

        Scene() : root_node("root", std::vector<Triangle>(), std::vector<Node>()) {
        }

        std::vector<float> getRenderVertices() {
            std::vector<float> verts = root_node.getVertices();
            for(int i=0; i<verts.size()/3; ++i) {
                verts[i*3] = verts[i*3]/aspectRatio;
            }
            return verts;
        }

        void updateAspectRatio(float x, float y) {
            aspectRatio = x/y;
        }

        Node lookUpNode(char* name) {
            return root_node.lookUpNode(name);
        }
};