// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberBombBase.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Engine/CollisionProfile.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Core/UBomberCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"
#include "Engine/World.h"

// Sets default values
AUBomberBombBase::AUBomberBombBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bTimerExpired = false;
	bIsBombRemotelyControlled = false;
	BombTime = 3.0f;
	BombRange = 3.0f;

	SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereComponent->Mobility = EComponentMobility::Static;
	SphereComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AUBomberBombBase::OnOwnerOverlapEnd);
	RootComponent = SphereComponent;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
}

void AUBomberBombBase::Initialize(float BombTime, int32 BombRange, bool bIsBombRemotelyControlled) {
	this->BombTime = BombTime;
	this->BombRange = BombRange;
	this->bIsBombRemotelyControlled = bIsBombRemotelyControlled;
}

void AUBomberBombBase::OnOwnerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == GetOwner()) {
		SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}
}

// Called when the game starts or when spawned
void AUBomberBombBase::BeginPlay()
{
	Super::BeginPlay();

	if (!bIsBombRemotelyControlled) {
		ToggleTimer();
	}	
}

// Called every frame
void AUBomberBombBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

}

float AUBomberBombBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (!bTimerExpired && IsValid(this)) {
		UE_LOG(LogTemp, Warning, TEXT("Damage inflicted to bomb by %s"), *DamageCauser->GetName());
		GetWorld()->GetTimerManager().PauseTimer(BombTimerHandle);
		bTimerExpired = true;
		Detonate();
	}
	return Damage;
}

void AUBomberBombBase::Detonate()
{
	//Send information to BombOwner to update BombCounter
	AActor* const BombOwner = GetOwner();
	if (IsValid(BombOwner) && BombOwner->IsA<AUBomberCharacter>()) {
		AUBomberCharacter* UB_C = Cast<AUBomberCharacter>(BombOwner);
		UB_C->OnBombExploded();
	}
	//Get Actors to Damage (without those behind walls) and Inflict Damage
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);
	const float DamageAmount = 1.f;
	TArray<AActor*> ActorsToDamage = GetActorsToDamage(true);
	for (AActor* Actor : ActorsToDamage) {
		if (IsValid(Actor)) {
			Actor->TakeDamage(DamageAmount, DamageEvent, NULL, this);
		}
	}
	//Call BP Event
	OnBombExploded();
	//Remove Bomb from game
	this->Destroy();
}

TArray<AActor*> AUBomberBombBase::GetActorsToDamage(bool bDrawDebugLines)
{
	TArray<AActor*> FinalActorsArray;
	TArray<FHitResult> ObstacleHitResults;
	FCollisionQueryParams ObstacleCollisionQueryParams;
	ObstacleCollisionQueryParams.AddIgnoredActor(this);
	FCollisionResponseParams CollisionResponseParams = FCollisionResponseParams(ECollisionResponse::ECR_Overlap);

	if (SphereComponent) {
		FVector Origin;
		FVector BoxExtent;
		float SphereRadius;
		UKismetSystemLibrary::GetComponentBounds(SphereComponent, Origin, BoxExtent, SphereRadius);
		
		float TraceLength = SphereRadius * (2 * BombRange + 1);
		TArray<AActor*> TempActors;
		TempActors = GetActorsToDamageFromSide(EBombDamageDirection::Left, TraceLength, bDrawDebugLines);
		for (AActor* Actor : TempActors) {
			FinalActorsArray.AddUnique(Actor);
		}
		TempActors = GetActorsToDamageFromSide(EBombDamageDirection::Right, TraceLength, bDrawDebugLines);
		for (AActor* Actor : TempActors) {
			FinalActorsArray.AddUnique(Actor);
		}
		TempActors = GetActorsToDamageFromSide(EBombDamageDirection::Top, TraceLength, bDrawDebugLines);
		for (AActor* Actor : TempActors) {
			FinalActorsArray.AddUnique(Actor);
		}
		TempActors = GetActorsToDamageFromSide(EBombDamageDirection::Bottom, TraceLength, bDrawDebugLines);
		for (AActor* Actor : TempActors) {
			FinalActorsArray.AddUnique(Actor);
		}

		for (AActor* FinalActor : FinalActorsArray) {
			FString ActorName = FinalActor->GetName();
			UE_LOG(LogTemp, Warning, TEXT("HIT!: %s"), *ActorName);
		}
	}

	return FinalActorsArray;
}

TArray<AActor*> AUBomberBombBase::GetActorsToDamageFromSide(EBombDamageDirection::Type DamageDirection, float TraceLength, bool bDisplayDebugLine)
{
	TArray<AActor*> FinalActorsArray;
	TArray<FHitResult> ObstacleHitResults;
	FCollisionQueryParams ObstacleCollisionQueryParams = FCollisionQueryParams(FName(TEXT("Trace")), false, this);
	FCollisionResponseParams CollisionResponseParams = FCollisionResponseParams(ECollisionResponse::ECR_Overlap);

	FVector TraceVector;
	switch (DamageDirection) {
	case(EBombDamageDirection::Left):
		TraceVector = FVector(0, -TraceLength, 0);
		break;
	case(EBombDamageDirection::Right):
		TraceVector = FVector(0, TraceLength, 0);
		break;
	case(EBombDamageDirection::Top):
		TraceVector = FVector(TraceLength, 0, 0);
		break;
	case(EBombDamageDirection::Bottom):
		TraceVector = FVector(-TraceLength, 0, 0);
		break;
	}
	if (bDisplayDebugLine) {
		DrawDebugLine(
			GetWorld(),
			GetActorLocation(),
			GetActorLocation() + TraceVector,
			FColor(255, 0, 0),
			false, -1, 0,
			12.333
		);
	}
	GetWorld()->LineTraceMultiByChannel(ObstacleHitResults, GetActorLocation(), GetActorLocation() + TraceVector, ECC_Visibility, ObstacleCollisionQueryParams, CollisionResponseParams);
	for (FHitResult HitResult : ObstacleHitResults) {
		FString ActorName = HitResult.Actor->GetName();
		FinalActorsArray.AddUnique(HitResult.Actor.Get());
	}
	return FinalActorsArray;
}

void AUBomberBombBase::ToggleTimer()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// If the timer has expired or does not exist, start it  
		if ((BombTimerHandle.IsValid() == false) || (bTimerExpired))
		{
			GetWorld()->GetTimerManager().SetTimer(BombTimerHandle, this, &AUBomberBombBase::BombTimerExpired, BombTime);
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

void AUBomberBombBase::BombTimerExpired()
{
	bTimerExpired = true;
	
	Detonate();
}

