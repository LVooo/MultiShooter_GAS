// Copyright Weilin


#include "AuroraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AuroraGameModeBase.h"
#include "CharacterClassInfo.h"
#include "GameplayEffectTypes.h"
#include "Kismet/GameplayStatics.h"

void UAuroraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
                                                              ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
}

UCharacterClassInfo* UAuroraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AAuroraGameModeBase* AuraGameMode = Cast<AAuroraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AuraGameMode == nullptr) return nullptr;
	return AuraGameMode->CharacterClassInfo;
}
