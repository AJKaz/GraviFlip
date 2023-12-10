// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Engine/GameInstance.h"
//#include "OnlineSubsystem.h"
//#include "OnlineSessionSettings.h"
//#include "Interfaces/OnlineSessionInterface.h"
#include "GraviFlipGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GRAVIFLIP_API UGraviFlipGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGraviFlipGameInstance();

protected:
	/* Online Subsystem Stuff */
	/*
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	IOnlineSessionPtr SessionInterface;

	virtual void Init() override;
	virtual void OnCreateSessionComplete(FName NameOfSession, bool Succeeded);
	virtual void OnFindSessionComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName NameOfSession, EOnJoinSessionCompleteResult::Type Result);
	virtual void OnDestroySessionComplete(FName NameOfSession, bool Succeeded);
	virtual void OnNetworkFailure(UWorld* InWorld, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
	virtual void OnTravelFailure(UWorld* InWorld, ETravelFailure::Type FailureType, const FString& ErrorString);

	UFUNCTION(BlueprintCallable)
	void CreateServer();

	UFUNCTION(BlueprintCallable)
	void JoinServer();

	void JoinSession(FName NameOfSession, const FOnlineSessionSearchResult &DesiredSession);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Create Session Settings")
	FName SessionName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Create Session Settings")
	int32 NumPublicConnections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Create Session Settings")
	bool bShouldAdvertise;

	UPROPERTY(BlueprintReadWrite, Category = "Session Info")
	FName CurrentSessionName;
	*/

};
