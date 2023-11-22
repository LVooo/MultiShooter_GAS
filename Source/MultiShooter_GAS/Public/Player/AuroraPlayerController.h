// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuroraPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class MULTISHOOTER_GAS_API AAuroraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuroraPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuroraContext;
};
