#pragma once

#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "UBomberTypes.generated.h"

/** 
* Defines the pickup type
*/

UENUM(BlueprintType)
namespace EPickupType
{
	enum Type
	{
		NONE = 0,
		LONGER_BOMB_BLASTS = 1,
		MORE_BOMBS = 2,
		FASTER_RUN_SPEED = 3,
		REMOTE_CONTROLLED_BOMBS = 4,
	};

}
namespace EPickupType
{
	static const int32 NUMBER_OF_PICKUP_TYPES = 5;
}

/**
* Stores Map metadata
*/
USTRUCT(BlueprintType)
struct FMapDataStruct
{
	GENERATED_USTRUCT_BODY()

public:

	FMapDataStruct()
		: Size(0)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	uint8 Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		TArray<uint8> MapTiles;

};