// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerBox.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "ButtonPressing.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UButtonPressing : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UButtonPressing();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//Called when grabbing and releasing an item
	void ButtonPress(); 

private:
	float Reach = 200.f;
	
	//Input Component
	void SetupInputComponent();
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;
	
	//Return the line trace end
	FVector GetPlayerReach() const;

	//Get player position in world
	FVector GetPlayerWorldPos() const;

	//Return the first actor within reach with physics body
	FHitResult GetFirstTriggerInReach() const;

	//TriggedDoor
	void FindTriggedDoor();
	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggedDoor = nullptr;
};
