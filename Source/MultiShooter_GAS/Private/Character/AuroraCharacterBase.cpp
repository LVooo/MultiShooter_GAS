// Copyright Weilin


#include "Character/AuroraCharacterBase.h"

#include "AbilitySystem/AuroraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "MultiShooter_GAS/MultiShooter_GAS.h"

AAuroraCharacterBase::AAuroraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
}

UAbilitySystemComponent* AAuroraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuroraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuroraCharacterBase::InitAbilityActorInfo()
{
}

void AAuroraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;

	UAuroraAbilitySystemComponent* AuroraASC = CastChecked<UAuroraAbilitySystemComponent>(AbilitySystemComponent);
	AuroraASC->AddCharacterAbilities(StartupAbilities);
}
