#pragma once
#include "Node.h"

class Scene {
    public:
        Node root_node;
        float aspectRatio = 1;

        Scene();

        std::vector<float> getRenderVertices();

        void updateAspectRatio(float x, float y);

        Node* lookUpNode(char* name);
};