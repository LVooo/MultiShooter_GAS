// Copyright Weilin


#include "AuroraGameplayTags.h"

#include "GameplayTagsManager.h"

void FAuroraGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken"));
}
