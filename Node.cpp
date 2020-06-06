#include "Node.h"

void Node::addChild(Node child) {
    children.push_back(child);
}

Node::Node(std::string name, std::vector<Vertex> vertices, std::vector<Node> children) {
    this->vertices = vertices;
    this->children = children;
    this->pos = float3(0, 0, 0);
    this->name = name;
}

float3 Node::getPos() {
    return pos;
}

void Node::setPos(float3 pos_) {
    this->pos = pos_;
}

void Node::changePos(float3 _pos) {
    pos = float3(pos.x+_pos.x, pos.y+_pos.y, pos.z+_pos.z);
}

std::vector<Vertex> Node::getVertices() {
    return vertices;
}

std::vector<float> Node::getVectorBuffer() {
    std::vector<Vertex> tempvertices = vertices;
    std::vector<float> floats= std::vector<float>();

    for(int i=0; i<tempvertices.size(); ++i) {
        floats.push_back(tempvertices[i].v1.x);
        floats.push_back(tempvertices[i].v1.y);
        floats.push_back(tempvertices[i].v1.z);

        floats.push_back(tempvertices[i].color.x);
        floats.push_back(tempvertices[i].color.y);
        floats.push_back(tempvertices[i].color.z);
        floats.push_back(tempvertices[i].color.w);
    }

    for(int i=0; i<children.size(); ++i) {
        std::vector<float> childverts = children[i].getVectorBuffer();
        for(int j=0; j<childverts.size(); ++j) {
            floats.push_back(childverts[j]);
        }
    }

    for(int i=0; i<floats.size()/7; ++i) {
        floats[7*i] = floats[7*i]+pos.x;
        floats[7*i+1] = floats[7*i+1]+pos.y;
        floats[7*i+2] = floats[7*i+2]+pos.z;
    }

    return floats;
}

Node* Node::lookUpNode(char* _name) {
    if(name == _name) {
        return this;
    }
    for(int i=0; i<children.size(); ++i) {
        if(children[i].lookUpNode(_name) != nullptr) {
            return children[i].lookUpNode(_name);
        } 
    }
    return nullptr;
}