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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
	FString PlayerName;

	UFUNCTION(BlueprintNativeEvent, Category = Default)
	void PlayerStateReady();

	float GetSpeedModifier() const;

	void PlaceBomb();
	void OnBombExploded(AUBomberBombBase* BombReference);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		float BombTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		int32 BombRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		uint8 bRemoteDetonatingOn : 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		int32 BombLimit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
		TSubclassOf<AUBomberBombBase> BombClass;

	UFUNCTION(BlueprintCallable, Category = Pickup)
	void PickupFound(EPickupType::Type PickupType);

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:
	int32 BombCounter;
	float SpeedModifier;

	uint8 bTimerExpired : 1;
	void BombTimerExpired();
	FTimerHandle BombTimerHandle;

	AUBomberBombBase* RemoteBombReference;

	UFUNCTION()
		void OnBeginOverlapPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
