#include "Scene.cpp"
#include <random>

class Logic {
    public:

        Scene setup(Scene scene) {
            time(&time_old);

            Node p1 = Node("paddle1", loadTriangles("paddle.txt"));
            Node p2 = Node("paddle2", loadTriangles("paddle.txt"));
            Node ball = Node("ball", loadTriangles("ball.txt"));
            p1.setPos(float3(-1, -0.15, 0));
            p2.setPos(float3(1-0.02, -0.15, 0));

            scene.root_node.addChild(p1);
            scene.root_node.addChild(p2);
            scene.root_node.addChild(ball);
            srand(time(0));
            float ballyvel = (rand() % 100 + 1);
            ballvec.y = ballyvel/1000;

            return scene;
        }

        Scene doLogicTick(Scene scene, GLFWwindow* window) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            scene.updateAspectRatio(width, height);
            time_t temp;
            time(&temp);
            if(difftime(temp, time_old) >= 1/60) {
                time_old = temp;
                if(scene.lookUpNode("ball") == nullptr) {
                    std::cout << "nullnode unexpected!" << std::endl;
                }else {
                    float ballRadius = 0.05;
                    if(scene.lookUpNode("ball")->getPos().y >= 1-ballRadius || scene.lookUpNode("ball")->getPos().y <= -1+ballRadius) {
                        ballvec.y = -ballvec.y;
                    }
                    scene.lookUpNode("ball")->changePos(ballvec);
                }
            }
            return scene;
        }

    private:
        time_t time_old;
        float3 ballvec = float3(0.0083, 0, 0);
};