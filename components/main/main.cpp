#include "layer.h"
#include "runtime.h"

#include <cmath>

class ScreenSaver : public Layer {
protected:
    int m_PositionX = 25;
    int m_PositionY = 25;
    int m_VeclotyX = 1;
    int m_VecocityY = -1;
    const int m_ScaleX  = 10;
    const int m_ScaleY = m_ScaleX;

    void Initialize(Runtime& runtime) override {
        runtime.GetDisplay().clearDisplay();
    }

    void Process(Runtime& runtime) override {
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

class Diagnostics : public Layer {
    const char* GetName() const override {
        return "Diagnostics";
    }

    void Process(Runtime& runtime) override {
        auto& display = runtime.GetDisplay();

        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setTextSize(1);

        // LJX
        display.setCursor(0, 0);
        display.print(runtime.GetInput().LeftJoystickX());
        // LJY
        display.setCursor(0, 10);
        display.print(runtime.GetInput().LeftJoystickY());
        // LJZ
        display.setCursor(0, 20);
        display.print(runtime.GetInput().LeftJoystickButton());
        // RJX
        display.setCursor(95, 0);
        display.print(runtime.GetInput().RightJoystickX());
        // RJY
        display.setCursor(95, 10);
        display.print(runtime.GetInput().RightJoystickY());
        // RJZ
        display.setCursor(95, 20);
        display.print(runtime.GetInput().RightJoystickButton());
        // B1
        display.setCursor(40, 50);
        display.print(runtime.GetInput().Button1());
        // B2
        display.setCursor(50, 50);
        display.print(runtime.GetInput().Button2());
        // B3
        display.setCursor(60, 50);
        display.print(runtime.GetInput().Button3());
        // B4
        display.setCursor(70, 50);
        display.print(runtime.GetInput().Button4());
        // Battery percentage
        display.setCursor(40, 0);
        if (runtime.GetFuel().IsActive()) {
            display.print(runtime.GetFuel().Percent());
            display.print("%");
        } else {
            display.print("Plugged");
        }
        // Charge rate
        display.setCursor(40, 10);
        display.print(runtime.GetFuel().ChargeRate());
        display.print("%/h");
        // Voltage
        display.setCursor(40, 20);
        display.print(runtime.GetFuel().Voltage());
        display.print("V");

        display.display();
    }
};

template<int Size>
class Menu : public Layer {
public:
    Menu(Layer* (&items)[Size]) : m_Items(items) {}
    const char* GetName() const override { return "Menu"; }
protected:
    void Initialize(Runtime& runtime) override {
        runtime.GetDisplay().clearDisplay();
        runtime.GetDisplay().display();
    }

    void Process(Runtime& runtime) override {
    }

    void Shutdown(Runtime& runtime) override {

    }
private:
    Layer* (&m_Items)[Size];
};

extern "C" void app_main(void) {
    Diagnostics diagnostics;
    ScreenSaver screenSaver;

    Layer* items[] = {
        &diagnostics,
        &screenSaver,
    };
    Menu mainMenu(items);

    Runtime runtime;
    runtime.Switch(&mainMenu);
    runtime.BeginLoop();
}
