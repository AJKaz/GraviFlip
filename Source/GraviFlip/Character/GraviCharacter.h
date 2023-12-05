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

UCLASS()
class GRAVIFLIP_API AGraviCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGraviCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	/* Input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") UInputAction* InputMoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") UInputAction* InputLookAction;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	/* Camera Components */
	UPROPERTY(VisibleAnywhere, Category = "Camera") USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = "Camera") UCameraComponent* FollowCamera;

	
	
	

public:	
	

};
