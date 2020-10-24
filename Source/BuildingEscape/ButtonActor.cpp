// Copyright Erik 2020


#include "ButtonActor.h"

// Sets default values
AButtonActor::AButtonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	RootComponent = ButtonMesh;

	ButtonMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh2"));
	ButtonMesh2->SetupAttachment(ButtonMesh);

}

// Called when the game starts or when spawned
void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonActor::PressButton(ACharacter_BuildingESC* Player)
{
	if (Player)
	{
		if (DoorToOpen.Num() != 0)
		{
			for (class AButtonDoor* Doors : DoorToOpen)
			{
				Doors->HasAllButtonPressed.Add(this);
			}
			ButtonsLeft = DoorToOpen[0]->Buttons.Num() - DoorToOpen[0]->HasAllButtonPressed.Num();
			FString PrintButtons = "Buttons left to open door: " + FString::FromInt(ButtonsLeft);
			FString ButtonPressed = "Button Pressed: " + this->GetName();
			if (GEngine && ButtonsLeft >= 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, ButtonPressed, true, { 1.5f ,1.5f });
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, PrintButtons, true, { 1.5f ,1.5f });
			}

		}
	}

}

