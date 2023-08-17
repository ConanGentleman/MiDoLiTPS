// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"


USTRUCT(BlueprintType)//表示这个结构应该总是作为一个单元序列化 BlueprintType 将此结构公开为蓝图中变量的类型
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()//GENERATED_USTRUCT_BODY 宏的作用是自动生成一些默认的函数和成员，以确保 USTRUCT 的正常使用和功能。这些自动生成的函数和成员包括默认构造函数、复制构造函数、析构函数、赋值运算符等。

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;//TSubclassOf用于过滤类，保证虚幻里的下拉框只有与ABaseGeometryActor有关的类

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
};

UCLASS()
class MIDOLITPS_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;//TSubclassOf用于过滤类，保证虚幻里的下拉框只有与ABaseGeometryActor有关的类

	//UPROPERTY(EditAnywhere)
	//UClass* Class; //所有类

	//UPROPERTY(EditAnywhere)
	//ABaseGeometryActor* GeometryObject;//指向场景中的物体指针

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();
};
