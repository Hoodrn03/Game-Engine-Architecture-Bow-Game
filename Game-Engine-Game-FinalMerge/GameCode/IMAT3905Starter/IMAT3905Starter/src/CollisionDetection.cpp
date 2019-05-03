#include "CollisionDetection.h"

CollisionDetection::CollisionDetection()
{
}

CollisionDetection::~CollisionDetection()
{
}

float CollisionDetection::m_CalcDist(glm::vec3 pointOne, glm::vec3 pointTwo)
{
	float l_fDist; 

	// The formula for finding the distance between two points is sqrt((X2 - X1)^2 + (Y2 - Y1)^2). 

	float l_fNewX = pow((pointTwo.x - pointOne.x), 2);
	float l_fNewY = pow((pointTwo.y - pointOne.y), 2);

	l_fDist = sqrt((l_fNewX + l_fNewY));

	return l_fDist;
}

bool CollisionDetection::m_CheckForObjectBoxColl(GameObject* objectToCheck)
{
	if (m_CurrentArrowObject != nullptr && (objectToCheck != nullptr))
	{
		// Create Local Variables. 

		float l_fArrowX, l_fArrowY;

		float l_fOtherObjX, l_fOtherObjY, l_fOtherObjWidth, l_fOtherObjHeight;

		l_fArrowX = m_CurrentArrowObject->getComponent<TransformComponent>()->m_position.x;
		l_fArrowY = m_CurrentArrowObject->getComponent<TransformComponent>()->m_position.y;

		l_fOtherObjX = objectToCheck->getComponent<TransformComponent>()->m_position.x;
		l_fOtherObjY = objectToCheck->getComponent<TransformComponent>()->m_position.y;

		l_fOtherObjWidth = objectToCheck->getComponent<TransformComponent>()->width;
		l_fOtherObjHeight = objectToCheck->getComponent<TransformComponent>()->height;

		l_fOtherObjWidth = 10.f;
		l_fOtherObjHeight = 10.f;

		// Check for collision. 
		if (((l_fArrowX > l_fOtherObjX) && (l_fArrowY > l_fOtherObjY)) &&
			((l_fArrowX < l_fOtherObjX + l_fOtherObjWidth) && (l_fArrowY < l_fOtherObjY + l_fOtherObjHeight)))
		{
			std::cout << "I iz filly gud" << std::endl;

			m_CurrentArrowObject->getComponent<Velocity>()->m_HitObject(true);
			m_CurrentArrowObject->getComponent<Gravity>()->m_HitObject(true);

			return true;
		}

	}
	else
	{
		std::cout << "NULLPTR ALERT GITOUT" << std::endl;
	}

	return false;
}

bool CollisionDetection::m_CheckForLineColl(glm::vec3 pointOne, glm::vec3 pointTwo)
{
	// Create Local Variables
	if (m_CurrentArrowObject != nullptr)
	{

		float l_fCollBuffer = 0.01f;

		float l_fArrowX, l_fArrowY;

		l_fArrowX = m_CurrentArrowObject->getComponent<TransformComponent>()->m_position.x;
		l_fArrowY = m_CurrentArrowObject->getComponent<TransformComponent>()->m_position.y;

		float l_fLineLength = m_CalcDist(pointOne, pointTwo);

		float l_fDistOne = m_CalcDist(glm::vec3(l_fArrowX, l_fArrowY, 0), pointOne);
		float l_fDistTwo = m_CalcDist(glm::vec3(l_fArrowX, l_fArrowY, 0), pointTwo);

		// Check For Collision 

		if ((l_fDistOne + l_fDistTwo >= l_fLineLength - l_fCollBuffer) && (l_fDistOne + l_fDistTwo <= l_fLineLength + l_fCollBuffer))
		{
			m_CurrentArrowObject->getComponent<Velocity>()->m_HitObject(true); 
			m_CurrentArrowObject->getComponent<Gravity>()->m_HitObject(true);
			return true;
		}

	}
		return false;
}

void CollisionDetection::m_Update()
{
	m_bHitPlayer = m_CheckForObjectBoxColl(m_PlayerObject);
	m_bHitEnemy = m_CheckForObjectBoxColl(m_EnemyObject); 

	for (unsigned int i = 0; i < m_MainLevelPoints.size() - 1; i++)
	{
		m_bHitGround = m_CheckForLineColl(m_MainLevelPoints[i], m_MainLevelPoints[i + 1]); 
	}
}

void CollisionDetection::m_SetPlayerObject(GameObject* currPlayer)
{
	m_PlayerObject = currPlayer;
}

void CollisionDetection::m_SetEnemyObject(GameObject* currEnemy)
{
	m_EnemyObject = currEnemy; 
}

void CollisionDetection::m_SetMainMapPoints(std::vector<glm::vec3> mapPoints)
{
	m_MainLevelPoints.clear();

	m_MainLevelPoints.operator=(mapPoints); 
}

void CollisionDetection::m_SetCurrArrowObject(GameObject* currArrow)
{
	m_CurrentArrowObject = currArrow; 
}

bool CollisionDetection::m_GetPlayerHit()
{
	return m_bHitPlayer;
}

bool CollisionDetection::m_GetEnemyHit()
{
	return m_bHitEnemy;
}

bool CollisionDetection::m_GetGroundHit()
{
	return m_bHitGround;
}
