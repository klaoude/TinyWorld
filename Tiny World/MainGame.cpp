#include "MainGame.h"

#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>

#include <KlaoudeEngine\KlaoudeEngine.h>

MainGame::MainGame(int screenWidth, int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	
	m_gameState = PLAYING;
}

MainGame::~MainGame()
{
}

void MainGame::InitSystem()
{
	KlaoudeEngine::init();

	m_window.create("Tiny World", m_screenWidth, m_screenHeight, 0);
	glClearColor(.7f, .7f, .7f, 1.f);

	m_camera.init(m_screenWidth, m_screenHeight);

	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	m_player = new Player();
	m_player->Init(glm::vec2(100, 100), 1.f);
}

void MainGame::Draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_entitySpriteBatch.begin();

	m_player->Draw(m_entitySpriteBatch);

	m_entitySpriteBatch.end();

	m_entitySpriteBatch.renderBatch();

	m_textureProgram.unUse();

	m_window.swapBuffer();
}

void MainGame::ProcessInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			m_gameState = QUITTING;
			break;
		case SDL_MOUSEMOTION:
			m_im.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_im.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_im.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_im.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_im.releaseKey(evnt.button.button);
			break;
		}
	}
}

void MainGame::GameLoop()
{
	const float DESIRED_FPS = 60.0f;
	const int MAX_PHYSICS_STEPS = 6;

	KlaoudeEngine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(0.0f);

	const float MS_PER_SEC = 1000.0f;
	const float DESIRED_FRAMETIME = MS_PER_SEC / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;

	float previousTicks = SDL_GetTicks();

	const float CAMERA_SCALE = 1.2f;

	m_camera.setScale(CAMERA_SCALE);

	while (m_gameState == PLAYING)
	{
		fpsLimiter.begin();

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		m_im.update();
		ProcessInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
		{
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);

			m_player->Update();

			totalDeltaTime -= deltaTime;
			i++;
		}

		Draw();

		m_fps = fpsLimiter.end();
	}
}

void MainGame::Run()
{
	InitSystem();

	GameLoop();
}