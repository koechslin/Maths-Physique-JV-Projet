#include "physics/contacts/WallContactGenerator.hpp"

WallContactGenerator::WallContactGenerator(Vector3f directionWidth, Vector3f directionLength, float length, float width, float thickness, Vector3f centerPosition, Particle * otherParticle, float restitution) :
    m_directionWidth{directionWidth.normalize()},
    m_directionLength{directionLength.normalize()},
    m_length{length},
    m_width{width},
    m_thickness{thickness},
    m_restitution{restitution},
    m_centerPosition{centerPosition},
    m_otherParticle{otherParticle}
{

}

void WallContactGenerator::addContact(std::vector<ParticleContact>& contacts) const
{
    Vector3f vectWallToParticle = m_otherParticle->getPosition() - m_centerPosition;
    Vector3f wallNormal = m_directionWidth.crossProduct(m_directionLength).normalize();
    float normalComponentNorm = vectWallToParticle.dotProduct(wallNormal);
    Vector3f tangentComponent = vectWallToParticle - normalComponentNorm * wallNormal;

    // We get the particle's radius and its penetration inside the wall
    float particleRadius = m_otherParticle->getRadius();
    float penetration = normalComponentNorm - particleRadius - m_thickness / 2.0f;

    if (penetration < 0.0f && abs(tangentComponent.dotProduct(m_directionLength)) <= m_length / 2.0f && abs(tangentComponent.dotProduct(m_directionWidth)) <= m_width / 2.0f)
    {
        // Contact with the wall
        contacts.emplace_back(m_otherParticle, nullptr, -penetration, wallNormal, m_restitution);
    }
}