#include "debug.h"
#include "layer.h"
#include "runtime.h"

class TestTestLayer : public Layer {
protected:
    virtual void Initialize() override {
        auto& dev = Runtime::Instance().getDisplay().getDevice();
        ssd1306_display_text(&dev, 0, (char*)"Hello", 5, false);
    }

    virtual void Process() override {
        DEBUG("Test test");
    }
};

class TestLayer : public Layer {
protected:
    TestTestLayer testTestLayer;

    virtual void Initialize() override {
        StartSync(&testTestLayer);
    }

    virtual void Process() override {
        DEBUG("Test");
    }
};

extern "C" void app_main(void) {
    Runtime::Initialize();

    TestLayer testLayer;

    Runtime::Instance().Switch(&testLayer);
    Runtime::Instance().BeginLoop();

    Runtime::Shutdown();
}
