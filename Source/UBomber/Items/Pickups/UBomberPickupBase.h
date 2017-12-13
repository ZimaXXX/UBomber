// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/UBomberTypes.h"
#include "UBomberPickupBase.generated.h"
/**
* Actor containing Pickup information
*/
UCLASS()
class UBOMBER_API AUBomberPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AUBomberPickupBase(const FObjectInitializer& ObjectInitializer);

	/**
	* Plane to step up on
	*/
	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UStaticMeshComponent* PlaneComponent;

	/**
	* Box for detecting collisions with Players
	*/
	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UBoxComponent* BoxComponent;

	/**
	* Type of Pickup contained by this Actor
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	TEnumAsByte<EPickupType::Type> PickupType;

protected:
	/**
	* Override for handling damage and destruction
	*/
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
};
