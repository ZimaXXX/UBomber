// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberCameraFocusActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Engine/World.h"


// Sets default values
AUBomberCameraFocusActor::AUBomberCameraFocusActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MinArmLength = 900.f;
	MaxArmLength = 2000.f;
	FVector LastPlayer1Location = FVector::ZeroVector;
	FVector LastPlayer2Location = FVector::ZeroVector;

	RootComponent = CreateDefaultSubobject<USceneComponent>("DummyRoot");
	// Create a camera boom attached to the root (capsule)
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArmComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	CameraArmComponent->TargetArmLength = 1000.f;
	//Prevent Camera from being blocked by map elements
	CameraArmComponent->bDoCollisionTest = false;
	CameraArmComponent->RelativeRotation = FRotator(270.f, 0.f, 0.f);

	// Create a camera and attach to boom
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(CameraArmComponent, FAttachmentTransformRules::KeepWorldTransform, USpringArmComponent::SocketName);
	
	//CameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUBomberCameraFocusActor::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Player1;
	APlayerController* Player2;
	GetPlayerControllers(Player1, Player2);
	if (Player1 && Player2) {
		//UE_LOG(LogTemp, Warning, TEXT("Got both!"));
		Player1->SetViewTargetWithBlend(this, 0.f);
		//Player2->SetViewTargetWithBlend(this, 0.f);
	}
}

// Called every frame
void AUBomberCameraFocusActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Get Player Pawns
	APawn* PlayerPawn1;
	APawn* PlayerPawn2;
	GetPlayersPawns(PlayerPawn1, PlayerPawn2);

	if (PlayerPawn1 && PlayerPawn2) {
		LastPlayer1Location = PlayerPawn1->GetActorLocation();
		LastPlayer2Location = PlayerPawn2->GetActorLocation();

		UpdateCamera(LastPlayer1Location, LastPlayer2Location);
	}
	else if (PlayerPawn1) {
		LastPlayer1Location = PlayerPawn1->GetActorLocation();
		UpdateCamera(LastPlayer1Location, LastPlayer2Location);
	}
	else if (PlayerPawn2) {
		LastPlayer2Location = PlayerPawn2->GetActorLocation();
		UpdateCamera(LastPlayer1Location, LastPlayer2Location);
	}
}

void AUBomberCameraFocusActor::GetPlayersPawns(APawn *& PlayerPawn1, APawn *& PlayerPawn2)
{
	APlayerController* Player1;
	APlayerController* Player2;
	GetPlayerControllers(Player1, Player2);
	if (Player1) {
		PlayerPawn1 = Player1->GetPawn();
	}
	if (Player2) {
		PlayerPawn2 = Player2->GetPawn();
	}
}

void AUBomberCameraFocusActor::GetPlayerControllers(APlayerController *& PlayerController1, APlayerController *& PlayerController2)
{
	PlayerController1 = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController2 = UGameplayStatics::GetPlayerController(GetWorld(), 1);
}

void AUBomberCameraFocusActor::UpdateCamera(FVector Player1Location, FVector Player2Location)
{
	FVector Distance;
	Distance = Player1Location - Player2Location;

	float NewArmLength = 1.5 * Distance.Size();
	if (NewArmLength < MinArmLength) {
		NewArmLength = MinArmLength;
	}
	else if (NewArmLength > MaxArmLength)
		NewArmLength = MaxArmLength;
	CameraArmComponent->TargetArmLength = NewArmLength;
}

