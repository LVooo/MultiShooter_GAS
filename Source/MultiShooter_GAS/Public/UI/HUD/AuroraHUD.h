// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuroraHUD.generated.h"

class UAuroraUserWidget;
/**
 * 
 */
UCLASS()
class MULTISHOOTER_GAS_API AAuroraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	TObjectPtr<UAuroraUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuroraUserWidget> OverlayWidgetClass;
};
