// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/UBomberTypes.h"
#include "UBomberPickupBase.generated.h"

UCLASS()
class UBOMBER_API AUBomberPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUBomberPickupBase(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UStaticMeshComponent* PlaneComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UBoxComponent* BoxComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	TEnumAsByte<EPickupType::Type> PickupType;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	
	
};
