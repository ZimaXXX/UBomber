// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UBomberWallBase.generated.h"
/**
* Base for game Walls. Walls block Bomb impact
*/
UCLASS()
class UBOMBER_API AUBomberWallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUBomberWallBase();

	/**
	* Box for Wall mesh
	*/
	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UStaticMeshComponent* BoxComponent;
	
};
