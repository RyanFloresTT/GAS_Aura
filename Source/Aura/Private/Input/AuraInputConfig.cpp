// Copyright Ryan Flores :)


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::GetInputAction(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{
	for (FAuraInputAction AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.GameplayTag.MatchesTagExact(GameplayTag))
		{
			return AbilityInputAction.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAuraInputConfig: Could not find input action for tag %s"), *GameplayTag.ToString());
	}
	return nullptr;
}
