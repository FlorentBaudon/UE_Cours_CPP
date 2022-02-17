// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("FPSCamera");
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->bUsePawnControlRotation = true;


	/**** Skeletal mesh configuration ****/
	//Load ressources
	USkeletalMesh* SKMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms") );
	UAnimBlueprint* AnimInstance = LoadObject<UAnimBlueprint>(nullptr, TEXT("/Game/FirstPerson/Animations/FirstPerson_AnimBP.FirstPerson_AnimBP"));
	this->GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	this->GetMesh()->SetSkeletalMesh(SKMesh);
	this->GetMesh()->SetAnimInstanceClass(AnimInstance->GetAnimBlueprintGeneratedClass());
	this->GetMesh()->SetupAttachment(Camera);


	/*** Gun Skeletal Mesh ***/
	//Load Mesh
	USkeletalMesh* GunMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun") );
	//Create gun suboject
	Gun = CreateDefaultSubobject<USkeletalMeshComponent>("GunMesh");
	Gun->SetSkeletalMesh(GunMesh);
	Gun->SetupAttachment(this->GetMesh(), "GripPoint");
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AFPSPlayer::MoveFoward);
	PlayerInputComponent->BindAxis("Right", this, &AFPSPlayer::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSPlayer::Fire);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AFPSPlayer::Action);

}

void AFPSPlayer::MoveFoward(float v)
{
	this->AddMovementInput(GetActorForwardVector(), v);	
}

void AFPSPlayer::MoveRight(float v)
{
	this->AddMovementInput(GetActorRightVector(), v);
}

void AFPSPlayer::Fire()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AProjectile>(Projectile, Gun->GetSocketLocation("Muzzle"), Gun->GetSocketRotation("Muzzle"));
}

void AFPSPlayer::Action_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("AAAAAAAAAAction !"));
}


