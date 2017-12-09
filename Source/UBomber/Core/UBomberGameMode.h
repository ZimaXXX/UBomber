// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Common/UBomberTypes.h"
#include "Maps/Components/MapGeneratorComponent.h"
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
	
	UPROPERTY(VisibleAnywhere, Category = Map)
	UMapGeneratorComponent* MapGeneratorComponent;

protected:
	//Overrides
	virtual void BeginPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;


};
