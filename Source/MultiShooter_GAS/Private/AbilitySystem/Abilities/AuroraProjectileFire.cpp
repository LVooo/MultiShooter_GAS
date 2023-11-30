// Copyright Weilin


#include "AbilitySystem/Abilities/AuroraProjectileFire.h"
#include "Weapon/Projectile.h"
#include "Interfaces/InteractWithCrosshairsInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuroraProjectileFire::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	IInteractWithCrosshairsInterface* InteractWithCrosshairsInterface = Cast<IInteractWithCrosshairsInterface>(GetAvatarActorFromActorInfo());
	if (InteractWithCrosshairsInterface)
	{
		const FVector SocketLocation = InteractWithCrosshairsInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->FinishSpawning(SpawnTransform);
	}
}
