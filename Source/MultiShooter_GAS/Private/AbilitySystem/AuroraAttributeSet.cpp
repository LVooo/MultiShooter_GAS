// Copyright Weilin


#include "AbilitySystem/AuroraAttributeSet.h"

#include "Net/UnrealNetwork.h"

UAuroraAttributeSet::UAuroraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(20.f);
	InitMaxMana(100.f);
}

void UAuroraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuroraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuroraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuroraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuroraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuroraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// 通知ASC系统
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuroraAttributeSet, Health, OldHealth);
}

void UAuroraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuroraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuroraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuroraAttributeSet, Mana, OldMana);
}

void UAuroraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuroraAttributeSet, MaxMana, OldMaxMana);
}
