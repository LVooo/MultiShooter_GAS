// Copyright Weilin


#include "Player/AuroraPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuroraAbilitySystemComponent.h"
#include "AbilitySystem/AuroraAttributeSet.h"

AAuroraPlayerState::AAuroraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuroraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAuroraAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AAuroraPlayerState::GetAbilitySystemComponent() const
{
	return  AbilitySystemComponent;
}
