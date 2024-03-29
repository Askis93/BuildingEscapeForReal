// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Containers/Array.h"
#include "InventoryComponent.h"
#include "DoorOpenByKey.h"
#include "Character_BuildingESC.generated.h"

UCLASS()
class BUILDINGESCAPE_API ACharacter_BuildingESC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_BuildingESC();

	bool bIsPickingUp = false;

	class UInventoryComponent* PlayerInventoryComp;

	class ULineTracer* LineTraceComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
		class USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger Capsule")
		class UCapsuleComponent* TriggerCapsule;

	class ADoorOpenByKey* CurrentDoor = nullptr;

	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void LookUpRate(float Value);

	void StartSprint();
	void EndSprint();

	UFUNCTION()
	void CrouchDown();
	UFUNCTION()
	void CrouchUp();

	void BeginPickUp();

	void Interact();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float SprintSpeedMulti;

	UPROPERTY()
	bool bIsSprinting = false;

	
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UInventoryComponent* GetInventoryComp();


	
	
	

};
