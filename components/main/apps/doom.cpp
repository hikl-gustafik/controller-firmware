#include "layer.h"
#include "runtime.h"

#include <cmath>

class Doom : public Layer {
public:
    const char* GetName() const override { return "Doom"; }
protected:
    struct Vector2 {
        float x, y;

        Vector2 operator-(const Vector2& other) const {
            return Vector2(x - other.x, y - other.y);
        }

        float cross(const Vector2& other) const {
            return x * other.y - y * other.x;
        }

        float dot(const Vector2& other) const {
            return x * other.x + y * other.y;
        }
    };
    struct Line {
        Vector2 start, end;

        bool IsIntersecting(const Line& other) const {
            Vector2 r = end - start;
            Vector2 s = other.end - other.start;

            float r_cross_s = r.cross(s);

            // If r_cross_s is 0, the lines are parallel or collinear
            if (r_cross_s == 0) {
                return false;
            }

            Vector2 p = other.start - start;
            float t = p.cross(s) / r_cross_s;
            float u = p.cross(r) / r_cross_s;

            // Check if the intersection point is on both line segments
            if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
                return true;
            }

            return false;
        }
    };
    struct Player {
        Vector2 position;
        float rotation; // Radians
    };
protected:
    const float m_MoveSpeed = 1.0f;
    const float m_RotationSpeed = 0.2f;
    const float m_FOV = 3.14159f / 12.0f;
    const float m_DepthOfField = 100.0f;
protected:
    Player m_Player = { { 0.0f, 0.0f }, 0.0f };
    Line m_Level[1] = {
        { { 1.0, -1.0 }, { 1.0, 1.0 } }
        /*// Upper wall
        { { -2.5, 0.5 }, { -1.0, 0.5 } },
        { { -1.0, 0.5 }, { -1.0, 1.0 } },
        { { -1.0, 1.0 }, { -0.5, 1.0 } },
        { { -0.5, 1.0 }, { 0.0, 2.0 } },
        { { 0.0, 2.0 }, { 0.5, 1.0 } },
        { { 0.5, 1.0 }, { 1.0, 1.0 } },
        { { 1.0, 1.0 }, { 1.0, 0.5 } },
        { { 1.0, 0.5 }, { 2.5, 0.5 } },
        // Lower wall left
        { { -2.5, -0.5 }, { -1.0, -0.5 } },
        { { -1.0, -0.5 }, { -1.0, -1.0 } },
        { { -1.0, -1.0 }, { -0.5, -1.0 } },
        // Lower wall right
        { { 0.5, -1.0 }, { 1.0, -1.0 } },
        { { 1.0, -1.0 }, { 1.0, -0.5 } },
        { { 1.0, -0.5 }, { 2.5, -0.5 } },*/
    };
protected:
    void Draw(Runtime& runtime, float delta) override {
        auto& input = runtime.GetInput();

        // Forward/backward
        m_Player.position.x -=
            input.LeftJoystickY() * cos(m_Player.rotation) * m_MoveSpeed;
        m_Player.position.y -=
            input.LeftJoystickY() * sin(m_Player.rotation) * m_MoveSpeed;
        // Rotate
        m_Player.rotation +=
            input.RightJoystickX() * m_RotationSpeed;

        auto& display = runtime.GetDisplay();

        display.clearDisplay();

        static int optimization = 4;
        static float numRays = display.width();
        for (int x = 0; x < numRays; x += optimization) {
            float rayAngle =
                m_Player.rotation - m_FOV /
                2.0f + (x / float(numRays)) * m_FOV;

            Line ray = { m_Player.position, { cos(rayAngle), sin(rayAngle) }};

            bool hit = false;
            float depth = 0.0f;

            while (!hit && depth < m_DepthOfField) {
                ray.start.x += ray.end.x * 0.1f;
                ray.start.y += ray.end.y * 0.1f;
                depth += 0.1f;

                for (const Line& wall : m_Level) {
                    if (ray.IsIntersecting(wall)) {
                        hit = true;
                        if (depth <= 0.0f) break;
                        float depthDamper = 0.25;
                        float rawWallHeight = (int)(display.height() / (depth * depthDamper));
                        float wallHeight = rawWallHeight > display.height() ? display.height() : rawWallHeight;
                        float wallY = (float)display.height() / 2 - wallHeight / 2;
                        for (int y = wallY; y < wallY + wallHeight; y++) {
                            if (y % 2 == 0) display.drawPixel(x, y, WHITE);
                            else display.drawPixel(x, y+1, WHITE);
                        }
                        break;
                    }
                }
            }
        }

        display.display();
    }
};
