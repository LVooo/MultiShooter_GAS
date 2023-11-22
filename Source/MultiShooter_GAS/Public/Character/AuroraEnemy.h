// Copyright LVooo

#pragma once

#include "CoreMinimal.h"
#include "AuroraCharacterBase.h"
#include "AuroraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MULTISHOOTER_GAS_API AAuroraEnemy : public AAuroraCharacterBase
{
	GENERATED_BODY()
public:
	AAuroraEnemy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
