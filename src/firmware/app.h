#pragma once

class App {
public:
    // Runs while the app loads
    virtual void Initialize() {}
    // Runs repeatedly when the app is active
    virtual void Process() {}
    // Runs before the app is closed
    virtual void Shutdown() {}
protected:
};
