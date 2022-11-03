#include "SurAttributeComponent.h"

USurAttributeComponent::USurAttributeComponent()
{
	Health = 100;

}

bool USurAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USurAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}