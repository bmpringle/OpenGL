#include "Engine.h"

class AdventureLogic : public Logic {
        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

        }

        void setup(Scene& scene) {

        }

        void doLogicTick(Scene& scene, GLFWwindow* window) {

        }
};


int main() {
    AdventureLogic logic = AdventureLogic();
    Engine engine = Engine(logic);
    engine.runEngine();
}