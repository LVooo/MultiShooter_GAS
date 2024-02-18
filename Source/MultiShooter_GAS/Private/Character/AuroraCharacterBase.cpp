// Copyright Weilin


#include "Character/AuroraCharacterBase.h"

#include "LowLevelTestAdapter.h"
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

void AAuroraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuroraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
}

void AAuroraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;

	UAuroraAbilitySystemComponent* AuroraASC = CastChecked<UAuroraAbilitySystemComponent>(AbilitySystemComponent);
	AuroraASC->AddCharacterAbilities(StartupAbilities);
}
