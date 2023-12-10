// Fill out your copyright notice in the Description page of Project Settings.


#include "GraviFlipGameInstance.h"
//#include "Kismet/GameplayStatics.h"
//#include "Engine/GameInstance.h"
//#include "Engine/World.h"
//#include "Engine/Engine.h"

UGraviFlipGameInstance::UGraviFlipGameInstance() {
	/* Steam Sessions
	SessionName = FName("Boring Session Name");
	NumPublicConnections = 20;
	bShouldAdvertise = true;
	CurrentSessionName = FName("");
	*/
}

/* Steam Session Subsystem
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
		CurrentSessionName = NameOfSession;
		GetWorld()->ServerTravel("Game/Maps/TestingLevel?listen");
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed To Create Session: %s"), NameOfSession);
	}
}

void UGraviFlipGameInstance::OnFindSessionComplete(bool Succeeded) {
	if (Succeeded && SessionSearch) {
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		if (SearchResults.Num()) {
			this->JoinSession(FName("SessionName"), SearchResults[0]);	// This just joins the first found session, should be changed in future to pick session
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed To Find Sessions. Please Try Again."));
	}
}

void UGraviFlipGameInstance::OnJoinSessionComplete(FName NameOfSession, EOnJoinSessionCompleteResult::Type Result) {
	if (Result == EOnJoinSessionCompleteResult::Success) CurrentSessionName = NameOfSession;
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
	if (SessionInterface) {
		SessionInterface->DestroySession(CurrentSessionName);
	}
}

void UGraviFlipGameInstance::OnTravelFailure(UWorld* InWorld, ETravelFailure::Type FailureType, const FString& ErrorString) {
	UE_LOG(LogTemp, Warning, TEXT("Travel Error"));
	if (SessionInterface) {
		SessionInterface->DestroySession(CurrentSessionName);
	}
}

void UGraviFlipGameInstance::CreateServer() {
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = false;
	SessionSettings.bUsesPresence = true;
	SessionSettings.bAllowInvites = true;
	SessionSettings.bShouldAdvertise = bShouldAdvertise;
	SessionSettings.NumPublicConnections = NumPublicConnections;

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
*/
