#pragma once
#include "Screen.h"
#include "EditorInputHandler.h"

class EditorScreen :
    public Screen
{
private:
    ScreenManagerRemoteControl * m_ScreenManagerRemoteControl;
    // shared ? (cant do unique because addButton method require shared)
    shared_ptr<EditorInputHandler> m_EIH;

    Texture m_BackgroundTexture;
    Sprite m_BackgroundSprite;

public:
    EditorScreen(ScreenManagerRemoteControl* smrc, Vector2i res);
    void initialise() override;
    virtual void update(float fps);
    virtual void draw(RenderWindow& window);

    // call to level manager to update component
};

