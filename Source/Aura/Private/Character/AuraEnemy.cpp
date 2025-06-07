// Copyright Madmer


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent) MeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (!IsValid(MeshComponent)) return;

	MeshComponent->SetRenderCustomDepth(true);
	MeshComponent->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	if (!IsValid(Weapon)) return;

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnhighlightActor()
{
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (!IsValid(MeshComponent)) return;

	MeshComponent->SetRenderCustomDepth(false);

	if (!IsValid(Weapon)) return;

	Weapon->SetRenderCustomDepth(false);
}
