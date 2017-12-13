// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UBomberBombBase.generated.h"

UENUM()
namespace EBombDamageDirection
{
	enum Type
	{
		Left,
		Right,
		Top,
		Bottom
	};
}
UCLASS()
class UBOMBER_API AUBomberBombBase : public AActor
{
	GENERATED_BODY()
	
public:	

	/**
	* Timer which ends in Detonation
	*/
	DECLARE_MULTICAST_DELEGATE(FOnBombTimerFinished)
	FOnBombTimerFinished OnBombTimerFinished;

	/**
	* Delegate to inform GameMode about explosion to check for Game End
	*/
	DECLARE_DELEGATE_OneParam(FOnBombExploded, AUBomberBombBase*)
	FOnBombExploded OnBombExplodedDelegate;

	AUBomberBombBase(const FObjectInitializer& ObjectInitializer);

	/**
	* Initialization method for deferred spawning
	*/
	void Initialize(float BombTime, int32 BombRange, bool bIsBombRemotelyControlled);

	/**
	* Place for an StaticMesh that renders this Actor
	*/
	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UStaticMeshComponent* SphereComponent;

	/**
	* Event for changing bomb's collision settings. It's initially overlapping Pawns so Owner can place the bomb under him. It starts to block Pawn channel as soon as Player stops overlapping it.
	*/
	UFUNCTION()
	void OnOwnerOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Bomb properties, set from Initialize method if spawned by Character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		float BombTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		int32 BombRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		uint8 bIsBombRemotelyControlled : 1;

	/**
	* Results in bomb explosion
	*/
	void Detonate();

	/**
	* Uses tracelines to find Actors to damage in 4 directions. Uses Visibility channel and is blocked by Walls (both Solid and Destructable)
	*/
	TArray<AActor*> GetActorsToDamage(bool bDrawDebugLines);
	/**
	* Uses tracelines to find Actors to damage in 1 of directions
	*/
	TArray<AActor*> GetActorsToDamageFromSide(EBombDamageDirection::Type DamageDirection, float TraceLength, bool bDisplayDebugLine);

	uint8 bIsInflictingChainDamage : 1;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	/**
	* Override to maintain destruction instigated by other bomb
	*/
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:
	//Bombs timer related
	uint8 bTimerExpired : 1;
	void BombTimerExpired();
	FTimerHandle BombTimerHandle;
};
