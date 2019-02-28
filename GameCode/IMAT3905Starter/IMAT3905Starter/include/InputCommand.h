#pragma once

// forward declaration - better than including the .h file if we don't need internal details
class GameObject;

/*! \class The base for all inputs commands. */
class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& player) = 0;
};

// classes implementing the InputCommand interface (implementations are in the .cpp file)

/*! \class Used to rotate left. */
class RotateLeftCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to rotate right. */
class RotateRightCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to rotate up. */
class RotateUpCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to rotate down. */
class RotateDownCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to move forward. */
class MoveForwardCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to move back. */
class MoveBackCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to move up. */
class MoveUpCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to move down. */
class MoveDownCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to change to a first person camera. */
class CameraFirstCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to change to a third person camera. */
class CameraThirdCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to reset the commands. */
class ResetCommand : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to change the current level. */
class GotoLevel1Command : public InputCommand
{
	void execute(GameObject& player);
};

/*! \class Used to change the current level. */
class GotoLevel2Command : public InputCommand
{
	void execute(GameObject& player);
};