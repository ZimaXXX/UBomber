// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UBomberFloorBase.generated.h"

/**
* Actor for generating Floor of the Procedural Map
*/
UCLASS()
class UBOMBER_API AUBomberFloorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUBomberFloorBase();

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UStaticMeshComponent* PlaneComponent;

protected:
	
};
