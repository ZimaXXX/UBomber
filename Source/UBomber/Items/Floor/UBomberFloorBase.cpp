// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberFloorBase.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
AUBomberFloorBase::AUBomberFloorBase()
{
	PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	PlaneComponent->bGenerateOverlapEvents = false;

	RootComponent = PlaneComponent;

	PrimaryActorTick.bCanEverTick = false;

}