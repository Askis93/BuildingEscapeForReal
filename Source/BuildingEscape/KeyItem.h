// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "KeyItem.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API UKeyItem : public UItem
{
	GENERATED_BODY()

public:

	UKeyItem();

	virtual void Use(class ACharacter_BuildingESC* Character) override;

	virtual	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	UPROPERTY()
	USphereComponent* CollisionComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable)
	UStaticMeshComponent* SM_Key = nullptr;
	
};
