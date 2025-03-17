#include "fuel.h"

#include "debug.h"

#include "Wire.h"

static const char* s_Tag = "fuel";

Fuel::Fuel(int maxAttempts, int waitMs) {
    ESP_LOGD(s_Tag, "Initializing MAX17048");
    m_Device.begin();
}

bool Fuel::IsActive() {
    Wire.beginTransmission(MAX17048_I2CADDR_DEFAULT);
    return Wire.endTransmission() == 0;
}

float Fuel::Voltage(float badResult) {
    return IsActive() ? m_Device.cellVoltage() : badResult;
}

float Fuel::Percent(float badResult) {
    return IsActive() ? m_Device.cellPercent() : badResult;
}

float Fuel::ChargeRate(float badResult) {
    return IsActive() ? m_Device.chargeRate() : badResult;
}
