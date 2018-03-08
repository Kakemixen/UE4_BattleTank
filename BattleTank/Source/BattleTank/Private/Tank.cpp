// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect since constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Tank Fires"), Time);

	if (!Barrel) { return; }

	//Spawn projectile at socket location from barrel
	GetWorld()->SpawnActor<AProjectile>(
		ProjectileBP,
		Barrel->GetSocketLocation(FName("ProjectileStart")),
		Barrel->GetSocketRotation(FName("ProjectileStart"))
	);
}



void ATank::SetBarrelReference(UTankBarrel* Barrel)
{
	this->Barrel = Barrel; //local variable to spawn stuffs
	TankAimingComponent->SetBarrelReference(Barrel);
}
void ATank::SetTurretReference(UTankTurret* Turret)
{
	TankAimingComponent->SetTurretReference(Turret);
}