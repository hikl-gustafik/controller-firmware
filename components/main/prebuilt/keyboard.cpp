#include "keyboard.h"

void Keyboard::Draw(Runtime& runtime, float delta) {
    auto& display = runtime.GetDisplay();
    auto& input = runtime.GetInput();

    const int currentLayerIndex = WrapIndex(m_Layer, m_KeyboardChars.size());
    const auto& currentLayer = m_KeyboardChars[currentLayerIndex];
    const int currentLayerSize = currentLayer.size();

    const int screenLetterCount = 5;
    const int screenPosY = 32;

    // Draw input text.
    display.fillRect(0, 0, display.width(), 20, BLACK);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(m_InputText.c_str());

    // Draw keyboard.
    for (int i = 0; i < screenLetterCount; i++) {
        const int layerIndex = WrapIndex(
            i + m_Index - (int)(screenLetterCount / 2),
            currentLayerSize
        );
        const char ch = currentLayer[layerIndex];
        const int screenSegmentX = (int)(display.width() / screenLetterCount);
        const int screenPosX = screenSegmentX * i;

        if (layerIndex == WrapIndex(m_Index, currentLayerSize)) /* Selected char */ {
            display.fillRect(
                screenPosX - 1, screenPosY - 1,
                screenSegmentX - 5, screenSegmentX - 5,
                WHITE
            );
            display.setTextColor(BLACK);
        } else {
            display.fillRect(
                screenPosX - 1, screenPosY - 1,
                screenSegmentX, screenSegmentX,
                BLACK
            );
            display.setTextColor(WHITE);
        }
        display.setCursor(screenPosX, screenPosY);
        display.setTextSize(2);
        display.print(ch);
        display.display();
    }

     // Change index.
    if (input.LeftJoystickX() > 0.5) {
        m_Index++;
    } else if (input.LeftJoystickX() < -0.5) {
        m_Index--;
    }

    // Change layer.
    if (input.RightJoystickY() > 0.5) {
        m_Layer++;
    } else if (input.RightJoystickY() < -0.5) {
        m_Layer--;
    }

    // Add char to input text.
    if (input.Button1()) {
        m_InputText += currentLayer[WrapIndex(m_Index, currentLayerSize)];
    }

    // Remove char from input text.
    // If input text is empty, pop the layer.
    if (input.Button2()) {
        if (m_InputText.length() > 0) {
            m_InputText.remove(m_InputText.length() - 1);
        } else {
            runtime.Pop();
        }
    }

    // Confirm input text.
    if (input.Button3()) {
        runtime.Pop();
    }
}

void Keyboard::Sleep(Runtime& runtime)  {
    // Reset data.
    m_InputText.clear();
    m_Layer = 0;
    m_Index = 0;
}

const char* Keyboard::GetReturnText() const {
    // Return input text.
    return m_InputText.c_str();
}
