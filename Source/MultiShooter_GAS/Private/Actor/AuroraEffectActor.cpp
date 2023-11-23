// Copyright LVooo


#include "Actor/AuroraEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuroraAttributeSet.h"

AAuroraEffectActor::AAuroraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuroraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: now is const_Cast as a hack
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuroraAttributeSet* AuroraAttributeSet = Cast<UAuroraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuroraAttributeSet::StaticClass()));

		UAuroraAttributeSet* MutableAuroraAttributeSet = const_cast<UAuroraAttributeSet*>(AuroraAttributeSet);
		MutableAuroraAttributeSet->SetHealth(AuroraAttributeSet->GetHealth() + 25.f);
		MutableAuroraAttributeSet->SetMana(AuroraAttributeSet->GetMana() - 25.f);
		Destroy();
	}
}

void AAuroraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAuroraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuroraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuroraEffectActor::EndOverlap);
}


