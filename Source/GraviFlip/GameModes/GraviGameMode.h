// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GraviGameMode.generated.h"

class AGraviPlayerController;

/**
 * 
 */
UCLASS()
class GRAVIFLIP_API AGraviGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AGraviGameMode();

protected:
	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* ExitingPlayer) override;

private:
	UPROPERTY()
	TArray<AGraviPlayerController*> GraviPlayerControllers;

	void UpdatePlayerList();
};
