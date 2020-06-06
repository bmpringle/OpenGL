#pragma once

#include<cstdlib>
#include<vector>
#include"VertexLoader.cpp"

class Node {
    public:
        std::string name;
        std::vector<Vertex> vertices;
        std::vector<Node> children;
        float3 pos;

        void addChild(Node child);

        Node(std::string name, std::vector<Vertex> vertices = std::vector<Vertex>(), std::vector<Node> children = std::vector<Node>());

        float3 getPos();

        void setPos(float3 pos_);

        void changePos(float3 _pos);

        std::vector<Vertex> getVertices();

        std::vector<float> getVectorBuffer();

        Node* lookUpNode(char* _name);
};