// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "ButtonDoor.h"
#include "ButtonActor.generated.h"

UCLASS()
class BUILDINGESCAPE_API AButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonActor();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* ButtonMesh;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* ButtonMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorToOpen")
		TArray<class AButtonDoor*> DoorToOpen;

	int32 ButtonsLeft;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PressButton(class ACharacter_BuildingESC* Player);

};
