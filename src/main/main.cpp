#include "app.h"
#include "debug.h"
#include "runtime.h"

class TestApp : public App {
public:
    virtual void Process() override {
        DEBUG("Test");
    }
};

extern "C" void app_main(void) {
    Runtime::Initialize();

    TestApp testApp;

    Runtime::Instance().Switch(&testApp);
    Runtime::Instance().BeginLoop();

    Runtime::Shutdown();
}
