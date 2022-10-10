#include "SurAttributeComponent.h"

USurAttributeComponent::USurAttributeComponent()
{
	Health = 100;

}

bool USurAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}