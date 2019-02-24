#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

/*! \class The main camera for the game engine. */
class CameraComponent : public Component
{
private: 

	// Data Members 

	/*! \var A vector (X, Y, Y) position for this camera. */
	glm::vec3 m_position;

	/*! \var The direction the camera is facing. */
	glm::quat m_orientation;

public:

	/*! \var The field of view for the camera. */
	float m_fov;

	// Member Functions

	/*! \fn Constructor */
	CameraComponent() : m_position(0), m_orientation(1,0,0,0), m_fov(45) 
	{
	}
	
	/*! \fn Constructor 
	*Param One vec3 A position for the camera. 
	*/
	CameraComponent(const glm::vec3& pos) : m_position(pos), m_orientation(1, 0, 0, 0),m_fov(45) {}
	
	/*! \fn Constructor
	*Param One vec3 A position for the camera.
	*Param Two quat The orientation for the camera. 
	*/
	CameraComponent(const glm::vec3& pos, const glm::quat& orient) : m_position(pos), m_orientation(orient), m_fov(45) {}

	/*! \fn Used to make the camera face a specific target. 
	*Param One vec3 The position of the look at target. 
	*/
	void lookAt(const glm::vec3& target) { m_orientation = (glm::toQuat(glm::lookAt(m_position, target, glm::vec3(0, 1, 0)))); }
	
	/*! \fn The current position of the camera. */
	const glm::vec3& position() const { return m_position; }

	/*! \fn THe current orientation of the camera. */
	const glm::quat& orientation() const { return m_orientation; }

	// added setters

	/*! \fn Used to set the camera's position. 
	*Param One vec3 The new position. 
	*/
	void setPosition(const glm::vec3 newPosition)
	{
		m_position = newPosition;
	}

	/*! \fn Used to set the camera's orientation.
	*Param One vec3 The new orientation. 
	*/
	void setOrientation(const glm::quat newOrientation)
	{
		m_orientation = newOrientation;

	}

	/*! \fn Returns the current view matrix for this camera. */
	glm::mat4 getViewMatrix() const 
	{ 
		// try this....
		return glm::translate(glm::mat4_cast(inverse(m_orientation)), -m_position); 
	}
	
#if 0

	// if camera pos and orientation are copied from transform then these are not used

	/*! \fn Used to move the camera by an amount. 
	*Param One vec3 A movement vector to move the camera by.
	*/
	void translate(const glm::vec3 &v) { m_position += v * m_orientation; }
	
	/*! \fn Used to move the camera by an amount.
	*Param One float The movement value for the X axis. 
	*Param Two float The movement value for the Y axis.
	*Param Three float The movement value for the Z axis. 
	*/
	void translate(float x, float y, float z) { m_position += glm::vec3(x, y, z) * m_orientation; }

	/*! \fn Used to rotate the camera by an amount around an angle.
	*Param One float The angle to rotate by.
	*Param Two vec3 The axis which to rotate around. 
	*/
	void rotate(float angle, const glm::vec3 &axis) { m_orientation *= glm::angleAxis(angle, axis * m_orientation); }
	
	/*! \fn Used to rotate the camera by an amount around an angle.
	*Param One float The angle to rotate by.
	*Param Two float The X axis. 
	*Param Three float The Y axis.
	*Param Four float The Z axis. 
	*/
	void rotate(float angle, float x, float y, float z) { m_orientation *= glm::angleAxis(angle, glm::vec3(x, y, z) * m_orientation); }

	/*! \fn Used to rotate the camera around the Y axis. 
	*Param One float The rotation angle.
	*/
	void yaw(float angle) { rotate(angle, 0.0f, 1.0f, 0.0f); }
	
	/*! \fn Used to rotate the camera around the X axis.
	*Param One float The rotation angle.
	*/
	void pitch(float angle) { rotate(angle, 1.0f, 0.0f, 0.0f); }
	
	/*! \fn Used to rotate the camera around the Z axis.
	*Param One float The rotation angle.
	*/
	void roll(float angle) { rotate(angle, 0.0f, 0.0f, 1.0f); }

#endif

	/*! \fn Used to change the current field of view. 
	*Param One float The new fov. 
	*/
	void setFOV(float fov) { m_fov = fov; }


	// component interface - not used currently

	/*! \fn Used to update this class every frame.
	*Param One float The current delta (change in) time since last frame.
	*/
	void OnUpdate(float dt) override
	{
	}

	/*! \fn Used to respond to inputs.
	*Param One String The input message.
	*/
	void OnMessage(const std::string m) override
	{

	}

};
