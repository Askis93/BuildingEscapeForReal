// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character_BuildingESC.h"
#include "InventoryComponent.h"
//#include "Components/StaticMeshComponent.h"
#include "PickUps.generated.h"

UCLASS()
class BUILDINGESCAPE_API APickUps : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUps();

	class UInventoryComponent* InvenComp;

protected:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

	

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemType")
		FString ItemType;*/

	//enum class ItemsCategory{Key, Time, Hint, Light};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void AddToInv(class ACharacter_BuildingESC* Player);

};
