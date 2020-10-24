// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
//#include "ButtonActor.h"
#include "ButtonDoor.generated.h"

UCLASS()
class BUILDINGESCAPE_API AButtonDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonDoor();

	TArray<class AButtonActor*> HasAllButtonPressed;

	UPROPERTY(EditAnywhere)
		TArray<class AButtonActor*> Buttons;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

private:

	float InitialYaw;
	float CurrentYaw;
	float AddRotation;

	float InitialZ;
	float CurrentZ;
	float AddZ;


	UPROPERTY(EditAnywhere)
		float OpenAngle = 0.f;
	UPROPERTY(EditAnywhere)
		float OpenUp = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.f;

	bool DoorHasBeenOpened;

	UPROPERTY(EditAnywhere)
		class UAudioComponent* AudioComponent1 = nullptr;
	UPROPERTY(EditAnywhere)
		class UAudioComponent* AudioComponent2 = nullptr;

	TArray<UAudioComponent*> Sounds;

	bool OpenDoorSound = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OpenDoor(float delta);
	UFUNCTION()
		void OpenUpwards(float delta);

};
