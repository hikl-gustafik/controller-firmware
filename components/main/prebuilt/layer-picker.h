#pragma once

#include "layer.h"
#include "runtime.h"

#include "esp32-hal.h"

// Template class cannot be split into .h and .cpp files.
template<size_t Size>
class LayerPicker : public Layer {
public:
    LayerPicker(Layer* (&items)[Size], const char* name = "Layer Picker") :
        m_Items(items), m_Name(name) { }

    const char* GetName() const override { return m_Name; }
protected:
    void Awake(Runtime& runtime) override {
        // Artifical delay to prevent accidental double clicks.
        delay(100);
    }

    void Draw(Runtime& runtime, float delta) override {
        auto& display = runtime.GetDisplay();

        static const int lineHeight = 10; // Pixels
        static int linesPerPage = display.height() / lineHeight;

        for (int pageIndex = 0; pageIndex < linesPerPage && pageIndex < Size; pageIndex++) {
            int arrayIndex = m_PageViewTopIndex + pageIndex;
            bool isSelected = arrayIndex == m_SelectedIndex;
            const char* name =
                m_Items[arrayIndex] ?
                m_Items[arrayIndex]->GetName() :
                "NULL";

            display.writeFillRect(
                0, pageIndex * lineHeight,
                display.width(), lineHeight,
                isSelected ? WHITE : BLACK
            );

            display.setTextSize(1);
            display.setTextColor(isSelected ? BLACK : WHITE);
            display.setTextWrap(false);
            display.setCursor(0, pageIndex * lineHeight);
            display.print(arrayIndex + 1);
            display.print(": ");
            display.print(name);

            display.display();
        }

        float leftJoystickY = runtime.GetInput().LeftJoystickY();
        if (
            leftJoystickY > 0.2 &&
            m_SelectedIndex < Size - 1
        ) {
            m_SelectedIndex++;
            if (m_SelectedIndex > m_PageViewTopIndex + linesPerPage - 1) {
                m_PageViewTopIndex++;
            }
        }
        if (
            leftJoystickY < -0.2 &&
            m_SelectedIndex > 0
        ) {
            m_SelectedIndex--;
            if (m_SelectedIndex < m_PageViewTopIndex) {
                m_PageViewTopIndex--;
            }
        }

        if (runtime.GetInput().Button1()) {
            Layer* selected = m_Items[m_SelectedIndex];
            if (selected) {
                runtime.Push(selected);
            }
        }
    }
private:
    Layer* (&m_Items)[Size];
    const char* m_Name;

    int m_SelectedIndex = 0;
    int m_PageViewTopIndex = 0;
};
