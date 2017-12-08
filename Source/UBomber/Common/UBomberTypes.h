#pragma once

#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "UBomberTypes.generated.h"

/** Structure that defines a level up table entry */
USTRUCT(BlueprintType)
struct FPlayerData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FPlayerData()
		: PlayerName("")
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		int32 PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		UMaterial* MeshMaterial;

};

UENUM(BlueprintType)
namespace EPickupType
{
	enum Type
	{
		NONE,
		LONGER_BOMB_BLASTS,
		MORE_BOMBS,
		FASTER_RUN_SPEED,
		REMOTE_CONTROLLED_BOMBS
	};
}

namespace EPickupType
{
	inline const TCHAR* ToString(EPickupType::Type Type)
	{
		switch (Type)
		{
		case LONGER_BOMB_BLASTS:
			return TEXT("Longer Blasts");

		case MORE_BOMBS:
			return TEXT("More Bombs");

		case FASTER_RUN_SPEED:
			return TEXT("Faster Run");

		case REMOTE_CONTROLLED_BOMBS:
			return TEXT("Remote Bombs");

		default:
			return TEXT("INVALID");
		}
	}
}

USTRUCT(BlueprintType)
struct FMapDataStruct
{
	GENERATED_USTRUCT_BODY()

public:

	FMapDataStruct()
		: Height(0), Width(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		uint8 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		uint8 Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		TArray<uint8> MapTiles;

};