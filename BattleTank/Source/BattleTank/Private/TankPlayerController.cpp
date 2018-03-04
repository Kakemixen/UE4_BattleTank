// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* TempTank = GetControlledTank();
	if (TempTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Player Has No Tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Has Tank %s"), *TempTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OUT HitLocation;

	//Get World Location through(linetrace) crosshair
	if (GetSightRayHitLocation(HitLocation)) {
		//stuff
		UE_LOG(LogTemp, Warning, TEXT("HitLocation %s"), *HitLocation.ToCompactString());
		//if hits landscape
			// TODO Tell controlled tank to aim towards spot
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OUT HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;
}
