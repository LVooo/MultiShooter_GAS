// Copyright Weilin


#include "Player/AuroraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/AuroraEnhancedInputComponent.h"

AAuroraPlayerController::AAuroraPlayerController()
{
	bReplicates = true;
}

void AAuroraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuroraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuroraContext, 0);	
	}
}

void AAuroraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuroraEnhancedInputComponent* AuroraEnhancedInputComponent = CastChecked<UAuroraEnhancedInputComponent>(InputComponent);
	AuroraEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuroraPlayerController::Move);
	AuroraEnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AAuroraPlayerController::Turn);
	AuroraEnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuroraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuroraPlayerController::Turn(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(InputAxisVector.X);
		ControlledPawn->AddControllerPitchInput(-InputAxisVector.Y);
	}
}

void AAuroraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, *InputTag.ToString());
}

void AAuroraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2, 2.f, FColor::Blue, *InputTag.ToString());
}

void AAuroraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, *InputTag.ToString());
}
