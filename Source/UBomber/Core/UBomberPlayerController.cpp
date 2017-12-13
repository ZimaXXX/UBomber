// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberPlayerController.h"
#include "Core/UBomberGameMode.h"
#include "Core/UBomberPlayerState.h"
#include "Core/UBomberCharacter.h"
#include "Core/UBomberGameInstance.h"
#include "Core/UBomberGameState.h"
#include "Core/UBomberHUD.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerState.h"
#include "Engine/World.h"

AUBomberPlayerController::AUBomberPlayerController() : Super(){
	//Disables losing focus on map when Player Controller 0's Pawn dies
	bAutoManageActiveCameraTarget = false;
}

void AUBomberPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	ULocalPlayer* const LocalPlayer = GetLocalPlayer();
	if (IsValid(LocalPlayer)) {
		int32 id = LocalPlayer->GetControllerId();
		if (id == 0)
		{
			InputComponent->BindAxis("MoveForward_Player1", this, &AUBomberPlayerController::MoveForward);
			InputComponent->BindAxis("MoveRight_Player1", this, &AUBomberPlayerController::MoveRight);
			InputComponent->BindAction("PlaceBomb_Player1", IE_Pressed, this, &AUBomberPlayerController::PlaceBomb);
		}
		else if (id == 1)
		{
			InputComponent->BindAxis("MoveForward_Player2", this, &AUBomberPlayerController::MoveForward);
			InputComponent->BindAxis("MoveRight_Player2", this, &AUBomberPlayerController::MoveRight);
			InputComponent->BindAction("PlaceBomb_Player2", IE_Pressed, this, &AUBomberPlayerController::PlaceBomb);
		}
		InputComponent->BindAction("RestartGame", IE_Pressed, this, &AUBomberPlayerController::RestartGame).bExecuteWhenPaused = true;
		InputComponent->BindAction("ExitGame", IE_Pressed, this, &AUBomberPlayerController::ExitGame).bExecuteWhenPaused = true;
	}	
}

void AUBomberPlayerController::PreClientTravel(const FString & PendingURL, ETravelType TravelType, bool bIsSeamlessTravel)
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	if (PlayerState) {
		AUBomberPlayerState* UB_PS = Cast<AUBomberPlayerState>(PlayerState);
		if (UB_PS && GameInstance->IsA<UGameInstance>()) {
			UUBomberGameInstance* UB_GI = Cast<UUBomberGameInstance>(GameInstance);
			UB_GI->SetVictoriesForIndex(UGameplayStatics::GetPlayerControllerID(this), UB_PS->NumberOfVictories);
		}
		
	}
	Super::PreClientTravel(PendingURL, TravelType, bIsSeamlessTravel);
}

void AUBomberPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	if (PlayerState) {
		AUBomberPlayerState* UB_PS = Cast<AUBomberPlayerState>(PlayerState);
		if (UB_PS && GameInstance->IsA<UGameInstance>()) {
			UUBomberGameInstance* UB_GI = Cast<UUBomberGameInstance>(GameInstance);
			UB_PS->NumberOfVictories = UB_GI->GetVictoriesForIndex(UGameplayStatics::GetPlayerControllerID(this));
		}
	
	}
}

bool AUBomberPlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate)
{
	bool bIsSetPauseSuccessful = Super::SetPause(bPause, CanUnpauseDelegate);
	if (bIsSetPauseSuccessful) {
		AHUD* HUD = GetHUD();
		if (HUD && HUD->IsA<AUBomberHUD>()) {
			AUBomberHUD* UB_HUD = Cast<AUBomberHUD>(HUD);
			if (bPause) {
				FString FinalText;
				AUBomberGameState* UB_GS = Cast<AUBomberGameState>(GetWorld()->GetGameState());
				if (UB_GS) {
					bool bWinnerFound = false;
					TArray<bool> Results = UB_GS->GetResultsForControllers();
					for (int i = 0; i < Results.Num(); ++i) {
						if (Results[i] == true) {
							auto PC = UGameplayStatics::GetPlayerController(GetWorld(), i);
							if (PC && PC->PlayerState) {
								FinalText = "Player " + PC->PlayerState->PlayerName + " WINS!";
								bWinnerFound = true;
							}
							break;
						}
					}
					if (!bWinnerFound) {
						FinalText = "It's a TIE!";
					}
				}
				UB_HUD->ShowEndScreen(FinalText);
			}
			else {
				UB_HUD->CloseEndScreen();
			}
		}
	}
	return bIsSetPauseSuccessful;
}
void AUBomberPlayerController::MoveForward(float axisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("Going forward: %f"), axisValue);
	APawn* const Pawn = GetPawn();
	if (IsValid(Pawn)) {
		Pawn->AddMovementInput(GetActorForwardVector(), axisValue);
	}

}

void AUBomberPlayerController::MoveRight(float axisValue)
{
	APawn* const Pawn = GetPawn();
	if (IsValid(Pawn)) {
		Pawn->AddMovementInput(GetActorRightVector(), axisValue);
	}
}

void AUBomberPlayerController::PlaceBomb()
{
	APawn* Pawn = GetPawn();
	if (IsValid(Pawn) && Pawn->IsA<AUBomberCharacter>()) {
		AUBomberCharacter* UB_C = Cast<AUBomberCharacter>(Pawn);
		UB_C->PlaceBomb();		
	}
	
}

void AUBomberPlayerController::RestartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to restart level"));
	RestartLevel();

}

void AUBomberPlayerController::ExitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to end game"));
	ConsoleCommand("quit");
}
