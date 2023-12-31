// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"

#include "Character/AuroraCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Casing.h"
#include "AuroraComponents/CombatComponent.h"
#include "Engine/SkeletalMeshSocket.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; // 设置该武器可以被复制到服务器端和客户端上
	SetReplicateMovement(true); // 同步服务端和客户端的武器位置

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeapnMesh"));
	SetRootComponent(WeaponMesh); // 将mesh设置为root
	
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block); // 物理模拟体上的碰撞响应
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 基于形状和位置上的碰撞检测，在一开始还未捡起枪时禁用

	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	WeaponMesh->MarkRenderStateDirty(); // 实时更新post process
	EnableCustomDepth(true);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/*PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);*/
}

void AWeapon::
EnableCustomDepth(bool bEnable)
{
	if (WeaponMesh)
	{
		WeaponMesh->SetRenderCustomDepth(bEnable);
	}
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap); // 动态委托，重叠时调用该函数
		AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);
	}
	/*if (PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}*/
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, WeaponState);
	DOREPLIFETIME(AWeapon, Ammo);
}

void AWeapon::SetHUDAmmo()
{
	AuroraOwnerCharacter = AuroraOwnerCharacter == nullptr ? Cast<AAuroraCharacter>(GetOwner()) : AuroraOwnerCharacter;
	if (AuroraOwnerCharacter)
	{
		/*AuroraOwnerController = AuroraOwnerController == nullptr ? Cast<AAuroraPlayerController>(AuroraOwnerCharacter->Controller) : AuroraOwnerController;
		if (AuroraOwnerController)
		{
			AuroraOwnerController->SetHUDWeaponAmmo(Ammo);
		}*/
	}
}

void AWeapon::SetHUDWeaponType()
{
	// GetOwner在没有设置Owner前是空的
	AuroraOwnerCharacter = AuroraOwnerCharacter == nullptr ? Cast<AAuroraCharacter>(GetOwner()) : AuroraOwnerCharacter;
	/*if (AuroraOwnerCharacter)
	{
		AuroraOwnerController = AuroraOwnerController == nullptr ? Cast<AAuroraPlayerController>(AuroraOwnerCharacter->Controller) : AuroraOwnerController;
		if (AuroraOwnerController)
		{
			AuroraOwnerController->SetHUDWeaponType(WeaponType);
		}
	}*/
}


void AWeapon::SpendRound()
{
	// 防止子弹减到0以下
	Ammo = FMath::Clamp(Ammo - 1, 0, MagCapacity);
	SetHUDAmmo();
}

void AWeapon::OnRep_Ammmo()
{
	AuroraOwnerCharacter = AuroraOwnerCharacter == nullptr ? Cast<AAuroraCharacter>(GetOwner()) : AuroraOwnerCharacter;
	if (AuroraOwnerCharacter && AuroraOwnerCharacter->GetCombat() && WeaponType == EWeaponType::EWT_Shotgun && IsFull())
	{
		AuroraOwnerCharacter->GetCombat()->JumpToShotgunEnd();
	}
	SetHUDAmmo();
}

void AWeapon::OnRep_Owner()
{
	Super::OnRep_Owner();
	if (Owner == nullptr)
	{
		AuroraOwnerCharacter = nullptr;
		/*
		AuroraOwnerController = nullptr;
	*/
	}
	else
	{
		AuroraOwnerCharacter = AuroraOwnerCharacter == nullptr ? Cast<AAuroraCharacter>(Owner) : AuroraOwnerCharacter;
		if (AuroraOwnerCharacter && AuroraOwnerCharacter->GetEquippedWeapon() && AuroraOwnerCharacter->GetEquippedWeapon() == this)
		{
			SetHUDAmmo();
			SetHUDWeaponType();	
		}
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAuroraCharacter* AuroraCharacter = Cast<AAuroraCharacter>(OtherActor);
	if (AuroraCharacter)
	{
		AuroraCharacter->SetOverlappingWeapon(this);
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAuroraCharacter* AuroraCharacter = Cast<AAuroraCharacter>(OtherActor);
	if (AuroraCharacter)
	{
		AuroraCharacter->SetOverlappingWeapon(nullptr);
	}
}

void AWeapon::SetWeaponState(EWeaponState State)
{
	WeaponState = State;
	OnWeaponStateSet();
}

void AWeapon::OnWeaponStateSet()
{
	// server
	switch (WeaponState)
	{
	case EWeaponState::EWS_Equipped:
		OnEquipped();
		break;
	case EWeaponState::EWS_EquippedSecondary:
		OnEquippedSecondary();
		break;
	case EWeaponState::EWS_Dropped:
		OnDropped();
		break;
	}
}

void AWeapon::OnRep_WeaponState()
{
	OnWeaponStateSet();
}

void AWeapon::OnEquipped()
{
	// 关掉拾取武器widget
	ShowPickupWidget(false);
	// 关掉overlap事件，只需要在服务端上判断是否overlap
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (WeaponType == EWeaponType::EWT_SubmachineGun)
	{
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}
	EnableCustomDepth(false);
}

void AWeapon::OnDropped()
{
	if (HasAuthority())
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_BLUE);
	WeaponMesh->MarkRenderStateDirty(); // 实时更新post process
	EnableCustomDepth(true);
}

void AWeapon::OnEquippedSecondary()
{
	// 关掉拾取武器widget
	ShowPickupWidget(false);
	// 关掉overlap事件，只需要在服务端上判断是否overlap
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->SetEnableGravity(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (WeaponType == EWeaponType::EWT_SubmachineGun)
	{
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}
	EnableCustomDepth(true);
	if (WeaponMesh)
	{
		WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_TAN);
		WeaponMesh->MarkRenderStateDirty();
	}
}

void AWeapon::ShowPickupWidget(bool bShowWidget)
{
	return;
	/*if (PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}*/
}

void AWeapon::Fire(const FVector& HitTarget)
{
	if (FireAnimation)
	{
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}
	if (CasingClass)
	{
		// 需要确保所有的武器都有相同socket名的弹壳
		const USkeletalMeshSocket* AmmoEjectSocket = WeaponMesh->GetSocketByName(FName("AmmoEject"));
		if (AmmoEjectSocket)
		{
			FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(WeaponMesh);
			UWorld* World = GetWorld();
			if (World)
			{
				// 在世界中生成投掷物
				World->SpawnActor<ACasing>(
					CasingClass, // 触发projectile的tracer
					SocketTransform.GetLocation(),
					SocketTransform.GetRotation().Rotator()
					);
			}
		}
	}
	SpendRound();
}

void AWeapon::Dropped()
{
	SetWeaponState(EWeaponState::EWS_Dropped);
	FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	WeaponMesh->DetachFromComponent(DetachRules);
	SetOwner(nullptr);
	AuroraOwnerCharacter = nullptr;
	/*
	AuroraOwnerController = nullptr;
*/
}

void AWeapon::AddAmmo(int32 AmmoToAdd)
{
	Ammo = FMath::Clamp(Ammo + AmmoToAdd, 0, MagCapacity);
	SetHUDAmmo();
}

bool AWeapon::IsEmpty()
{
	return Ammo <= 0;
}

bool AWeapon::IsFull()
{
	return Ammo == MagCapacity;
}
