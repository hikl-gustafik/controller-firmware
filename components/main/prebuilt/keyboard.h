#pragma once

#include "runtime.h"
#include "layer.h"

#include <vector>

#include "WString.h"

class Keyboard : public Layer {
public:
    inline const char* GetName() const override { return "Keyboard"; }
protected:
    void Draw(Runtime& runtime, float delta) override;
    void Sleep(Runtime& runtime) override;

    const char* GetReturnText() const override;
private:
    String m_InputText;

    int m_Layer = 0;
    int m_Index = 0;

    const std::vector<std::vector<char>> m_KeyboardChars = {
        {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
            'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z',
        },
        {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
            'W', 'X', 'Y', 'Z',
        },
        {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        },
        {
            '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-',
            '_', '=', '+', '[', ']', '{', '}', ';', ':', '\'', '"',
            ',', '.', '<', '>', '/', '?', '\\', '|',
        },
    };

    // Accounts for negative index.
    inline static int WrapIndex(int index, int maxIndex) {
        return ((index % maxIndex) + maxIndex) % maxIndex;
    }
};
