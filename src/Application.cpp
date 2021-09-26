#include "Application.hpp"

void Application::init(World & world)
{
    Camera & cam = world.getCamera();
    LightSource & sun = world.getLightSource();

    cam.setPosition({0.0f, 0.0f, 0.0f});
    // rotate cam to look at X- (this way Y+ and Z+ looks more natural for a 2D environment, aka. Y+ is on the right)
    cam.rotateYaw(PI);

    sun.setPosition({0.0f, 0.0f, 0.0f});

    // background
    auto cube = world.makeCube({0.9f, 0.9f, 0.9f});
    cube->setPosition({-10.0f, 0.0f, 0.0f});
    cube->scale({0.1f, 10.0f, 10.0f});

    // center
    cube = world.makeCube({0.0f, 0.0f, 0.0f});
    cube->setPosition({-9.0f, 0.0f, 0.0f});
    cube->scale(0.05f);

    // axe Y+
    cube = world.makeCube({1.0f, 0.0f, 0.0f});
    cube->setPosition({-9.0f, 1.0f, 0.0f});
    cube->scale(0.05f);

    // axe Z+
    cube = world.makeCube({0.0f, 1.0f, 0.0f});
    cube->setPosition({-9.0f, 0.0f, 1.0f});
    cube->scale(0.05f);

    // Construction du rendu graphique de la particule
    particleRendered = world.makeCube({ 0.2f, 0.2f, 0.2f });
    particleRendered->scale(0.2f);

    // Construction de la particule avec les données spécifiées par l'utilisateur dans ImGUI - A CHANGER
    particle.setMass(1.0f);
    particle.setPosition(positionInit);
    particle.setVelocity(velocityInit);

    // Initialisation des forces s'appliquant sur le projectile
    Vector3f g(0, 0, -9.81);
    float mass = 1.0f / particle.getInverseMass();
    forceList = { mass * g };
}

void Application::update(World & world, float deltaTime)
{
    static constexpr float TIMESTEP = 1.0f / 60.0f;
    static float elapsedTime = 0.0f;
    elapsedTime += deltaTime;

    // Si le temps écoulé est supérieur à TIMESTEP, on entre dans la boucle
    while (elapsedTime >= TIMESTEP)
    {
        elapsedTime -= TIMESTEP;
        // On update la position du projectile ainsi que de son affichage graphique
        particle.integrate(forceList, TIMESTEP);
        particleRendered->setPosition(particle.getPosition());
    }

    if(world.getWindow().isKeyPressed(GLFW_KEY_R))
    {
        particle.setPosition(positionInit);
        particle.setVelocity(velocityInit);
    }
}
