// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "ClippingPlaneVolume.generated.h"

UCLASS()
class SECTIONTOOL_API AClippingPlaneVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClippingPlaneVolume();

	UPROPERTY(BlueprintReadOnly)
		USceneComponent* Root;
	UPROPERTY(BlueprintReadOnly)
		USceneComponent* CameraRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* SphereVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ClippingViewerAngle")
		void SetView(FRotator Rotation);
	// Pitch Y
	UFUNCTION(BlueprintCallable, Category = "ClippingViewerAngle")
		void AddPitch(float DeltaPitch);
	// Yaw Z
	UFUNCTION(BlueprintCallable, Category = "ClippingViewerAngle")
		void AddYaw(float DeltaYaw);
	UFUNCTION(BlueprintCallable, Category = "ClippingViewerAngle")
		FRotator GetCurrentRotator();
};
