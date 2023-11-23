// Copyright Weilin


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuroraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuroraAttributeSet* AuroraAttributeSet = CastChecked<UAuroraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuroraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuroraAttributeSet->GetMaxHealth());
}
