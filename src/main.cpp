#include <iostream>
#include <map>
#include <functional>

#include "render/VulkanApplication.hpp"
#include "render/IApplication.hpp"

class Application : public IApplication
{
    static constexpr float PI = glm::pi<float>();

    std::shared_ptr<Entity> platform;

    virtual void init(World & world) override
    {
        Camera & cam = world.getCamera();

        cam.setPosition({2.0f, 2.0f, 3.0f});
        cam.setRotation(-3.0f * PI/4.0f, -PI/4.0f);

        platform = world.makeEntity(
        {
            {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
            {{0.5f , -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
            {{0.5f ,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        },
        {
            0, 1, 2, 2, 3, 0,
        });

        auto cube = world.makeCube();
        cube->scale(0.5f);
        cube->translate({0.0f, 0.0f, -2.0f});

        auto square = world.makeSquare();
        square->scale(2.0f);
        square->translate({0.0f, 0.0f, -5.0f});

        auto disk = world.makeDisk();
        disk->scale(0.5f);
        disk->translate({3.0f, 0.0f, 0.3f});
    }

    virtual void update(World & world, float deltaTime) override
    {
        const float rotationSpeed = 1.0f / 3.0f * PI; // rad/s

        platform->rotate(deltaTime * rotationSpeed, {0.0f, 0.0f, 1.0f});

        updateCamera(world, deltaTime);
    }

    void updateCamera(World & world, float deltaTime)
    {
        const Window & win = world.getWindow();
              Camera & cam = world.getCamera();

        const float rotationSpeed = 1.0f * PI; // rad/s
        const float moveSpeed     = 0.1f; // unit/s

        static std::vector<std::tuple<int, std::function<void ()>>> keymap = 
        {
            { GLFW_KEY_A, [&](){ cam.rotateYaw(   deltaTime * rotationSpeed); } },
            { GLFW_KEY_D, [&](){ cam.rotateYaw(  -deltaTime * rotationSpeed); } },
            { GLFW_KEY_W, [&](){ cam.rotatePitch( deltaTime * rotationSpeed); } },
            { GLFW_KEY_S, [&](){ cam.rotatePitch(-deltaTime * rotationSpeed); } },

            { GLFW_KEY_LEFT , [&](){ cam.move( moveSpeed * glm::vec3{0.0f, 1.0f, 0.0f}); } },
            { GLFW_KEY_RIGHT, [&](){ cam.move(-moveSpeed * glm::vec3{0.0f, 1.0f, 0.0f}); } },
            { GLFW_KEY_UP   , [&](){ cam.move( moveSpeed * glm::vec3{1.0f, 0.0f, 0.0f}); } },
            { GLFW_KEY_DOWN , [&](){ cam.move(-moveSpeed * glm::vec3{1.0f, 0.0f, 0.0f}); } },
            { GLFW_KEY_O    , [&](){ cam.move( moveSpeed * glm::vec3{0.0f, 0.0f, 1.0f}); } },
            { GLFW_KEY_L    , [&](){ cam.move(-moveSpeed * glm::vec3{0.0f, 0.0f, 1.0f}); } },
        };

        for(const auto & [key, fun] : keymap)
        {
            if(win.isKeyPressed(key)) fun();
        }
    }
};

int main() 
{
    VulkanApplication app{std::make_shared<Application>()};

    try 
    {
        app.run();
    } 
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


#include "Vector3f.hpp"
#include "Particle.hpp"


int _main()
{
    Vector3f position{ 0, 0, 0 };
    Particle particle{ position, 50, 0.95 };
    Vector3f initialVelocity{ 5, 5, 5 };
    particle.setInitialVelocity(initialVelocity);
    particle.integrate();
    return 0;
}