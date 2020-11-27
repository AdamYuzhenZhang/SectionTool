// Fill out your copyright notice in the Description page of Project Settings.


#include "ClippingPlane.h"
#include "Misc/OutputDeviceNull.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

// Sets default values
AClippingPlane::AClippingPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Plane = CreateDefaultSubobject<USceneComponent>(TEXT("ThePlaneRoot"));
	Plane->SetupAttachment(Root);

	ThePlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThePlaneMesh"));
	ThePlaneMesh->SetupAttachment(Plane);
}

// Called when the game starts or when spawned
void AClippingPlane::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> ReturnedVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AClippingPlaneVolume::StaticClass(), ReturnedVolumes);
	TheVolume = Cast<AClippingPlaneVolume>(ReturnedVolumes[0]);
	TheVolume->GetActorBounds(false, VolumeLocation, VolumeBoxExtent);
	//PlaneOriginalLocation = FVector(0.0, 0.0, VolumeBoundSize);
	//UE_LOG(LogTemp, Warning, TEXT("VolumeZ is %d"), VolumeBoxExtent.Z);
	//UE_LOG(LogTemp, Warning, TEXT("VolumeBoundSize is %d"), VolumeBoundSize);

	SetPlaneToOriginal();
}

// Called every frame
void AClippingPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Clip();
}

void AClippingPlane::SetVolumeBoundSize(float Size)
{
	VolumeBoundSize = Size / 2;
	UE_LOG(LogTemp, Warning, TEXT("VolumeBoundSize is Set To %d"), VolumeBoundSize);
}

void AClippingPlane::SetPlaneToOriginal()
{
	this->SetActorLocation(VolumeLocation);
	Plane->SetRelativeLocation(FVector(0.0, 0.0, VolumeBoundSize));
	Plane->SetRelativeRotation(FRotator(0.0, 0.0, 0.0));
}

void AClippingPlane::SetPlaneHeight(float Height)
{
	Plane->SetRelativeLocation(FVector(0.0, 0.0, Height));
}

void AClippingPlane::SetPlaneVertical()
{
	SetPlaneToOriginal();
	Plane->SetRelativeRotation(FRotator(0.0, 0.0, 90.0));
}

void AClippingPlane::SetPlaneRotation(float Pitch)
{
	Plane->SetRelativeRotation(FRotator(0.0, Pitch, 90.0));
}

void AClippingPlane::SetPlaneOffSet(float ZValue)
{
	// UE_LOG(LogTemp, Warning, TEXT("ZValue1 is %d"), ZValue);
	FVector MovementVector = Plane->GetUpVector().operator*(ZValue);
	//UE_LOG(LogTemp, Warning, TEXT("ZValue is %d"), ZValue);
	//FVector DeltaLocation = MovementVector.operator-(PlaneOriginalLocation);
	//Plane->MoveComponent(MovementVector, Plane->GetRelativeRotation(), false);
	Plane->SetRelativeLocation(MovementVector);
}

void AClippingPlane::Clip()
{
	FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(TEXT("Clipping"), ar, NULL, true);
}