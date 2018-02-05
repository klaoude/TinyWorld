#pragma once

#include <KlaoudeEngine/Window.h>
#include <KlaoudeEngine\GLSLProgram.h>
#include <KlaoudeEngine\Camera2D.h>
#include <KlaoudeEngine\Timing.h>
#include <KlaoudeEngine\InputManager.h>

#include "Player.h"

enum GameState
{
	PLAYING,
	QUITTING
};

class MainGame
{
public:
	MainGame(int screenWidth, int screenHeight);
	~MainGame();

	void Run();

private:
	void InitSystem();
	void GameLoop();
	void Draw();
	void ProcessInput();

	KlaoudeEngine::Window m_window;
	KlaoudeEngine::GLSLProgram m_textureProgram;
	KlaoudeEngine::Camera2D m_camera;
	KlaoudeEngine::SpriteBatch m_entitySpriteBatch;
	KlaoudeEngine::InputManager m_im;

	int m_screenWidth, m_screenHeight;

	GameState m_gameState;

	float m_fps;

	Player* m_player;
};