// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberPlayerController.h"
#include "Core/UBomberGameMode.h"
#include "Core/UBomberPlayerState.h"
#include "Core/UBomberCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerState.h"
#include "Engine/World.h"

void AUBomberPlayerController::BeginPlay() {
	Super::BeginPlay();
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
	}	
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
