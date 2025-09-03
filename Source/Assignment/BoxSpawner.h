// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RBox.h"
#include "GameFramework/Actor.h"
#include "BoxSpawner.generated.h"

UCLASS()
class ASSIGNMENT_API ABoxSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSharedPtr<FJsonObject> JsonObject;

	void LoadJson();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARBox> Box;

	UFUNCTION(BlueprintCallable)
	void SpawnBox();
};
