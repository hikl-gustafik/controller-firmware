#include "layer.h"
#include "runtime.h"

class ScreenSaver : public Layer {
public:
    const char* GetName() const override { return "Screen Saver"; }
protected:
    int m_PositionX = 25;
    int m_PositionY = 25;
    int m_VeclotyX = 1;
    int m_VecocityY = -1;
    const int m_ScaleX  = 10;
    const int m_ScaleY = m_ScaleX;

    const char* GetLoadingText() override {
        return "Example...";
    }

    void Awake(Runtime& runtime) override {
        // Simulate loading
        vTaskDelay(1000);
        // Clear display after loading
        runtime.GetDisplay().clearDisplay();
    }

    void Draw(Runtime& runtime, float delta) override {
        static const int screenX = runtime.GetDisplay().width();
        static const int screenY = runtime.GetDisplay().height();

        // Clear
        runtime.GetDisplay().drawRect(
            m_PositionX, m_PositionY,
            m_ScaleX, m_ScaleY,
            BLACK
        );

        // Check collision
        if (
            m_PositionX + m_VeclotyX < 0 ||
            m_PositionX + m_ScaleX + m_VeclotyX >= screenX
        ) {
            m_VeclotyX *= -1;
        }
        if (
            m_PositionY + m_VecocityY < 0 ||
            m_PositionY + m_ScaleY + m_VecocityY >= screenY
        ) {
            m_VecocityY *= -1;
        }

        // Move
        m_PositionX += m_VeclotyX;
        m_PositionY += m_VecocityY;

        // Draw
        runtime.GetDisplay().drawRect(
            m_PositionX, m_PositionY,
            m_ScaleX, m_ScaleY,
            WHITE
        );

        runtime.GetDisplay().display();
    }
};
