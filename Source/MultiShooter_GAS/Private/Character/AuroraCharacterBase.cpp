// Copyright Weilin


#include "Character/AuroraCharacterBase.h"

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
