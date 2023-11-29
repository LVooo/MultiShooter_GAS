// Copyright Weilin


#include "AuroraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuroraGameplayTags FAuroraGameplayTags::GameplayTags;

void FAuroraGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes
	 */
	GameplayTags.Attributes_Primary_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Health"),
		FString("The character's Health")
		);

	GameplayTags.Attributes_Primary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MaxHealth"),
		FString("The character's MaxHealth")
	);

	GameplayTags.Attributes_Primary_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Mana"),
		FString("The character's Mana")
	);

	GameplayTags.Attributes_Primary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MaxMana"),
		FString("The character's MaxMana")
	);
	

	/*
	 * Input Tags
	 */
	GameplayTags.InputTag_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Fire"),
		FString("Input Tag for Left Mouse Button (Fire)")
		);

	GameplayTags.InputTag_Aim = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Aim"),
		FString("Input Tag for Right Mouse Button (Aim)")
		);

	GameplayTags.InputTag_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Jump"),
		FString("Input Tag for Space Button (Jump)")
		);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
		);
}
