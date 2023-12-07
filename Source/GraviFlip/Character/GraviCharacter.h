// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GraviCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ULegacyCameraShake;

UCLASS()
class GRAVIFLIP_API AGraviCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGraviCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

protected:
	virtual void BeginPlay() override;

	/* Input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") UInputAction* InputMoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") UInputAction* InputLookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") UInputAction* InputJumpAction;
	
	/* Movement */
	void Move(const FInputActionValue& Value);
	void StopMoving();
	void Look(const FInputActionValue& Value);
	virtual void Landed(const FHitResult& Hit) override;


private:
	/* Camera */
	UPROPERTY(VisibleAnywhere, Category = "Camera") UCameraComponent* PlayerCamera;
	// Camera View Bobbing
	UPROPERTY(EditAnywhere, Category = "Camera") TSubclassOf<ULegacyCameraShake> CameraShake;
	UPROPERTY(EditAnywhere, Category = "Camera") TSubclassOf<ULegacyCameraShake> CameraLand;
	UPROPERTY(EditAnywhere, Category = "Camera") float CameraShakeScale;
	UPROPERTY(EditAnywhere, Category = "Camera") float CameraLandScale;
	UPROPERTY() UCameraShakeBase* CameraShakeBase;
	void StartCameraShake();
	void StopCameraShake();

	/* Player Settings */
	UPROPERTY(EditAnywhere, Category = "Settings") float MouseSensitivity;
	UPROPERTY(EditAnywhere, Category = "Settings") bool bIsViewBobbingEnabled;


	/* Misc */
	UPROPERTY(VisibleAnywhere, Category = "Misc") bool bIsWalking;
	
	
	

public:	
	

};
