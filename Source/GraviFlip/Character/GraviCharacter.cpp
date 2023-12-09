// Fill out your copyright notice in the Description page of Project Settings.


#include "GraviCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "LegacyCameraShake.h"

AGraviCharacter::AGraviCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	/* Camera Component Setup */
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetMesh());
	PlayerCamera->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	PlayerCamera->SetRelativeLocation(FVector(0.f, 20.f, 165.f));
	PlayerCamera->bUsePawnControlRotation = true;
	SavedCameraMoveShake = nullptr;

	/* Player Settings Setup */
	MouseSensitivity = 0.5f;
	bIsViewBobbingEnabled = true;

	/* Misc */
	bIsWalking = false;
}

void AGraviCharacter::BeginPlay() {
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AGraviCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AGraviCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Setup Input */
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(InputMoveAction, ETriggerEvent::Triggered, this, &AGraviCharacter::Move);
		EnhancedInputComponent->BindAction(InputMoveAction, ETriggerEvent::Completed, this, &AGraviCharacter::StopMoving);
		EnhancedInputComponent->BindAction(InputLookAction, ETriggerEvent::Triggered, this, &AGraviCharacter::Look);
		EnhancedInputComponent->BindAction(InputJumpAction, ETriggerEvent::Triggered, this, &AGraviCharacter::Jump);
	}
}

void AGraviCharacter::Move(const FInputActionValue& Value) {
	if (!bIsWalking && bIsViewBobbingEnabled) {
		StartCameraShake();
	}
	bIsWalking = true;
	const FVector2D MoveVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorRightVector(), MoveVector.X);
	AddMovementInput(GetActorForwardVector(), MoveVector.Y);
}

void AGraviCharacter::StopMoving() {
	bIsWalking = false;
	StopCameraShake();
}

void AGraviCharacter::Look(const FInputActionValue& Value) {
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisValue.X * MouseSensitivity);
	AddControllerPitchInput(LookAxisValue.Y * MouseSensitivity);
}

void AGraviCharacter::StartCameraShake() {
	if (UWorld* World = GetWorld()) {
		if (APlayerController* PlayerController = World->GetFirstPlayerController()) {
			if (APlayerCameraManager* Manager = PlayerController->PlayerCameraManager) {
				SavedCameraMoveShake = Manager->StartCameraShake(CameraMoveShake);
			}
		}
	}
}

void AGraviCharacter::StopCameraShake() {
	if (SavedCameraMoveShake) {
		if (UWorld* World = GetWorld()) {
			if (APlayerController* PlayerController = World->GetFirstPlayerController()) {
				if (APlayerCameraManager* Manager = PlayerController->PlayerCameraManager) {
					Manager->StopCameraShake(SavedCameraMoveShake, false);
				}
			}
		}
	}
}

void AGraviCharacter::Jump() {
	Super::Jump();
}

void AGraviCharacter::Landed(const FHitResult& Hit) {
	Super::Landed(Hit); 
	if (UWorld* World = GetWorld()) {
		if (APlayerController* PlayerController = World->GetFirstPlayerController()) {
			if (APlayerCameraManager* Manager = PlayerController->PlayerCameraManager) {
				Manager->StartCameraShake(CameraLandShake);
			}
		}
	}
}