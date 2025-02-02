// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class AFPSProjectile;
class USoundBase;
class UAnimSequence;
class UParticleSystem;
class UPawnNoiseEmitterComponent;


UCLASS()
class AFPSCharacter : public ACharacter
{
	GENERATED_BODY()


public:
    AFPSCharacter();

		
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1PComponent; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

protected:
	
	/** Fires a projectile. */
	void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;


public:
    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    TSubclassOf<AFPSProjectile> ProjectileClass;

    /** Sound to play each time we fire */
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
    USoundBase* FireSound;

    /** AnimMontage to play each time we fire */
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
    UAnimSequence* FireAnimation;
    
    /** Flag for if the player is holding the objective Actor */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Gameplay")
    bool bIsHoldingObjective;

protected:

    /** Pawn mesh: 1st person view  */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    USkeletalMeshComponent* Mesh1PComponent;

    /** Gun mesh: 1st person view (seen only by self) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    USkeletalMeshComponent* GunMeshComponent;

    /** First person camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* CameraComponent;

	/** Sound emitter producing sound from the player projectile */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
    UPawnNoiseEmitterComponent* NoiseEmitterComponent;
};

