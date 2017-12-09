// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberGameMode.h"
#include "Core/UBomberGameState.h"
#include "Core/UBomberPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"

AUBomberGameMode::AUBomberGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) 
{

	MapGeneratorComponent = ObjectInitializer.CreateDefaultSubobject<UMapGeneratorComponent>(this, TEXT("MapGenerator"));
	MapGeneratorComponent->AttachTo(GetRootComponent());
}

void AUBomberGameMode::BeginPlay()
{
	Super::BeginPlay();
	//FMapDataStruct MapData = MapGenerator->GenerateMapData(7);
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
}

UClass* AUBomberGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	TSubclassOf<AUBomberCharacter> PawnClass = NULL;
	if (InController->IsA<AUBomberPlayerController>()) {
		AUBomberGameState* UB_GS = GetGameState<AUBomberGameState>();
		AUBomberPlayerController* UB_PC = Cast<AUBomberPlayerController>(InController);
		if (UB_PC->GetLocalPlayer()) {
			int32 PlayerControllerIndex = UB_PC->GetLocalPlayer()->GetControllerId();
			if (PlayerControllerIndex < UB_GS->PlayersPawns.Num()) {
				PawnClass = UB_GS->PlayersPawns[PlayerControllerIndex];
			}
		}
	}

	if(!PawnClass){
		PawnClass = Super::GetDefaultPawnClassForController_Implementation(InController);
	}	
	
	return PawnClass;
}



