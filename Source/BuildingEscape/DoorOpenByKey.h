// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Character_BuildingESC.h"
#include "InventoryComponent.h"
#include "PickUps.h"
#include "DoorOpenByKey.generated.h"

UCLASS()
class BUILDINGESCAPE_API ADoorOpenByKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorOpenByKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckPlayerInventory(class ACharacter_BuildingESC* Player);

	UFUNCTION()
		void OpenDoor(float delta);
	UFUNCTION()
		void OpenUpwards(float delta);


	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* DoorMesh;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* KeyMesh;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KeyToOpenDoor")
		TArray<class APickUps*> NeededKey;
		
	TArray<bool> DoIHaveAllKeys;

	class UInventoryComponent* InvenComp;


	float InitialYaw;
	float CurrentYaw;

	float InitialZ;
	float CurrentZ;


	UPROPERTY(EditAnywhere)
		float OpenAngle = 0.f;
	UPROPERTY(EditAnywhere)
		float OpenUp = 0.f;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 1.f;

	bool OpenTheDoor;

	bool OpenDoorSound = false;

	UPROPERTY(EditAnywhere)
		class UAudioComponent* AudioComponent1 = nullptr;
	UPROPERTY(EditAnywhere)
		class UAudioComponent* AudioComponent2 = nullptr;
	
	TArray<UAudioComponent*> Sounds;
};
