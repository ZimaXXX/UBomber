// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UBomberBombBase.generated.h"

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

	UFUNCTION()
	void OnOwnerOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UCapsuleComponent* CapsuleRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UStaticMeshComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		float BombTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		int32 BombRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		uint8 bIsBombRemotelyControlled : 1;


private:
	uint8 bTimerExpired : 1;
	void ToggleTimer();
	void BombTimerExpired();
	FTimerHandle BombTimerHandle;
};
