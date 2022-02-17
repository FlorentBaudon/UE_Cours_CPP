// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "FPSPlayer.generated.h"

UCLASS()
class COURS_CPP_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSPlayer();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	USkeletalMeshComponent* Gun;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AProjectile> Projectile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveFoward(float v);
	void MoveRight(float v);

	UFUNCTION(BlueprintNativeEvent)
	void Action();

	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
