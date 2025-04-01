#include "debug.h"
#include "runtime.h"
#include "layer.h"

#include "freertos/idf_additions.h"

class Pong : public Layer {
public:
    const char* GetName() const override { return "Pong"; }
protected:
    void Awake(Runtime& runtime) override {
        auto& display = runtime.GetDisplay();

        m_LeftPaddlePosition = {
            5.0f,
            display.height() / 2.0f - m_PaddleSize.y / 2.0f,
        };
        m_RightPaddlePosition = {
            display.width() - m_PaddleSize.x - 5.0f,
            display.height() / 2.0f - m_PaddleSize.y / 2.0f,
        };

        m_BallPosition = { display.width() / 2.0f, display.height() / 2.0f };
        m_BallVelocity = { m_BallSpeed, 0.0f };
    }

    void Draw(Runtime& runtime, float delta) override {
        auto& display = runtime.GetDisplay();
        auto& input = runtime.GetInput();

        // Clear the display
        display.clearDisplay();

        // Get the paddle velocities from the input
        float leftPaddleVelocity = input.LeftJoystickY() * m_PaddleSpeed;
        float rightPaddleVelocity = input.RightJoystickY() * m_PaddleSpeed;

        // Update the paddle positions
        m_LeftPaddlePosition.y += leftPaddleVelocity * delta;
        m_RightPaddlePosition.y += rightPaddleVelocity * delta;

        // Update ball velocity when colliding with paddles
        if (AABB(
            m_LeftPaddlePosition, m_PaddleSize,
            m_BallPosition, m_BallSize
        )) {
            m_BallVelocity.x = m_BallSpeed;
            m_BallVelocity.y += leftPaddleVelocity * 0.5f;
        }
        if (AABB(
            m_RightPaddlePosition, m_PaddleSize,
            m_BallPosition, m_BallSize
        )) {
            m_BallVelocity.x = -m_BallSpeed;
            m_BallVelocity.y += rightPaddleVelocity * 0.5f;
        }

        // Update ball position
        m_BallPosition.x += m_BallVelocity.x * delta;
        m_BallPosition.y += m_BallVelocity.y * delta;

        // Check for collisions with the walls
        if (m_LeftPaddlePosition.y < 0.0f) {
            m_LeftPaddlePosition.y = 0.0f;
        } else if (m_LeftPaddlePosition.y + m_PaddleSize.y > display.height()) {
            m_LeftPaddlePosition.y = display.height() - m_PaddleSize.y;
        }
        if (m_RightPaddlePosition.y < 0.0f) {
            m_RightPaddlePosition.y = 0.0f;
        } else if (m_RightPaddlePosition.y + m_PaddleSize.y > display.height()) {
            m_RightPaddlePosition.y = display.height() - m_PaddleSize.y;
        }
        if (
            m_BallPosition.y < 0.0f ||
            m_BallPosition.y + m_BallSize.y > display.height()
        ) {
            m_BallVelocity.y *= -1.0f;
        }

        // Check for scoring
        if (m_BallPosition.x < 0) {
            m_RightScore++;
            m_BallPosition = { display.width() / 2.0f, display.height() / 2.0f };
            m_BallVelocity = { m_BallSpeed, 0.0f };
            vTaskDelay(500 / portTICK_PERIOD_MS);
        } else if (m_BallPosition.x + m_BallSize.x > display.width()) {
            m_LeftScore++;
            m_BallPosition = { display.width() / 2.0f, display.height() / 2.0f };
            m_BallVelocity = { -m_BallSpeed, 0.0f };
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }

        // Draw the paddles and ball
        display.fillRect(
            m_LeftPaddlePosition.x, m_LeftPaddlePosition.y,
            m_PaddleSize.x, m_PaddleSize.y,
            WHITE
        );
        display.fillRect(
            m_RightPaddlePosition.x, m_RightPaddlePosition.y,
            m_PaddleSize.x, m_PaddleSize.y,
            WHITE
        );
        display.fillRect(
            m_BallPosition.x, m_BallPosition.y,
            m_BallSize.x, m_BallSize.y,
            WHITE
        );

        // Display the scores
        display.setCursor(display.width() / 2 - 20, 10);
        display.print(m_LeftScore);
        display.setCursor(display.width() / 2 + 10, 10);
        display.print(m_RightScore);

        display.display();
    }
private:
    struct Vector2 { float x = 0.0f, y = 0.0f; };

    Vector2
        m_LeftPaddlePosition,
        m_RightPaddlePosition,
        m_BallPosition,
        m_BallVelocity;

    const Vector2
        m_PaddleSize = { 4.0f, 15.0f },
        m_BallSize = { 4.0f, 4.0f };

    const float m_PaddleSpeed = 100.0f;
    const float m_BallSpeed = 50.0f;

    int m_LeftScore = 0, m_RightScore = 0;

    bool AABB(
        const Vector2& aPos, const Vector2& aSize,
        const Vector2& bPos, const Vector2& bSize
    ) {
        return
            (aPos.x < bPos.x + bSize.x) &&
            (aPos.x + aSize.x > bPos.x) &&
            (aPos.y < bPos.y + bSize.y) &&
            (aPos.y + aSize.y > bPos.y);
    }
};
