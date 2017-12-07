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

	DECLARE_MULTICAST_DELEGATE(FOnBombTimerFinished)
	FOnBombTimerFinished OnBombTimerFinished;

	// Sets default values for this actor's properties
	AUBomberBombBase(const FObjectInitializer& ObjectInitializer);

	void Initialize(float BombTime, int32 BombRange, bool bIsBombRemotelyControlled);

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UStaticMeshComponent* SphereComponent;

	UFUNCTION()
	void OnOwnerOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		float BombTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		int32 BombRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		uint8 bIsBombRemotelyControlled : 1;

	UFUNCTION(BlueprintImplementableEvent, Category = Bomb)
		void OnBombExploded();

	TArray<AActor*> GetActorsToDamage(bool bDrawDebugLines);
	TArray<AActor*> GetActorsToDamageFromSide(EBombDamageDirection::Type DamageDirection, float TraceLength, bool bDisplayDebugLine);
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
private:

	uint8 bTimerExpired : 1;
	void ToggleTimer();
	void BombTimerExpired();
	FTimerHandle BombTimerHandle;
};
