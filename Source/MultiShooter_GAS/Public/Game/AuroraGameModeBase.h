// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuroraGameModeBase.generated.h"

class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class MULTISHOOTER_GAS_API AAuroraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
