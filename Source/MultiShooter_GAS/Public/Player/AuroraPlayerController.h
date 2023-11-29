// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuroraPlayerController.generated.h"

class UAuroraAbilitySystemComponent;
class UAuroraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

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
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuroraContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> TurnAction;

	void Move(const FInputActionValue& InputActionValue);
	void Turn(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAuroraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuroraAbilitySystemComponent> AuroraAbilitySystemComponent;

	UAuroraAbilitySystemComponent* GetASC();
};
