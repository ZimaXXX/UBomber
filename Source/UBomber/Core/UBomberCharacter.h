// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/Bombs/UBomberBombBase.h"
#include "Common/UBomberTypes.h"
#include "UBomberCharacter.generated.h" 

UCLASS()
class UBOMBER_API AUBomberCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUBomberCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleDefaultsOnly, Category = Default)
	class UStaticMeshComponent* SphereComponent;

	//Properties to be set from BP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	FString PlayerName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
	float BombTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
	int32 BombRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
	uint8 bRemoteDetonatingOn : 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
	int32 BombLimit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed)
	float SpeedModifier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
	TSubclassOf<AUBomberBombBase> BombClass;


	UFUNCTION(BlueprintNativeEvent, Category = Default)
	void PlayerStateReady();

	/**
	* Indicator on is the player still playing
	*/
	uint8 bIsAlive;

	/**
	* Method for MovementComponent
	*/
	float GetSpeed() const;

	/**
	* Method for applying pickup to player stats
	*/
	void PickupFound(EPickupType::Type PickupType);

	/**
	* Places bomb on map
	*/
	void PlaceBomb();

	/**
	* Event sent from placed bomb
	*/
	void OnBombExploded(AUBomberBombBase* BombReference);

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:

	/** 
	* Tracks Number of currently placed bombs
	*/
	int32 BombCounter;

	//Bomb Timer related
	uint8 bTimerExpired : 1;
	void BombTimerExpired();
	FTimerHandle BombTimerHandle;

	/**
	* Tracks reference to placed Remote Bomb so Character knows which bomb to detonante and that it was detonated so he can place another one.
	*/
	AUBomberBombBase* RemoteBombReference;

	/**
	* Allows Pickup gathering
	*/
	UFUNCTION()
	void OnBeginOverlapPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
