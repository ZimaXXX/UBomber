// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberWallBase.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
AUBomberWallBase::AUBomberWallBase()
{
	BoxComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BoxComponent->Mobility = EComponentMobility::Static;
	BoxComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = BoxComponent;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUBomberWallBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUBomberWallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}