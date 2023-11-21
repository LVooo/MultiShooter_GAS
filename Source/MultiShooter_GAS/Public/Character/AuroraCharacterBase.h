// Copyright Weilin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuroraCharacterBase.generated.h"

UCLASS()
class MULTISHOOTER_GAS_API AAuroraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuroraCharacterBase();

protected:
	virtual void BeginPlay() override;
};
