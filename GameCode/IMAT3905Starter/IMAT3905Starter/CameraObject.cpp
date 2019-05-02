#include "CameraObject.h"

CameraObject::CameraObject(glm::vec3 position, glm::quat orientation)
{
	CameraComponent * cc = new CameraComponent(position, orientation);

	addComponent(cc);
}

void CameraObject::OnUpdate(float dt)
{
}

void CameraObject::OnUpdate(float dt, int currentTurn)
{
	int turn = currentTurn; 

	if (turn == 0) { setToPlayer(); } //set camera position to player if players turn
	if (turn == 1) { setToEnemy(); } //set camera position to enemy if enemy's turn 
	if (turn == 2) { setToArrow(); } //set camera position to arrow if enemy or player arrow is fired. 
}

void CameraObject::setToPlayer()
{
	getComponent<CameraComponent>()->setPosition((*playerPos + glm::vec3(0.0f, 0.0f, 7.0f))); //set the camera position to the players position with an offset in the Z axis of 7. 
}

void CameraObject::setToEnemy()
{
	getComponent<CameraComponent>()->setPosition((*enemyPos + glm::vec3(0.0f, 0.0f, 7.0f))); //set the camera position to the enemy's position with an offset in the Z axis of 7.
}

void CameraObject::setToArrow()
{
	getComponent<CameraComponent>()->setPosition((*arrowPos + glm::vec3(0.0f, 0.0f, 5.0f))); //set the camera position to the arrow's position with an offset in the Z axis of 5. 
}

void CameraObject::m_SetPlayerPos(glm::vec3 * newPlayerPos)
{
	playerPos = newPlayerPos;  // get the position of player
}

void CameraObject::m_SetEnemyPos(glm::vec3 * newEnemyPos)
{
	enemyPos = newEnemyPos; //get the position of enemy 
}

void CameraObject::m_CurrentArrowPos(glm::vec3 * newArrowPos)
{
	arrowPos = newArrowPos; //get the position of the current arrow
}

CameraComponent * CameraObject::getCamera()
{
	return getComponent<CameraComponent>();
}

void CameraObject::OnMessage(const std::string m)
{

}

CameraObject::~CameraObject()
{

}

