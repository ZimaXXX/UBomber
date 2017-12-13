// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UBomberPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UBOMBER_API AUBomberPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AUBomberPlayerController();
protected:

	/**
	* Override for setting input methods
	*/
	virtual void SetupInputComponent() override;
	/**
	* Override for saving Victories count to GameSession just before game restart
	*/
	virtual void PreClientTravel(const FString & PendingURL, ETravelType TravelType, bool bIsSeamlessTravel) override;
	/**
	* Override for loading Victories count to GameSession when Pawn and PlayerState are ready
	*/
	virtual void BeginPlayingState() override;

	/**
	* Override for showing and preparing end game text in HUD
	*/
	virtual bool SetPause(bool bPause, FCanUnpause CanUnpauseDelegate) override;
	
private:
	//Input methods
	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void PlaceBomb();	
	void RestartGame();
	void ExitGame();
};
