// Copyright Ryan Flores :)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "CharacterClassDefaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
