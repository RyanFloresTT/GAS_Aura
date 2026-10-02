// Copyright Ryan Flores :)


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

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
