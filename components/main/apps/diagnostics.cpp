#include "layer.h"
#include "runtime.h"

class Diagnostics : public Layer {
    const char* GetName() const override {
        return "Diagnostics";
    }

    void Draw(Runtime& runtime, float delta) override {
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
