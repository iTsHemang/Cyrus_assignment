// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawner.h"
#include "RBox.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();

	//loading Json
	LoadJson();

	//Spawning box
	SpawnBox();
}

void ABoxSpawner::LoadJson()
{
	//Load JSON file and deserializing it
	FString JsonPath = FPaths::ProjectContentDir() / TEXT("Data/BoxData.json");
	FString JsonString;

	if (!FFileHelper::LoadFileToString(JsonString, *JsonPath)) return;

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	FJsonSerializer::Deserialize(Reader, JsonObject);
}

// Called every frame
void ABoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxSpawner::SpawnBox()
{
	if (!JsonObject.IsValid()) return;

	//Get random type from JSON
	const TArray<TSharedPtr<FJsonValue>>* TypesArray;
	if (!JsonObject->TryGetArrayField(TEXT("types"), TypesArray)) return;

	int32 RandTypeIndex = FMath::RandRange(0, TypesArray->Num() - 1);
	TSharedPtr<FJsonObject> TypeObj = (*TypesArray)[RandTypeIndex]->AsObject();

	FString TypeName = TypeObj->GetStringField(TEXT("name"));
	int32 Health     = TypeObj->GetIntegerField(TEXT("health"));
	int32 Score      = TypeObj->GetIntegerField(TEXT("score"));

	//Get color from JSON
	const TArray<TSharedPtr<FJsonValue>>* ColorArray;
	TypeObj->TryGetArrayField(TEXT("color"), ColorArray);

	FLinearColor Color = FLinearColor::White;
	if (ColorArray && ColorArray->Num() == 3)
	{
		Color = FLinearColor(
			(*ColorArray)[0]->AsNumber() / 255.f,
			(*ColorArray)[1]->AsNumber() / 255.f,
			(*ColorArray)[2]->AsNumber() / 255.f
		);
	}

	const TArray<TSharedPtr<FJsonValue>>* ObjectsArray;
	if (!JsonObject->TryGetArrayField(TEXT("objects"), ObjectsArray)) return;

	TArray<TSharedPtr<FJsonObject>> MatchingObjects;
	for (auto& ObjVal : *ObjectsArray)
	{
		TSharedPtr<FJsonObject> Obj = ObjVal->AsObject();
		if (Obj->GetStringField(TEXT("type")) == TypeName)
		{
			MatchingObjects.Add(Obj);
		}
	}
	if (MatchingObjects.Num() == 0) return;

	//Get randome transform from JSON corresponding to type
	int32 RandObjIndex = FMath::RandRange(0, MatchingObjects.Num() - 1);
	TSharedPtr<FJsonObject> RandObj = MatchingObjects[RandObjIndex];
	TSharedPtr<FJsonObject> TransformObj = RandObj->GetObjectField(TEXT("transform"));

	auto ParseVector = [](const TArray<TSharedPtr<FJsonValue>>* Arr)
	{
		return FVector(
			(*Arr)[0]->AsNumber(),
			(*Arr)[1]->AsNumber(),
			(*Arr)[2]->AsNumber()
		);
	};

	FVector Location(0,0,0), Scale(1,1,1), VRotation(0,0,0);

	const TArray<TSharedPtr<FJsonValue>>* LocArr;
	if (TransformObj->TryGetArrayField(TEXT("location"), LocArr)) Location = ParseVector(LocArr);

	const TArray<TSharedPtr<FJsonValue>>* RotArr;
	if (TransformObj->TryGetArrayField(TEXT("rotation"), RotArr)) VRotation = ParseVector(RotArr);
	FRotator Rotation = VRotation.Rotation();

	const TArray<TSharedPtr<FJsonValue>>* ScaleArr;
	if (TransformObj->TryGetArrayField(TEXT("scale"), ScaleArr)) Scale = ParseVector(ScaleArr);

	FTransform SpawnTransform(Rotation, Location, Scale);
	
	//Spawn Box
	AActor* SBox =  GetWorld()->SpawnActor<AActor>(Box, SpawnTransform);

	if (SBox)
	{
		ARBox* BoxClass = Cast<ARBox>(SBox);
		if (BoxClass)
		{
			BoxClass->BS = this;

			//Giving box data to box class
			BoxClass->InitializeCube(Color, Health, Score, TypeName);
		}
	}
}

