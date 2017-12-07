// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberCharacter.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Items/Pickups/UBomberPickupBase.h"
#include "Core/UBomberPlayerState.h"
#include "Engine/World.h"
#include "Player/UBomberCharMovementComponent.h"


static const int32 REMOTE_BOMB_LIMIT = 1;
static const float REMOTE_BOMB_PICKUP_TIME = 10.0f;
// Sets default values
AUBomberCharacter::AUBomberCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UUBomberCharMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SpeedModifier = 1.0f;
	BombRange = 0;
	BombLimit = 1;
	BombTime = 3.0f;
	BombCounter = 0;
	bRemoteDetonatingOn = false;

	SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AUBomberCharacter::OnBeginOverlapPickup);
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

void AUBomberCharacter::ToggleTimer()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// If the timer has expired or does not exist, start it  
		if ((BombTimerHandle.IsValid() == false) || (bTimerExpired))
		{
			World->GetTimerManager().SetTimer(BombTimerHandle, this, &AUBomberCharacter::BombTimerExpired, BombTime);
			bTimerExpired = false;
		}
		else
		{
			if (World->GetTimerManager().IsTimerPaused(BombTimerHandle) == true)
			{
				World->GetTimerManager().UnPauseTimer(BombTimerHandle);
			}
			else
			{
				World->GetTimerManager().PauseTimer(BombTimerHandle);
			}
		}

	}
}

void AUBomberCharacter::BombTimerExpired()
{
	UE_LOG(LogTemp, Warning, TEXT("Remote bomb timer finished!"));
	if (bRemoteDetonatingOn && IsValid(RemoteBombReference)) {
		RemoteBombReference->Detonate();
	}
	bRemoteDetonatingOn = false;
}

void AUBomberCharacter::OnBeginOverlapPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor) && OtherActor->IsA<AUBomberPickupBase>()) {
		auto UB_PB = Cast<AUBomberPickupBase>(OtherActor);
		PickupFound(UB_PB->PickupType);
		UB_PB->Destroy();
	}
}

void AUBomberCharacter::PickupFound(EPickupType::Type PickupType)
{
	switch (PickupType) {
	case(EPickupType::LONGER_BOMB_BLASTS):
		BombRange++;
		break;
	case(EPickupType::MORE_BOMBS):
		BombLimit++;
		break;
	case(EPickupType::FASTER_RUN_SPEED):
		SpeedModifier += 0.5f;
		break;
	case(EPickupType::REMOTE_CONTROLLED_BOMBS):
		bRemoteDetonatingOn = true;
		GetWorld()->GetTimerManager().SetTimer(BombTimerHandle, this, &AUBomberCharacter::BombTimerExpired, REMOTE_BOMB_PICKUP_TIME);
		bTimerExpired = false;
		UE_LOG(LogTemp, Warning, TEXT("Remote bomb timer started!"));
		break;
	case(EPickupType::NONE):
	default:
		UE_LOG(LogTemp, Warning, TEXT("PickupType not set!"));
		break;
	}
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
	//If we are controlling remote bomb detonate it
	if (bRemoteDetonatingOn && IsValid(RemoteBombReference)) {
		UE_LOG(LogTemp, Warning, TEXT("Detonating remote bomb!"));
		RemoteBombReference->Detonate();
		RemoteBombReference = NULL;
		return;
	}
	//Check if there is sufficient limit to place new bomb
	if (BombCounter >= BombLimit || (bRemoteDetonatingOn && BombCounter >= REMOTE_BOMB_LIMIT)) {
		UE_LOG(LogTemp, Warning, TEXT("Bomb limit reached!"));
		return;
	}

	//Initialize variables
	FVector Location = this->GetActorLocation();
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
	//Initialize AUBomberBombBase
	auto DeferredBomb = Cast<AUBomberBombBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, NewBombClass, SpawnTransform));
	if (DeferredBomb != nullptr)
	{
		DeferredBomb->Initialize(BombTime, BombRange, bRemoteDetonatingOn);
		//Place bomb
		AActor* SpawnedActor = UGameplayStatics::FinishSpawningActor(DeferredBomb, SpawnTransform);
		AUBomberBombBase* BombActor = Cast<AUBomberBombBase>(SpawnedActor);
		if (BombActor) {
			BombActor->SetOwner(this);
			UE_LOG(LogTemp, Warning, TEXT("Placing bomb!"));
			BombCounter++;
			if (bRemoteDetonatingOn) {
				RemoteBombReference = BombActor;
			}
		}
	}
}

// Called every frame
void AUBomberCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AUBomberCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (IsValid(this)) {
		UE_LOG(LogTemp, Warning, TEXT("Damage inflicted to player by %s"), *DamageCauser->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Player %s killed"), *PlayerState->PlayerName);
		Destroy();
	}
	return Damage;
}