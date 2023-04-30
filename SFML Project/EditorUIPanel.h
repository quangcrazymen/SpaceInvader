#pragma once
#include "UIPanel.h"
class EditorUIPanel :
    public UIPanel
{
private:
    void initializeButtons();
public:
    EditorUIPanel(Vector2i res);
    virtual void draw(RenderWindow& window);
};

