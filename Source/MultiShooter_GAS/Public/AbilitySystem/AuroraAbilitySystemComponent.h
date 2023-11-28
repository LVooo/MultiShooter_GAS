// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuroraAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MULTISHOOTER_GAS_API UAuroraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
