// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UBomberCameraFocusActor.generated.h"

/**
* Actor for maintain panning camera logic
*/
UCLASS()
class UBOMBER_API AUBomberCameraFocusActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AUBomberCameraFocusActor(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraArmComponent;

	/**
	* Minimal Arm length to prevent too close panning in
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Arm)
		float MinArmLength;

	/**
	* Maximal Arm length to prevent too far panning out
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Arm)
		float MaxArmLength;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/**
	* Fetches Players from Controllers
	*/
	void GetPlayersPawns(APawn* &PlayerPawn1, APawn* &PlayerPawn2);
	/**
	* Fetches Player Controllers
	*/
	void GetPlayerControllers(APlayerController* &PlayerController1, APlayerController* &PlayerController2);
	/**
	* Updates Camera position on Tick
	*/
	void UpdateCamera(FVector Player1Location, FVector Player2Location);
	/**
	* Stores last known location of Player1 to handle lack of new data after Player death
	*/
	FVector LastPlayer1Location;
	/**
	* Stores last known location of Player1 to handle lack of new data after Player death
	*/
	FVector LastPlayer2Location;
};
