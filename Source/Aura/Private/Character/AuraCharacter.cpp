// Copyright Madmer


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
		MovementComponent->bConstrainToPlane = true;
		MovementComponent->bSnapToPlaneAtStart = true;
	}

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
