// Fill out your copyright notice in the Description page of Project Settings.


#include "GraviFlipGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

UGraviFlipGameInstance::UGraviFlipGameInstance() {
	// Steam Sessions
	bShouldAdvertise = true;
}

void UGraviFlipGameInstance::Init() {
	Super::Init();

	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get()) {
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGraviFlipGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UGraviFlipGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UGraviFlipGameInstance::OnJoinSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UGraviFlipGameInstance::OnDestroySessionComplete);
		}
	}
	if (GEngine) {
		GEngine->OnNetworkFailure().AddUObject(this, &UGraviFlipGameInstance::OnNetworkFailure);
		GEngine->OnTravelFailure().AddUObject(this, &UGraviFlipGameInstance::OnTravelFailure);
	}
}

void UGraviFlipGameInstance::OnCreateSessionComplete(FName NameOfSession, bool Succeeded) {
	if (Succeeded) {
		//GetWorld()->ServerTravel("/Game/Maps/TestingLevel?listen");
		UE_LOG(LogTemp, Warning, TEXT("SUCCESSFULLY made session: %s"), NameOfSession);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed To Create Session: %s"), NameOfSession);
	}
}

void UGraviFlipGameInstance::FindSessions() {

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false;
	SessionSearch->MaxSearchResults = 10000;	// Possibly many search results with same steam test ID, so get a lot
	SessionSearch->QuerySettings.Set("SEARCH_PRESENCE", true, EOnlineComparisonOp::Equals);
	if (SessionInterface) {
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		
	}

}

void UGraviFlipGameInstance::OnFindSessionComplete(bool Succeeded) {
	if (Succeeded && SessionSearch) {
		SearchResults = SessionSearch->SearchResults;

		OnSessionSearchComplete(SearchResults.Num());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed To Find Sessions. Please Try Again."));
	}
}

void UGraviFlipGameInstance::OnJoinSessionComplete(FName NameOfSession, EOnJoinSessionCompleteResult::Type Result) {
	if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(NameOfSession, JoinAddress);
		if (JoinAddress != "") {
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UGraviFlipGameInstance::OnDestroySessionComplete(FName NameOfSession, bool Succeeded) {
	if (Succeeded) {
		// TODO
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed To Destroy Session: %s"), NameOfSession);
	}
}

void UGraviFlipGameInstance::OnNetworkFailure(UWorld* InWorld, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString) {
	UE_LOG(LogTemp, Warning, TEXT("Network Error"));
	/*if (SessionInterface) {
		SessionInterface->DestroySession(CurrentSessionName);
	}*/
}

void UGraviFlipGameInstance::OnTravelFailure(UWorld* InWorld, ETravelFailure::Type FailureType, const FString& ErrorString) {
	UE_LOG(LogTemp, Warning, TEXT("Travel Error"));
	/*if (SessionInterface) {
		SessionInterface->DestroySession(CurrentSessionName);
	}*/
}

void UGraviFlipGameInstance::CreateServer(FName SessionName, int32 MaxPlayers) {
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = false;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bAllowInvites = true;
	SessionSettings.bShouldAdvertise = bShouldAdvertise;
	SessionSettings.NumPublicConnections = MaxPlayers;

	if (SessionInterface) SessionInterface->CreateSession(0, SessionName, SessionSettings);
}

void UGraviFlipGameInstance::JoinServer() {
	UE_LOG(LogTemp, Warning, TEXT("JoinServer"));

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false;
	SessionSearch->MaxSearchResults = 10000;	// Possibly many search results with same steam test ID, so get a lot
	SessionSearch->QuerySettings.Set("SEARCH_PRESENCE", true, EOnlineComparisonOp::Equals);
	if (SessionInterface) SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UGraviFlipGameInstance::JoinSession(FName NameOfSession, const FOnlineSessionSearchResult &DesiredSession) {
	if (SessionInterface) {
		SessionInterface->JoinSession(0, NameOfSession, DesiredSession);
	}
}

void UGraviFlipGameInstance::JoinSession(int32 Index) {
	if (SessionInterface && SearchResults.IsValidIndex(Index)) {
		SessionInterface->JoinSession(0, FName(GetServerName(Index)), SearchResults[Index]);
	}
}

FString UGraviFlipGameInstance::GetServerName(int32 Index) const {
	if (SearchResults.IsValidIndex(Index)) {
		return SearchResults[Index].Session.SessionSettings.Settings.FindRef("SESSION_NAME").Data.ToString();
	}
	return "Unknown Name";
}

int32 UGraviFlipGameInstance::GetServerPing(int32 Index) const {
	if (SearchResults.IsValidIndex(Index)) {
		return SearchResults[Index].PingInMs;
	}
	return -1;
}

FString UGraviFlipGameInstance::GetPlayerCount(int32 Index) const {
	if (SearchResults.IsValidIndex(Index)) {
		const FOnlineSessionSettings& SessionSettings = SearchResults[Index].Session.SessionSettings;

		// Find the current players and max players keys and extract the values
		const FString CurrentPlayers = SearchResults[Index].Session.SessionSettings.Settings.FindRef("CURRENT_PLAYERS").Data.ToString();
		const FString MaxPlayers = SearchResults[Index].Session.SessionSettings.Settings.FindRef("MAX_PLAYERS").Data.ToString();
		return CurrentPlayers + "/" + MaxPlayers + " Players";
	}

	return "?/?";
}

int32 UGraviFlipGameInstance::GetNumSessions() const {
	return SearchResults.Num();
}


