// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuroraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */
struct FAuroraGameplayTags
{
public:
 static const FAuroraGameplayTags& Get() { return GameplayTags; }
 static void InitializeNativeGameplayTags();

 FGameplayTag Attributes_Primary_Health;
 FGameplayTag Attributes_Primary_MaxHealth;
 FGameplayTag Attributes_Primary_Mana;
 FGameplayTag Attributes_Primary_MaxMana;

 FGameplayTag InputTag_Fire;
 FGameplayTag InputTag_Aim;
 FGameplayTag InputTag_Jump;
 FGameplayTag InputTag_1;
 FGameplayTag InputTag_2;
 FGameplayTag InputTag_3;
 FGameplayTag InputTag_4;

private:
 static FAuroraGameplayTags GameplayTags;
};
