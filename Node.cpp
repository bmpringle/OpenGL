#include<cstdlib>
#include<vector>

class Node {
    public:
        char* name = "";
        std::vector<float> vertices = std::vector<float>();
        std::vector<Node> children = std::vector<Node>();

        Node(char* name, std::vector<float> vertices, std::vector<Node> children) {
            this->name = name;
            this->vertices = vertices;
            this->children = children;
            this->pos.push_back(0);
            this->pos.push_back(0);
            this->pos.push_back(0);
        }

        std::vector<float> getPos() {
            return pos;
        }

        void setPos(std::vector<float> pos) {
            this->pos = pos;
        }

        std::vector<float> getVertices() {
            std::vector<float> tempvertices = vertices;

            for(int i=0; i<children.size(); ++i) {
                for(int j=0; j<children[i].getVertices().size(); ++j) {
                    tempvertices.push_back(children[i].getVertices()[j]);
                }
            }

            for(int i=0; i<tempvertices.size()/3; ++i) {
                for(int j=0; j<3; ++j) {
                    tempvertices[3*i+j] = tempvertices[3*i+j] + pos[j];
                }
            }
            return tempvertices;
        }

        Node lookUpNode(char* name) {
            if(this->name == name) {
                return *this;
            }
            for(int i=0; i<children.size(); ++i) {
                if(children[i].lookUpNode(name).name != "null") {
                    return children[i].lookUpNode(name);
                } 
            }
            return Node("null", std::vector<float>(), std::vector<Node>());
        }
    
    private:
        std::vector<float> pos = std::vector<float>();
};

