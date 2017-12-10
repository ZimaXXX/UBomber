// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberDestructableWall.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Common/UBomberTypes.h"

AUBomberDestructableWall::AUBomberDestructableWall(const FObjectInitializer& ObjectInitializer){
	bShouldSpawnPickupOnDestroy = false;
	BoxComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
}

float AUBomberDestructableWall::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (IsValid(this)) {
		UE_LOG(LogTemp, Warning, TEXT("Damage inflicted to destructable wall by %s"), *DamageCauser->GetName());
		if (bShouldSpawnPickupOnDestroy) {
			SpawnRandomPickup();
		}
	}
	Destroy();
	return Damage;
}

void AUBomberDestructableWall::SpawnRandomPickup()
{	
	int32 NumberOfPickupTypes = EPickupType::NUMBER_OF_PICKUP_TYPES;
	//ommit the 0 valued NONE pickup
	int32 RandomPickupValue = FMath::RandRange(1, NumberOfPickupTypes);
	EPickupType::Type PickupType = static_cast<EPickupType::Type>((uint8)RandomPickupValue);

	AActor* Owner = GetOwner();

	//Initialize variables
	FVector Location = this->GetActorLocation();
	FRotator Rotation = this->GetActorRotation();
	FTransform SpawnTransform(Rotation, Location);
	FActorSpawnParameters SpawnInfo;
	TSubclassOf<AUBomberPickupBase> NewPickupClass;
	if (PickupClass) {
		NewPickupClass = PickupClass;
	}
	else {
		NewPickupClass = AUBomberPickupBase::StaticClass();
	}
	auto DeferredPickup = Cast<AUBomberPickupBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, NewPickupClass, SpawnTransform));
	if (DeferredPickup != nullptr)
	{
		DeferredPickup->PickupType = PickupType;
		//Place bomb
		AActor* SpawnedActor = UGameplayStatics::FinishSpawningActor(DeferredPickup, SpawnTransform);
		AUBomberPickupBase* PickupActor = Cast<AUBomberPickupBase>(SpawnedActor);
		if (PickupActor) {
			//Set Pickups owner to this walls owner because wall is getting destroyed
			PickupActor->SetOwner(Owner);
			UE_LOG(LogTemp, Warning, TEXT("Placing Pickup!"));
		}
	}
}
