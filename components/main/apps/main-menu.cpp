#include "runtime.h"
#include "layer.h"

#include "prebuilt/layer-picker.h"

template<size_t Size>
class MainMenu : public Layer {
public:
    MainMenu(Layer* (&items)[Size]) :
        m_LayerPicker(items) { }

    const char* GetName() const override { return "Main Menu"; }
protected:
    void Awake(Runtime& runtime) override {
        runtime.Push(&m_LayerPicker);
    }

    void Process(Runtime& runtime, float delta) override {
        static const int requiredSeconds = 3;
        if (runtime.GetInput().Button2()) {
            m_HoldCounter += delta;
            if (m_HoldCounter >= requiredSeconds) {
                while (
                    runtime.Top() != &m_LayerPicker &&
                    runtime.Top() != this
                ) {
                    runtime.Pop();
                }
                m_HoldCounter = 0.0;
            }
        } else {
            m_HoldCounter = 0.0;
        }
    }
private:
    LayerPicker<Size> m_LayerPicker;
    float m_HoldCounter = 0.0;
};
