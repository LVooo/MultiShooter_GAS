// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuroraAnimInstance.h"

#include "Character/AuroraCharacter.h"
#include "Weapon/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAuroraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation(); // 保留父类的行为

	AuroraCharacter = Cast<AAuroraCharacter>(TryGetPawnOwner());
}

void UAuroraAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (AuroraCharacter == nullptr)
	{
		AuroraCharacter = Cast<AAuroraCharacter>(TryGetPawnOwner());
	}
	if (AuroraCharacter == nullptr) return;

	FVector Velocity = AuroraCharacter->GetVelocity();
	Velocity.Z = 0.f; // 在平面中只需要x和y轴分量，忽略垂直方向的分量
	Speed = Velocity.Size(); // 计算速度向量的长度，即速度大小

	bIsInAir =  AuroraCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = AuroraCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = AuroraCharacter->IsWeaponEquipped();
	EquippedWeapon = AuroraCharacter->GetEquippedWeapon();
	bIsCrouched = AuroraCharacter->bIsCrouched;
	bAiming = AuroraCharacter->IsAiming();
	TurningInPlace = AuroraCharacter->GetTurningInPlace();
	bRotateRootBone = AuroraCharacter->ShouldRotateRootBone();
	bElimmed = AuroraCharacter->isElimed();

	// Offset Yaw for Strafing
	FRotator AnimRotation = AuroraCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(AuroraCharacter->GetVelocity());
	FRotator DelataRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AnimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DelataRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;

	// Lean 一堆差值计算
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = AuroraCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = AuroraCharacter->GetAO_Yaw();
	Ao_Pitch = AuroraCharacter->GetAO_Pitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh())
	{
		// 从world中获取的值并求出它的骨骼空间
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		AuroraCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));

		// 只调整本地客户端的右手旋转角度为了减少带宽
		if (AuroraCharacter->IsLocallyControlled())
		{
			bLocallyControlled = true;
			FTransform RightHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("Hand_R"), ERelativeTransformSpace::RTS_World);
			// hand_r的x轴方向为反方向
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() + (RightHandTransform.GetLocation() - AuroraCharacter->GetHitTarget())); 
			RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRotation, DeltaTime, 30.f);
		}
	}

	bUseFABRIK = AuroraCharacter->GetCombatState() == ECombatState::ECS_Unoccupied;
	bUseAimOffsets = AuroraCharacter->GetCombatState() == ECombatState::ECS_Unoccupied && !AuroraCharacter->GetDisableGameplay();
	bTransformRightHand = AuroraCharacter->GetCombatState() == ECombatState::ECS_Unoccupied && !AuroraCharacter->GetDisableGameplay();
}
