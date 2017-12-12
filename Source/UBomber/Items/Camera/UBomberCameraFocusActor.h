// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UBomberCameraFocusActor.generated.h"

UCLASS()
class UBOMBER_API AUBomberCameraFocusActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUBomberCameraFocusActor(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Arm)
		float MinArmLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Arm)
		float MaxArmLength;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void GetPlayersPawns(APawn* &PlayerPawn1, APawn* &PlayerPawn2);
	void GetPlayerControllers(APlayerController* &PlayerController1, APlayerController* &PlayerController2);
	void UpdateCamera(FVector Player1Location, FVector Player2Location);
	FVector LastPlayer1Location;
	FVector LastPlayer2Location;
};
