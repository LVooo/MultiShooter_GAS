// Copyright Weilin


#include "Player/AuroraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuroraPlayerController::AAuroraPlayerController()
{
	bReplicates = true;
}

void AAuroraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuroraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuroraContext, 0);
}
