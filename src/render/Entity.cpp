#include "render/Entity.hpp"

Entity::Entity(const std::shared_ptr<LogicalDevice> & logicalDevice, const std::shared_ptr<CommandPool> & commandPool, const std::vector<Vertex> & vertices, const std::vector<uint32_t> & indices) :
    m_indexSize{indices.size()},
    m_transform{1.0f}
{
    {
        VkDeviceSize bufferSize = sizeof(Vertex) * vertices.size();

        // Create staging buffer
        Buffer staging{logicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT};

        // Copy vertices data into staging buffer
        staging.loadData(vertices.data(), (size_t) bufferSize);

        // Create vertex buffer
        m_vertexBuffer = std::make_unique<Buffer>(logicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        // Copy staging buffer data into vertex buffer
        commandPool->copyBuffer(staging, *m_vertexBuffer, bufferSize);
    }
    {
        VkDeviceSize bufferSize = sizeof(uint32_t) * indices.size();

        // Create staging buffer
        Buffer staging{logicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT};

        // Copy vertices data into staging buffer
        staging.loadData(indices.data(), (size_t) bufferSize);

        // Create index buffer
        m_indexBuffer = std::make_unique<Buffer>(logicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        // Copy staging buffer data into index buffer
        commandPool->copyBuffer(staging, *m_indexBuffer, bufferSize);
    }
}

Entity::~Entity()
{
}

void Entity::rotate(float angle, const glm::vec3 & axis)
{
    m_transform = glm::rotate(m_transform, angle, axis);
}