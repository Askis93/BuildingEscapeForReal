// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "ItemNew.h"
#include "Containers/Array.h"
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
	
	TArray<int32> Items;
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	//bool AddItem(class AItem* Item);
	//void Item(class AItem* Item);
	//static TArray<int32> Items;
	void ShowInventoryComp();
	float TimeRemaining;
	void ShowTime();
	void AddTime(float Value);

	UPROPERTY()
	UInputComponent* PlayerInputComponent = nullptr;
	void SetupPlayerInput();
		
};
