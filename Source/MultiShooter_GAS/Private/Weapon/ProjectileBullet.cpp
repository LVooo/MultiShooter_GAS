// Copyright Weilin


#include "Weapon/ProjectileBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBullet::AProjectileBullet()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true; // 子弹旋转跟随子弹速度
	ProjectileMovementComponent->SetIsReplicated(true);
}
