// Fill out your copyright notice in the Description page of Project Settings.


#include "GraviGameMode.h"
#include "GameFramework/GameMode.h"
#include "GraviFlip/Character/GraviPlayerController.h"
#include "GraviFlip/GraviGameState.h"
#include "Kismet/GameplayStatics.h"

AGraviGameMode::AGraviGameMode() {
	GraviPlayerControllers.SetNum(20);
}


/// <summary>
/// Called when a player joins lobby & is assigned a player controller
/// Adds them to the array of GraviPlayerControllers
/// </summary>
/// <param name="NewPlayer">Joining Player's PlayerController</param>
void AGraviGameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);
	if (AGraviPlayerController* NewGraviPlayer = Cast<AGraviPlayerController>(NewPlayer)) {
		GraviPlayerControllers.Add(NewGraviPlayer);
		UpdatePlayerList();
	}
}

/// <summary>
/// Called when player leaves the game
/// Removes them from array of GraviPlayerControllers
/// </summary>
/// <param name="ExitingPlayer">Exiting Player's Controller</param>
void AGraviGameMode::Logout(AController* ExitingPlayer) {
	Super::Logout(ExitingPlayer);
	if (AGraviPlayerController* ExitingGraviPlayer = Cast<AGraviPlayerController>(ExitingPlayer)) {
		GraviPlayerControllers.Remove(ExitingGraviPlayer);
		UpdatePlayerList();
	}
}

void AGraviGameMode::UpdatePlayerList() {
	if (AGraviGameState* GraviGameState = Cast<AGraviGameState>(UGameplayStatics::GetGameState(this))) {
		// GameState UpdatePlayerList ?? 
	}
}
