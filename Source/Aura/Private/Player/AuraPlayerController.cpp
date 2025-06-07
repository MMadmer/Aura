// Copyright Madmer


#include "Player/AuraPlayerController.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController(): LastActor(nullptr), ThisActor(nullptr)
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(AuraContext)) return;

	const auto& Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(Subsystem)) return;

	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const auto& EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 * Line trace from cursor. There are several scenarios:
	 *   A. LastActor is null && ThisActor is null
	 *      - Do nothing
	 *   B. LastActor is null && ThisActor is valid
	 *      - Highlight ThisActor
	 *   C. LastActor is valid && ThisActor is null
	 *      - UnHighlight LastActor
	 *   D. Both actors are valid, but LastActor != ThisActor
	 *      - UnHighlight LastActor, and Highlight ThisActor
	 *   E. Both actors are valid, and are the same actor
	 *      - Do nothing
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A
			// Do nothing
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnhighlightActor();
		}
		else if (LastActor != ThisActor)
		{
			// Case D
			LastActor->UnhighlightActor();
			ThisActor->HighlightActor();
		}
		else
		{
			// Case E
			// Do nothing
		}
	}
}
