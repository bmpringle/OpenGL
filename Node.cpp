#include<cstdlib>
#include<vector>
#include"vertexLoader.cpp"

class Node {
    public:
        std::string name;
        std::vector<Triangle> vertices;
        std::vector<Node> children;
        float3 pos;

        void addChild(Node child) {
            children.push_back(child);
        }

        Node(std::string name, std::vector<Triangle> vertices, std::vector<Node> children) {
            this->vertices = vertices;
            this->children = children;
            this->pos = float3(0, 0, 0);
        }

        float3 getPos() {
            return pos;
        }

        void setPos(float3 pos_) {
            std::cout << pos_.x << " " << pos_.y << " "  << pos_.z << std::endl;
            this->pos = pos_;
            std::cout << pos.x << " " << pos.y << " "  << pos.z << std::endl;
        }

        std::vector<Triangle> getTriangles() {
            return vertices;
        }

        std::vector<float> getVertices() {
            std::vector<Triangle> tempvertices = vertices;

            std::vector<float> tempverticesfloat = std::vector<float>();

            for(int i=0; i<tempvertices.size(); ++i) {
                float3 v1 = tempvertices[i].v1;
                float3 v2 = tempvertices[i].v2;
                float3 v3 = tempvertices[i].v3;

                float v11 = v1.x;
                float v12 = v1.y;
                float v13 = v1.z;

                float v21 = v2.x;
                float v22 = v2.y;
                float v23 = v2.z;

                float v31 = v3.x;
                float v32 = v3.y;
                float v33 = v3.z;

                tempverticesfloat.push_back(v11);
                tempverticesfloat.push_back(v12);
                tempverticesfloat.push_back(v13);

                tempverticesfloat.push_back(v21);
                tempverticesfloat.push_back(v22);
                tempverticesfloat.push_back(v23);

                tempverticesfloat.push_back(v31);
                tempverticesfloat.push_back(v32);
                tempverticesfloat.push_back(v33);
            }

            for(int i=0; i<children.size(); ++i) {
                for(int j=0; j<children[i].getVertices().size(); ++j) {
                    tempverticesfloat.push_back(children[i].getVertices()[j]);
                }
            }

            for(int i=0; i<tempverticesfloat.size()/3; ++i) {
                float _pos [3];
                _pos[0] = pos.x;
                _pos[1] = pos.y;
                _pos[2] = pos.z;
                
                for(int j=0; j<3; ++j) {
                    tempverticesfloat[3*i+j] = tempverticesfloat[3*i+j] + _pos[j];
                }
            }
            return tempverticesfloat;
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
            return Node("null", std::vector<Triangle>(), std::vector<Node>());
        }
    
    private:
        
};

