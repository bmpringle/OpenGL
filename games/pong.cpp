#include "Engine.h"

class PongLogic : public Logic {
        public:

        int movePaddleLeft = 0;
        int movePaddleRight = 0;
        bool reset = false;
        int paddleHits = 0;

        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override {
            if(key == GLFW_KEY_R) {
                if(action ==GLFW_PRESS) {
                    reset = true;
                }
                if(action == GLFW_RELEASE) {
                    reset = false;
                }
            }

            if(key == GLFW_KEY_W) {
                if(action == GLFW_PRESS) {
                    movePaddleLeft = 1;
                }
                if(action == GLFW_RELEASE) {
                    if(movePaddleLeft != -1) {
                        movePaddleLeft = 0;
                    }
                }
            }
            if(key == GLFW_KEY_S) {
                if(action == GLFW_PRESS) {
                    movePaddleLeft = -1;
                }
                if(action == GLFW_RELEASE) {
                    if(movePaddleLeft != 1) {
                        movePaddleLeft = 0;
                    }
                }
            }

            if(key == GLFW_KEY_UP) {
                if(action == GLFW_PRESS) {
                    movePaddleRight = 1;
                }
                if(action == GLFW_RELEASE) {
                    if(movePaddleRight != -1) {
                        movePaddleRight = 0;
                    }
                }
            }
            if(key == GLFW_KEY_DOWN) {
                if(action == GLFW_PRESS) {
                    movePaddleRight = -1;
                }
                if(action == GLFW_RELEASE) {
                    if(movePaddleRight != 1) {
                        movePaddleRight = 0;
                    }
                }
            }
        }

        void setup(Scene& scene) override {
            time(&time_old);

            Node p1 = Node("paddleleft", loadTriangles("paddle.txt"));
            Node p2 = Node("paddleright", loadTriangles("paddle.txt"));
            Node ball = Node("ball", loadTriangles("ball.txt"));
            p1.setPos(float3(-1, -0.15, 0));
            p2.setPos(float3(1-0.02, -0.15, 0));

            scene.root_node.addChild(p1);
            scene.root_node.addChild(p2);
            scene.root_node.addChild(ball);
            srand(time(NULL));

            float distancepersecond = 1;

            float ballyvel = (rand() % 100)/(100/distancepersecond);

            float ballxvel = sqrt(distancepersecond*distancepersecond-ballyvel*ballyvel);
            ballvec.y = ballyvel/60;
            ballvec.x = ballxvel/60;
        }

        void doLogicTick(Scene& scene, GLFWwindow* window) override {
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
                    float paddleWidth = 0.02;
                    float paddleHeight = 0.15;

                    if(scene.lookUpNode("ball")->getPos().y >= 1-ballRadius || scene.lookUpNode("ball")->getPos().y <= -1+ballRadius) {
                        ballvec.y = -ballvec.y;
                    }
                    if(scene.lookUpNode("ball")->getPos().x >= 1-ballRadius || scene.lookUpNode("ball")->getPos().x <= -1+ballRadius) {
                        ballvec = float3();
                    }

                    float3 ball = scene.lookUpNode("ball")->getPos();
                    float bBottom = ball.y - ballRadius;
                    float bTop = ball.y + ballRadius;

                    float3 paddleRight = scene.lookUpNode("paddleright")->getPos();
                    float rBottom = paddleRight.y - paddleHeight + paddleHeight;
                    float rTop = paddleRight.y + paddleHeight + paddleHeight;

                    if(rBottom <= bTop && rTop >= bBottom) {
                        if(ball.x+ballRadius >= paddleRight.x) {
                            ballvec.x = -ballvec.x;
                        }
                    }

                    float3 paddleLeft = scene.lookUpNode("paddleleft")->getPos();
                    float lBottom = paddleLeft.y - paddleHeight + paddleHeight;
                    float lTop = paddleLeft.y + paddleHeight + paddleHeight;

                    if(lBottom <= bTop && lTop >= bBottom) {
                        if(ball.x-ballRadius <= paddleLeft.x+paddleWidth) {
                            ballvec.x = -ballvec.x;
                        }
                    }

                    scene.lookUpNode("paddleleft")->changePos(float3(0, movePaddleLeft*0.025, 0));
                    scene.lookUpNode("paddleright")->changePos(float3(0, movePaddleRight*0.025, 0));

                    scene.lookUpNode("ball")->changePos(float3(ballvec.x*(1+paddleHits/10), ballvec.y*(1+paddleHits/10), ballvec.z));

                    if(reset == true) {
                        scene.lookUpNode("ball")->setPos(float3());
                        scene.lookUpNode("paddleleft")->setPos(float3(-1, -0.15, 0));
                        scene.lookUpNode("paddleright")->setPos(float3(1-0.02, -0.15, 0));

                        float distancepersecond = 1;

                        float ballyvel = (rand() % 100)/(100/distancepersecond);

                        float ballxvel = sqrt(distancepersecond*distancepersecond-ballyvel*ballyvel);
                        ballvec.y = ballyvel/60;
                        ballvec.x = ballxvel/60;
                        paddleHits = 0;
                    }
                }
            }
        }

    private:
        time_t time_old;
        float3 ballvec = float3(0.0083, 0, 0);
};

int main() {
    PongLogic logic = PongLogic();
    Engine engine = Engine(logic);
    engine.runEngine();
}