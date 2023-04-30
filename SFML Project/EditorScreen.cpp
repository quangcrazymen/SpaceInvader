#include "EditorScreen.h"
#include "GameInputHandler.h"
#include "EditorUIPanel.h"
#include "WorldState.h"

EditorScreen::EditorScreen(ScreenManagerRemoteControl* smrc, Vector2i res){
	m_EIH = make_shared<EditorInputHandler>();
	auto euip = make_unique<EditorUIPanel>(res);
	addPanel(move(euip), smrc, m_EIH);

	m_ScreenManagerRemoteControl = smrc;
	float screenRatio = VideoMode::getDesktopMode().width /
		VideoMode::getDesktopMode().height;

	WorldState::WORLD_HEIGHT = WorldState::WORLD_WIDTH /
		screenRatio;

	m_View.setSize(
		WorldState::WORLD_WIDTH, WorldState::WORLD_HEIGHT);

	m_View.setCenter(Vector2f(WorldState::WORLD_WIDTH /
		2, WorldState::WORLD_HEIGHT / 2));

}

void EditorScreen::initialise() {
	m_EIH->initialize();
}
void EditorScreen::update(float fps) {
	Screen::update(fps);
	// Get all the objects
	for (auto& it : m_ScreenManagerRemoteControl->
		getGameObjects())
	{
		it.update(fps);
	}

}
void EditorScreen::draw(RenderWindow& window) {
	// Change to this screen's view to draw
	window.setView(m_View);

	// Draw the GameObject instances
	for (auto& it : m_ScreenManagerRemoteControl->
		getGameObjects())
	{
		it.draw(window);
	}

	// Draw the UIPanel view(s)
	Screen::draw(window);
}
