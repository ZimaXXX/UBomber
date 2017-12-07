// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberBombBase.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Engine/CollisionProfile.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Core/UBomberCharacter.h"
#include "Engine/World.h"


// Sets default values
AUBomberBombBase::AUBomberBombBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bTimerExpired = false;
	bIsBombRemotelyControlled = false;
	BombTime = 3.0f;

	//USceneComponent* DummyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//UCapsuleComponent* CapsuleRoot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//CapsuleRoot->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	//RootComponent = CapsuleRoot;
	SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SphereComponent->SetupAttachment(GetRootComponent());	
	SphereComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AUBomberBombBase::OnOwnerOverlapEnd);

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

	ToggleTimer();
	
}

// Called every frame
void AUBomberBombBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	
	AActor* const BombOwner = GetOwner();
	if (IsValid(BombOwner) && BombOwner->IsA<AUBomberCharacter>()) {
		AUBomberCharacter* UB_C = Cast<AUBomberCharacter>(BombOwner);
		UB_C->OnBombExploded();
	}
	
	this->Destroy();
}

