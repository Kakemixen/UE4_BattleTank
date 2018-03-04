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
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation %s"), *HitLocation.ToCompactString());
		
		//if hits landscape
			// TODO Tell controlled tank to aim towards spot
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OUT HitLocation) const
{
	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	//De-project screen pos of crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,OUT LookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("CameraDirection Location: %s"), *LookDirection.ToString());
	}
	// line-trace along that look direction (up to max range)
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OUT LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		OUT LookDirection
	);

}
