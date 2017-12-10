// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Common/UBomberTypes.h"
#include "UBomberGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API AUBomberGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AUBomberGameMode(const FObjectInitializer& ObjectInitializer);

	//Overrides
	virtual void BeginPlay() override;
	UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

};
