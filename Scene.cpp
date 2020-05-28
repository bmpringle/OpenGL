#include "Node.cpp"

class Scene {
    public:
        Node root_node;
        float aspectRatio = 1;

        Scene() : root_node("root", std::vector<Vertex>(), std::vector<Node>({Node("border", loadTriangles("border.txt"))})) {
        }

        std::vector<float> getRenderVertices() {
            std::vector<float> verts = root_node.getVectorBuffer();
            for(int i=0; i<verts.size()/7; ++i) {
                verts[i*7] = verts[i*7]/aspectRatio;
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