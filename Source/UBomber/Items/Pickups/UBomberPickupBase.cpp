// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberPickupBase.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
AUBomberPickupBase::AUBomberPickupBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PickupType = EPickupType::NONE;

	PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	PlaneComponent->bGenerateOverlapEvents = false;
	
	RootComponent = PlaneComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->bGenerateOverlapEvents = true;
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxComponent->SetupAttachment(PlaneComponent);

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUBomberPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUBomberPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AUBomberPickupBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	//Super::ReceiveAnyDamage_Implementation(Damage, DamageType, InstigatedBy, DamageCauser);

	if (IsValid(this)) {
		UE_LOG(LogTemp, Warning, TEXT("Damage inflicted to pickup by %s"), *DamageCauser->GetName());
		Destroy();
	}
	return Damage;
}