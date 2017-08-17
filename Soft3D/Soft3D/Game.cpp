#include "Game.h"

namespace Soft3D {

	void Game::Start() {
		
	}

	void Game::SetScene(Scene* scene) {
		if (m_scene != NULL) {
			m_scene->Destroy();
			m_scene->Resize(m_width, m_height);
		}
		m_scene = scene;
	}

	void Game::SetSize(int width, int height) {
		m_width = width;
		m_height = height;
		if (m_scene != NULL) {
			m_scene->Resize(width, height);
		}
	}

	void Game::Pause() {
		if (m_scene != NULL) {
			m_scene->Pause();
		}
	}

	void Game::Resume() {
		if (m_scene != NULL) {
			m_scene->Resume();
		}
	}

	void Game::Render(RenderContext& context, Float delta) {
		if (m_scene != NULL) {
			m_scene->Render(context, delta);
		}
	}

	void Game::Destroy() {
		if (m_scene != NULL) {
			m_scene->Destroy();
		}
	}

}
