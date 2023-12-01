// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuroraGameplayAbility.h"
#include "AuroraProjectileFire.generated.h"

class AProjectile;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class MULTISHOOTER_GAS_API UAuroraProjectileFire : public UAuroraGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
