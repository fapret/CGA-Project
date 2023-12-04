#include "SpotLightComponent.h"

SpotLightComponent::SpotLightComponent() : LightComponent()
{
    this->cutoff = 12.5f;
    this->outerCutoff = 17.5f;
    this->constant = 1.0f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;
    Hierarchy& hierarchy = Hierarchy::getInstance();
    this->index = hierarchy.getAmountSpotlights();
    hierarchy.incAmountSpotlights();
}

void SpotLightComponent::draw()
{
    //TODO
}

float SpotLightComponent::getCutoff()
{
    return cutoff;
}

void SpotLightComponent::setCutoff(float cutoff)
{
    this->cutoff = cutoff;
}

float SpotLightComponent::getOuterCutoff()
{
    return outerCutoff;
}

void SpotLightComponent::setOuterCutoff(float outerCutoff)
{
    this->outerCutoff = outerCutoff;
}

float SpotLightComponent::getConstant()
{
    return constant;
}

void SpotLightComponent::setConstant(float constant)
{
    this->constant = constant;
}

float SpotLightComponent::getLinear()
{
    return linear;
}

void SpotLightComponent::setLinear(float linear)
{
    this->linear = linear;
}

float SpotLightComponent::getQuadratic()
{
    return quadratic;
}

void SpotLightComponent::setQuadratic(float quadratic)
{
    this->quadratic = quadratic;
}