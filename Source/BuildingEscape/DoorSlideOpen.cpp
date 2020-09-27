// Copyright Erik 2020

#include "DoorSlideOpen.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorSlideOpen::UDoorSlideOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorSlideOpen::BeginPlay()
{
	Super::BeginPlay();

	InitialZ = GetOwner()->GetActorLocation().Z;
	CurrentZ = InitialZ;
	OpenSlide += InitialZ;
	OpenTheDoor = false;

	FindTrigger();
}


// Called every frame
void UDoorSlideOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (OpenTheDoor) //And if ButtonPressed
	{
		OpenDoor(DeltaTime);
	}
}

void UDoorSlideOpen::OpenDoor(float DeltaTime)
{
	CurrentZ = FMath::FInterpTo(CurrentZ, OpenSlide, DeltaTime, DoorOpenSpeed);
	FVector DoorSlide = GetOwner()->GetActorLocation();
	DoorSlide.Z = CurrentZ;
	GetOwner()->SetActorLocation(DoorSlide);
}

void UDoorSlideOpen::CloseDoor(float DeltaTime)
{

}

void UDoorSlideOpen::FindTrigger() const
{
	if (!ButtonTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it but no pressureplate set!"), *GetOwner()->GetName());
	}
}


