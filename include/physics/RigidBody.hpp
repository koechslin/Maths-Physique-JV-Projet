#ifndef MPJVP_RIGIDBODY
#define MPJVP_RIGIDBODY

#include "physics/Vector3f.hpp"
#include "physics/Quaternion.hpp"
#include "physics/Matrix34.hpp"
#include "physics/Matrix33.hpp"
#include <numeric>

class RigidBody {
public:
	RigidBody();
	RigidBody(Vector3f position, float mass, float damping, float angularDamping, bool isResting = false);
	~RigidBody();

	// Modify position, orientation and velocities (linear and angular)
	void integrate(float deltaTime);

	inline Vector3f getPosition() const { return m_position; }
	inline void setPosition(Vector3f pos) { m_position = pos; }
	inline void translate(Vector3f trans) { m_position += trans; }

	inline Vector3f getVelocity() const { return m_velocity; }
	inline void setVelocity(Vector3f initialVelocity) { m_velocity = initialVelocity; }
	inline void addVelocity(Vector3f vel) { m_velocity += vel; }

	inline Vector3f getTotalForce() const { return m_totalForce; }
	inline void setTotalForce(Vector3f totalForce) { m_totalForce = totalForce; }
	inline void addForce(Vector3f force) { m_totalForce += force; }

	inline Vector3f getTotalTorque() const { return m_totalTorque; }
	inline void setTotalTorque(Vector3f totalTorque) { m_totalTorque = totalTorque; }
	inline void addTorque(Vector3f torque) { m_totalTorque += torque; }

	inline float getInverseMass() const { return m_inverseMass; }
	inline float getMass() const { return m_inverseMass == 0.0f ? std::numeric_limits<float>().max() : (1.0f / m_inverseMass); }
	inline void setMass(float mass) { m_inverseMass = 1.0f / mass; }
	inline void setInverseMass(float inverseMass) { m_inverseMass = inverseMass; }

	inline float getDamping() const { return m_damping; }
	inline void setDamping(float damping) { m_damping = damping; }

	inline float getAngularDamping() const { return m_angularDamping; }
	inline void setAngularDamping(float angularDamping) { m_angularDamping = angularDamping; }

	inline Quaternion getQuaternion() const { return m_orientation; }
	inline void setQuaternion(Quaternion orientation) { m_orientation = orientation; }

	inline Vector3f getRotation() const { return m_angularVelocity; }
	inline void setRotation(Vector3f rotation) { m_angularVelocity = rotation; }
	inline void addRotation(Vector3f rotation) { m_angularVelocity += rotation; }

	inline bool getIsResting() const { return m_isResting; }
	inline void setIsResting(bool isResting) { m_isResting = isResting; }

	inline Matrix34 getTranformMatrix() const { return m_transformMatrix; }
	inline void setTransformMatrix(Matrix34 transformMatrix) { m_transformMatrix = transformMatrix; }

	void clearAccumulator();

	friend std::ostream& operator<<(std::ostream& out, const RigidBody& a);


private:
	Vector3f m_position;
	Vector3f m_velocity;
	Vector3f m_totalForce;
	Vector3f m_totalTorque;
	float m_inverseMass;
	float m_damping;
	float m_angularDamping;
	bool m_isResting;

	// Orientation of the Rigid Body
	Quaternion m_orientation;

	// Angular velocity
	Vector3f m_angularVelocity;

	// Inverse inertia moment
	Matrix33 m_inverseInertiaMoment;

	// transform Matrix from the calcul between orientation and rotation
	Matrix34 m_transformMatrix;

	// Call each frame to calculate the transformMatrix
	void calculateDerivedData();
};

#endif // MPJVP_RIGIDBODY