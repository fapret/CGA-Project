#pragma once
#include "LightComponent.h"

class SpotLightComponent : public LightComponent {
private:
    float cutoff;
    float outerCutoff;
    float constant;
    float linear;
    float quadratic;
    int index;
public:
    SpotLightComponent();
    void draw(float deltaTime = 0.0f) override;
    float getCutoff();
    void setCutoff(float cutoff);
    float getOuterCutoff();
    void setOuterCutoff(float outerCutoff);
    float getConstant();
    void setConstant(float constant);
    float getLinear();
    void setLinear(float linear);
    float getQuadratic();
    void setQuadratic(float quadratic);
};