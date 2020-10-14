// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "ItemNew.h"
#include "Containers/Array.h"
#include "PickUps.h"
#include "GameFramework/PlayerController.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected: 
	
	TArray<class APickUps*> Items;
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void ShowInventoryComp();
	//float TimeRemaining;
	//void ShowTime();
	void AddItemToInventory(class APickUps* Item);
	void RemoveItemFromInventory(class APickUps* Item);
	bool CheckInventory(class APickUps* item);

	UPROPERTY()
	class UInputComponent* PlayerInputComponent;
	void SetupPlayerInput();
		
};
