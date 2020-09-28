// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Character_BuildingESC.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class BUILDINGESCAPE_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UStaticMesh* SM_PickUp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	//Remove this?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		float Weight;

	UPROPERTY()
		class UInventoryComponent* MyInventory;

	virtual void Use(class ACharacter_BuildingESC* Character) PURE_VIRTUAL(UItem, );

	UFUNCTION()
		virtual	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult) PURE_VIRTUAL(UItem, );

	UFUNCTION(BlueprintImplementableEvent)
		void OnUse(class ACharacter_BuildingESC* Character);
};
