// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuroraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MULTISHOOTER_GAS_API UAuroraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;
};
