// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/Bombs/UBomberBombBase.h"
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
	void OnBombExploded();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		float BombTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		int32 BombRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		uint8 bIsBombRemotelyControlled : 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb)
		int32 BombLimit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Default)
		TSubclassOf<AUBomberBombBase> BombClass;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;

private:
	int32 BombCounter;
	float SpeedModifier;
};
