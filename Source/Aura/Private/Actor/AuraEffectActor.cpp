// Copyright Madmer


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	const IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if (!ASCInterface) return;

	const UAbilitySystemComponent* ASComp = ASCInterface->GetAbilitySystemComponent();
	if (!IsValid(ASComp)) return;

	const auto AttributeSet = Cast<UAuraAttributeSet>(ASComp->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	if (!IsValid(AttributeSet)) return;

	// TODO: Change this to apply Gameplay effect
	UAuraAttributeSet* MutableAttributeSet = const_cast<UAuraAttributeSet*>(Cast<UAuraAttributeSet>(AttributeSet));
	MutableAttributeSet->SetHealth(AttributeSet->GetHealth() + 25.0f);
	Destroy();
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
}
