// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "PickUps.h"
#include "KeyDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UKeyDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKeyDoor();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KeyToOpenDoor")
	class APickUps* NeededKey;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OpenDoor(float DeltaTime);
	

private: 
	UPROPERTY(EditAnywhere)
		class UBoxComponent* TriggerVolume;
	
	float InitialYaw;
	float CurrentYaw;
	
	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.f;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 1.f;

	
};
