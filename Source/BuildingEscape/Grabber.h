// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 200.f;
	
	//PhysicsHandle
	void FindPhysicsHandle();
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	//Input Component
	void SetupInputComponent();
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	//Called when grabbing and releasing an item
	void Grab();
	void Release();	

	//Return the first actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Return the line trace end
	FVector GetPlayerReach() const;

	//Get player position in world
	FVector GetPlayerWorldPos() const;
};
