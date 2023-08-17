// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"


USTRUCT(BlueprintType)//��ʾ����ṹӦ��������Ϊһ����Ԫ���л� BlueprintType ���˽ṹ����Ϊ��ͼ�б���������
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()//GENERATED_USTRUCT_BODY ����������Զ�����һЩĬ�ϵĺ����ͳ�Ա����ȷ�� USTRUCT ������ʹ�ú͹��ܡ���Щ�Զ����ɵĺ����ͳ�Ա����Ĭ�Ϲ��캯�������ƹ��캯����������������ֵ������ȡ�

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;//TSubclassOf���ڹ����࣬��֤������������ֻ����ABaseGeometryActor�йص���

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
	TSubclassOf<ABaseGeometryActor> GeometryClass;//TSubclassOf���ڹ����࣬��֤������������ֻ����ABaseGeometryActor�йص���

	//UPROPERTY(EditAnywhere)
	//UClass* Class; //������

	//UPROPERTY(EditAnywhere)
	//ABaseGeometryActor* GeometryObject;//ָ�򳡾��е�����ָ��

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
