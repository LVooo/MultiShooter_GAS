// Copyright Weilin


#include "UI/HUD/AuroraHUD.h"
#include "UI/Widget/AuroraUserWidget.h"
#include "Blueprint/UserWidget.h"

void AAuroraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
