// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Walls/UBomberWallBase.h"
#include "Items/Pickups/UBomberPickupBase.h"
#include "UBomberDestructableWall.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API AUBomberDestructableWall : public AUBomberWallBase
{
	GENERATED_BODY()
	
public:
	AUBomberDestructableWall(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		uint8 bShouldSpawnPickupOnDestroy : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = Spawning)
		TSubclassOf<AUBomberPickupBase> PickupClass;

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:
	void SpawnRandomPickup();
};
