#include "Adafruit_SSD1306.h"
#include "layer.h"
#include "runtime.h"

class Bounce : public Layer {
public:
    int PosX = 25;
    int PosY = 25;
    int SclX  = 10;
    int SclY = SclX;
protected:
    int VelX = 1;
    int VelY = -1;

    void Initialize(Runtime& runtime) override {
        runtime.GetDisplay().clearDisplay();
    }

    void Process(Runtime& runtime) override {
        static const int screenX = runtime.GetDisplay().width();
        static const int screenY = runtime.GetDisplay().height();

        // Clear
        runtime.GetDisplay().drawRect(PosX, PosY, SclX, SclY, BLACK);

        // Check collision
        if (PosX + VelX < 0 || PosX + SclX + VelX >= screenX) { VelX *= -1; }
        if (PosY + VelY < 0 || PosY + SclY + VelY >= screenY) { VelY *= -1; }

        // Move
        PosX += VelX;
        PosY += VelY;

        // Draw
        runtime.GetDisplay().drawRect(PosX, PosY, SclX, SclY, WHITE);
        runtime.GetDisplay().display();
    }
};

class JoyPos : public Layer {
    void Process(Runtime& runtime) override {
        auto& display = runtime.GetDisplay();
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setTextSize(1);
        // LJX
        display.setCursor(0, 0);
        display.print(runtime.GetInput().LeftJoystickX());
        // LJY
        display.setCursor(0, 15);
        display.print(runtime.GetInput().LeftJoystickY());
        // RJX
        display.setCursor(0, 30);
        display.print(runtime.GetInput().RightJoystickX());
        // RJY
        display.setCursor(0, 45);
        display.print(runtime.GetInput().RightJoystickY());
        //
        display.display();
    }
};

extern "C" void app_main(void) {
    Runtime runtime;

    JoyPos testLayer;

    runtime.Switch(&testLayer);
    runtime.BeginLoop();
}
