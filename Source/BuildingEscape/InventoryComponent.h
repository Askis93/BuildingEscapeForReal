// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemNew.h"
#include "Containers/Array.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected: 
	//UPROPERTY(Replicated)
	//TArray<FString> Items;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	//bool AddItem(class AItem* Item);
	//void Item(class AItem* Item);
	TArray<int32> Items;
	static void ShowInventoryComp();
		
};
