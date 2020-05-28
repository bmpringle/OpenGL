#include "Scene.cpp"

class Logic {
    public:

        Scene setup(Scene scene) {
            Node p1 = Node("paddle1", loadTriangles("paddle.txt"));
            Node p2 = Node("paddle2", loadTriangles("paddle.txt"));
            Node ball = Node("ball", loadTriangles("ball.txt"));
            p1.setPos(float3(-1, -0.15, 0));
            p2.setPos(float3(1-0.02, -0.15, 0));

            scene.root_node.addChild(p1);
            scene.root_node.addChild(p2);
            scene.root_node.addChild(ball);
            return scene;
        }

        Scene doLogicTick(Scene scene, GLFWwindow* window) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            scene.updateAspectRatio(width, height);
            return scene;
        }
};