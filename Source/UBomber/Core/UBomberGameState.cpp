// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberGameState.h"
#include "Engine/World.h"
#include "Core/UBomberPlayerState.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AUBomberGameState::AUBomberGameState() : Super(){
	CurrentGameTimeInSeconds = -1;
}

TArray<bool> AUBomberGameState::GetResultsForControllers()
{
	TArray<bool> ResultArray;
	ResultArray.Init(false, 2);
	for (int i = 0; i < 2; ++i) {
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), i);
		if (PC->PlayerState && PC->PlayerState->IsA<AUBomberPlayerState>()) {
			AUBomberPlayerState* UB_PS = Cast<AUBomberPlayerState>(PC->PlayerState);
			ResultArray[i] = UB_PS->WonLastGame;
		}
	}
	return ResultArray;

}


 