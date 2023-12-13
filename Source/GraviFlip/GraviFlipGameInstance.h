// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
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
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	IOnlineSessionPtr SessionInterface;

	virtual void Init() override;
	virtual void OnCreateSessionComplete(FName NameOfSession, bool Succeeded);
	virtual void OnFindSessionComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName NameOfSession, EOnJoinSessionCompleteResult::Type Result);
	virtual void OnDestroySessionComplete(FName NameOfSession, bool Succeeded);
	virtual void OnNetworkFailure(UWorld* InWorld, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
	virtual void OnTravelFailure(UWorld* InWorld, ETravelFailure::Type FailureType, const FString& ErrorString);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSessionSearchComplete(int32 NumSessions);

	UFUNCTION(BlueprintCallable)
	void CreateServer(FName SessionName, int32 MaxPlayers);

	UFUNCTION(BlueprintCallable)
	void FindSessions();

	UFUNCTION(BlueprintCallable)
	void JoinServer();

	void JoinSession(FName NameOfSession, const FOnlineSessionSearchResult &DesiredSession);
	
	UFUNCTION(BlueprintCallable)
	void JoinSession(int32 Index);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Create Session Settings")
	bool bShouldAdvertise;

private:

	TArray<FOnlineSessionSearchResult> SearchResults;
	
public:
	UFUNCTION(BlueprintCallable)
	FString GetServerName(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	int32 GetServerPing(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	FString GetPlayerCount(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	int32 GetNumSessions() const;

};
