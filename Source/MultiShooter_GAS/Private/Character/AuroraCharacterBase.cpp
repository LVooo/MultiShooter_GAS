// Copyright Weilin


#include "Character/AuroraCharacterBase.h"

#include "AbilitySystem/AuroraAbilitySystemComponent.h"

AAuroraCharacterBase::AAuroraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

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
