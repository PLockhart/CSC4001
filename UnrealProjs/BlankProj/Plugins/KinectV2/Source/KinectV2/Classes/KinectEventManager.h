#pragma once

#include "Engine/EngineTypes.h"
//#include "KinectBodyFrameListenerInterface.h"

UENUM(MinimalApi, BlueprintType)
namespace EKinectPlayer
{
	enum Type
	{
		Player0,
		Player1,
		Player2,
		Player3,
		Player4,
		Player5
	};
}



#include "KinectEventManager.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewSkeletonDetectedEvent, const struct FBody&, NewSkeleton,int32,SkeletonIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkeletonLostEvent, EAutoReceiveInput::Type, KinectPlayerLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewKinectColorFrameEvent, const class UTexture2D*, ColorFrameTexture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewKinectDepthFrameEvent, const class UTexture2D*, DepthFrameTexture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewKinectInfraredFrameEvent, const class UTexture2D*, InfraredFrameTexture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FKinectBodyEventSigneture, EAutoReceiveInput::Type, KinectPlayer, const struct FBody&, Skeleton,int32,SkeletonIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKinectRawBodyFrameEvent, const struct FBodyFrame&, BodyFrame);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKinSkeletonEvent, EKinectPlayer::Type, KinectPlayer);

UCLASS(MinimalAPI)

/**************************************************************************************************
 * Manager for kinect events.
 *
 * @author	Leon Rosengarten
 **************************************************************************************************/

class UKinectEventManager : public UObject//, public IKinectBodyFrameListenerInterface
{

	GENERATED_UCLASS_BODY()

		//UPROPERTY(BlueprintAssignable, Category = "Kinect")
		//	FSkeletonEvent SkeletonEvent;
public:

	/**************************************************************************************************
	 * Process the new body frame event described by Body.
	 *
	 * @author	Leon Rosengarten
	 * @param	Body	The body.
	 **************************************************************************************************/

	void ProcessNewBodyFrameEvent(const struct FBodyFrame & NewBodyFrame, TSharedRef<FGenericApplicationMessageHandler> MessageHandler);


	UFUNCTION(BlueprintImplementableEvent)

		/**************************************************************************************************
		 * Creates a new skeleton detected.
		 *
		 * @author	Leon Rosengarten
		 * @param	Skeleton	The skeleton.
		 **************************************************************************************************/

		 void NewSkeletonDetected(const struct FBody& Skeleton);

	UFUNCTION(BlueprintImplementableEvent)

		/**************************************************************************************************
		 * Skeleton lost.
		 *
		 * @author	Leon Rosengarten
		 * @param	KinectPlayer	The kinect player.
		 **************************************************************************************************/

		 void SkeletonLost(EAutoReceiveInput::Type KinectPlayer);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * Assigne skeleton to player.
		 *
		 * @author	Leon Rosengarten
		 * @param	Body					The body.
		 * @param	Player					The player.
		 * @param	SetAsMouseController	true to set as mouse controller.
		 **************************************************************************************************/

		 void AssigneSkeletonToPlayer(const struct FBody& Body, TEnumAsByte<EAutoReceiveInput::Type> Player, bool SetAsMouseController);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * Enables the mouse control.
		 *
		 * @author	Leon Rosengarten
		 * @param	MouseControl	true to mouse control.
		 **************************************************************************************************/

		 void EnableMouseControl(bool MouseControl);

	UPROPERTY(BlueprintAssignable, Category = "Kinect")
		FNewSkeletonDetectedEvent NewSkeletonDetectedEvent; ///< The new skeleton detected event

	UPROPERTY(BlueprintAssignable, Category = "Kinect")
		FKinectBodyEventSigneture KinectBodyEvent;  ///< The kinect body event

	UPROPERTY(BlueprintAssignable, Category = "Kinect")
		FNewKinectColorFrameEvent OnNewKinectColorFrame;	///< The on new kinect color frame

	UPROPERTY(BlueprintAssignable, Category = "Kinect")
		FNewKinectDepthFrameEvent OnNewKinectDepthFrame;	///< The on new kinect depth frame

	UPROPERTY(BlueprintAssignable, Category = "Kinect")
		FNewKinectInfraredFrameEvent OnNewKinectInfraredFrame;  ///< The on new kinect infrared frame

	UPROPERTY(BlueprintAssignable, Category = "Kinect")
		FKinectRawBodyFrameEvent RawBodyFrameEvent; ///< The raw body frame event

	UPROPERTY(BlueprintAssignable, Category = "Kinect")
		FSkeletonLostEvent SkeletonLostEvent;   ///< The skeleton lost event

	/**************************************************************************************************
	 * Gets control mouse.
	 *
	 * @author	Leon Rosengarten
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	FORCEINLINE bool GetControlMouse()const { return ControlMouse; }
	//DECLARE_EVENT_TwoParams(UKinectBodyManeger, FSkeletonEvent, const FBody&, TEnumAsByte<EKinectPlayer::Type>);
	//FSkeletonEvent& OnNewSkeleton() { return SkeletonEvent; }

public:

	uint64 TrackingIds[6];  ///< The tracking ids[ 6]

	bool NeedsAssignment[6];	///< true to needs assignment[ 6]

	TEnumAsByte<EAutoReceiveInput::Type> CurrentAssignedPlayerIndex[6]; ///< The current assigned player index[ 6]

	TMap<uint64, TEnumAsByte<EAutoReceiveInput::Type>> AssignedKinectPlayerController;  ///< The assigned kinect player controller

	TMultiMap<TEnumAsByte<EKinectPlayer::Type>, TWeakObjectPtr<class AKinectPlayerController>> KinectPlayerActors;  ///< An enum constant representing the multi map option

protected:

	/**************************************************************************************************
	 * Begins a destroy.
	 *
	 * @author	Leon Rosengarten
	 **************************************************************************************************/

	virtual void BeginDestroy() override;
	///void BroadcastNewSkeleton(const FBody& Body, TEnumAsByte<EKinectPlayer::Type> AssingedPlayer){
	//	SkeletonEvent.Broadcast(Body, AssingedPlayer);
	//}

private:

	bool IsLeftHandTracked;

	bool IsRightHandTracked;

	FVector2D LastRightHandScreenPos;

	FVector2D LastLeftHandSrceenPos;

	FVector2D CurrRightHandScreenPos;

	FVector2D CurrLeftHandScreenPos;


	TEnumAsByte<EAutoReceiveInput::Type> MouseControllerPlayer; ///< The mouse controller player

	bool ControlMouse;  ///< true to control mouse

	INPUT* MouseInput;
};