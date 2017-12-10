// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UBomberWallBase.generated.h"

UCLASS()
class UBOMBER_API AUBomberWallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUBomberWallBase();

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
		class UStaticMeshComponent* BoxComponent;


protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	
	
};
