// Copyright Ryan Flores :)


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			FWidgetControllerParams ControllerParams;
			
			ControllerParams.PlayerController = PlayerController;
			AAuraPlayerState* PlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			ControllerParams.PlayerState = PlayerState;
			ControllerParams.AttributeSet = PlayerState->GetAttributeSet();
			ControllerParams.AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
			
			return AuraHUD->GetOverlayWidgetController(ControllerParams);
		}
	}
	return nullptr;
}

UAuraAttributeWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{	
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			FWidgetControllerParams ControllerParams;
				
			ControllerParams.PlayerController = PlayerController;
			AAuraPlayerState* PlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			ControllerParams.PlayerState = PlayerState;
			ControllerParams.AttributeSet = PlayerState->GetAttributeSet();
			ControllerParams.AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
				
			return AuraHUD->GetAttributeMenuWidgetController(ControllerParams);
		}
	}
		return nullptr;
}

void UAuraAbilitySystemLibrary::InitDefaultAttributes(const UObject* WorldContext, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if (!AuraGameMode) return;

	AActor* Avatar = ASC->GetAvatarActor();
	
	UCharacterClassInfo* ClassInfo = AuraGameMode->CharacterClassInfo;
	
	const FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(Avatar);

	const FGameplayEffectSpecHandle PrimarySpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, EffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandle.Data.Get());
	
	const FGameplayEffectSpecHandle SecondarySpecHandle = ASC->MakeOutgoingSpec(ClassInfo->SecondaryAttributes, Level, EffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandle.Data.Get());
	
	const FGameplayEffectSpecHandle VitalSpecHandle = ASC->MakeOutgoingSpec(ClassInfo->VitalAttributes, Level, EffectContext);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalSpecHandle.Data.Get());
}
