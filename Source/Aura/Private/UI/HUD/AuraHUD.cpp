// Copyright Ryan Flores :)


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr) {
		OverlayWidgetController = NewObject<UOverlayWidgetController>(GetWorld(), OverlayWidgetControllerClass);
		
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set on BP_AuraHud"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllClass is not set on BP_AuraHud"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);
	
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}