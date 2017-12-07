// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberCharacter.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Core/UBomberPlayerState.h"
#include "Player/UBomberCharMovementComponent.h"

// Sets default values
AUBomberCharacter::AUBomberCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UUBomberCharMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SpeedModifier = 1.0f;
	BombRange = 0;
	BombLimit = 1;
	BombTime = 3.0f;
	BombCounter = 0;
	bIsBombRemotelyControlled = false;

	SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereComponent->SetupAttachment(GetRootComponent());

	PrimaryActorTick.bCanEverTick = true;
}

void AUBomberCharacter::PlayerStateReady_Implementation()
{
	if (!this->PlayerName.IsEmpty() && PlayerState) {
		PlayerState->PlayerName = this->PlayerName;
	}
}

void AUBomberCharacter::OnBombExploded()
{
	UE_LOG(LogTemp, Warning, TEXT("My bomb exploded!"));
	BombCounter--;
}

// Called when the game starts or when spawned
void AUBomberCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void AUBomberCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);
	if (PlayerState) {
		PlayerStateReady();
	}
}

float AUBomberCharacter::GetSpeedModifier() const
{
	return SpeedModifier;
}

void AUBomberCharacter::PlaceBomb() {
	if (BombCounter >= BombLimit) {
		UE_LOG(LogTemp, Warning, TEXT("Bomb limit reached!"));
		return;
	}

	FVector Location = this->GetActorLocation();
	//Location.Z = 0;
	FRotator Rotation = this->GetActorRotation();
	FTransform SpawnTransform(Rotation, Location);
	FActorSpawnParameters SpawnInfo;
	TSubclassOf<AUBomberBombBase> NewBombClass;
	if (BombClass) {
		NewBombClass = BombClass;
	}
	else {
		NewBombClass = AUBomberBombBase::StaticClass();
	}
	auto DeferredBomb = Cast<AUBomberBombBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, NewBombClass, SpawnTransform));
	if (DeferredBomb != nullptr)
	{
		DeferredBomb->Initialize(BombTime, BombRange, bIsBombRemotelyControlled);

		AActor* SpawnedActor = UGameplayStatics::FinishSpawningActor(DeferredBomb, SpawnTransform);
		AUBomberBombBase* BombActor = Cast<AUBomberBombBase>(SpawnedActor);
		if (BombActor) {
			BombActor->SetOwner(this);
			UE_LOG(LogTemp, Warning, TEXT("Placing bomb!"));
			BombCounter++;
		}
	}
}

// Called every frame
void AUBomberCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

