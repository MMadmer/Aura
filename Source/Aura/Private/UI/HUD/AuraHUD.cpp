// Copyright Madmer


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	OverlayWidget = CreateWidget<UAuraUserWidget>(PC, OverlayWidgetClass);
	if (!IsValid(OverlayWidget)) return;

	UOverlayWidgetController* WidgetController = GetOverlayWidgetController({PC, PS, ASC, AS});
	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();

	OverlayWidget->AddToViewport();
}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}
