// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGeneratorComponent.h"


// Sets default values for this component's properties
UMapGeneratorComponent::UMapGeneratorComponent()
{
	MapDimensionSize = 7;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMapGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
	MapGenerator = NewObject<UMapGenerator>();
	FMapDataStruct MapData = MapGenerator->GenerateMapData(MapDimensionSize);
	SpawnProceduralMap(MapData);
	// ...
	
}


// Called every frame
void UMapGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMapGeneratorComponent::SpawnProceduralMap(FMapDataStruct MapData)
{
	UE_LOG(LogTemp, Warning, TEXT("Ready to spwn map!"));
}

