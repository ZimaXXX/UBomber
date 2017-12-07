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