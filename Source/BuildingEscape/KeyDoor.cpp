// Copyright Erik 2020


#include "KeyDoor.h"

// Sets default values for this component's properties
UKeyDoor::UKeyDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//TriggerVolume = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (TriggerVolume)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &UKeyDoor::OnOverlapBegin);
	}
	InitialYaw = 0;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;
	
}


// Called when the game starts
void UKeyDoor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UKeyDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void UKeyDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void UKeyDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	// LÄGG EVENTUELLT TILL LJUD!
	//CloseDoorSound = false;
	/*if (!AudioComponent) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}*/
}



