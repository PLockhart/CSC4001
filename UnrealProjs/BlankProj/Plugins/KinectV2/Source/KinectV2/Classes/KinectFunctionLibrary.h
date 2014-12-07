//------------------------------------------------------------------------------
// 
//     The Kinect for Windows APIs used here are preliminary and subject to change
// 
//------------------------------------------------------------------------------
#pragma once
#include "Core.h"
#include "CoreUObject.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "AllowWindowsPlatformTypes.h"
#include "Kinect.h"
#include "HideWindowsPlatformTypes.h"
#include "KinectFunctionLibrary.generated.h"


UENUM(BlueprintType, MinimalAPI)
namespace EJoint{
	enum Type
	{
		JointType_SpineBase = 0 UMETA(DisplayName = "JointType_SpineBase"),
		JointType_SpineMid = 1 UMETA(DisplayName = "JointType_SpineMid"),
		JointType_Neck = 2 UMETA(DisplayName = "JointType_Neck"),
		JointType_Head = 3 UMETA(DisplayName = "JointType_Head"),
		JointType_ShoulderLeft = 4 UMETA(DisplayName = "JointType_ShoulderLeft"),
		JointType_ElbowLeft = 5 UMETA(DisplayName = "JointType_ElbowLeft"),
		JointType_WristLeft = 6 UMETA(DisplayName = "JointType_WristLeft"),
		JointType_HandLeft = 7 UMETA(DisplayName = "JointType_HandLeft"),
		JointType_ShoulderRight = 8 UMETA(DisplayName = "JointType_ShoulderRight"),
		JointType_ElbowRight = 9 UMETA(DisplayName = "JointType_ElbowRight"),
		JointType_WristRight = 10 UMETA(DisplayName = "JointType_WristRight"),
		JointType_HandRight = 11 UMETA(DisplayName = "JointType_HandRight"),
		JointType_HipLeft = 12 UMETA(DisplayName = "JointType_HipLeft"),
		JointType_KneeLeft = 13 UMETA(DisplayName = "JointType_KneeLeft"),
		JointType_AnkleLeft = 14 UMETA(DisplayName = "JointType_AnkleLeft"),
		JointType_FootLeft = 15 UMETA(DisplayName = "JointType_FootLeft"),
		JointType_HipRight = 16 UMETA(DisplayName = "JointType_HipRight"),
		JointType_KneeRight = 17 UMETA(DisplayName = "JointType_KneeRight"),
		JointType_AnkleRight = 18 UMETA(DisplayName = "JointType_AnkleRight"),
		JointType_FootRight = 19 UMETA(DisplayName = "JointType_FootRight"),
		JointType_SpineShoulder = 20 UMETA(DisplayName = "JointType_SpineShoulder"),
		JointType_HandTipLeft = 21 UMETA(DisplayName = "JointType_HandTipLeft"),
		JointType_ThumbLeft = 22 UMETA(DisplayName = "JointType_ThumbLeft"),
		JointType_HandTipRight = 23 UMETA(DisplayName = "JointType_HandTipRight"),
		JointType_ThumbRight = 24 UMETA(DisplayName = "JointType_ThumbRight"),
		JointType_Count = 25 UMETA(DisplayName = "JointType_Count", Hidden)
	};
}

UENUM(BlueprintType, MinimalAPI)
namespace ETrackingState{

	enum Type{
		TrackingState_NotTracked = 0 UMETA(DisplayName = "TrackingState_NotTracked"),
		TrackingState_Inferred = 1 UMETA(DisplayName = "TrackingState_Inferred"),
		TrackingState_Tracked = 2 UMETA(DisplayName = "TrackingState_Tracked")
	};

}

UENUM(BlueprintType, MinimalAPI)
namespace EHandState {

	enum Type{
		HandState_Unknown = 0 UMETA(DisplayName = "HandState_Unknown"),
		HandState_NotTracked = 1 UMETA(DisplayName = "HandState_NotTracked"),
		HandState_Open = 2 UMETA(DisplayName = "HandState_Open"),
		HandState_Closed = 3 UMETA(DisplayName = "HandState_Closed"),
		HandState_Lasso = 4 UMETA(DisplayName = "HandState_Lasso")
	};

}


USTRUCT(BlueprintType)

/**************************************************************************************************
 * A kinect bone.
 *
 * @author	Leon Rosengarten
 **************************************************************************************************/

struct KINECTV2_API FKinectBone
{
	GENERATED_USTRUCT_BODY()

public:

	/**************************************************************************************************
	 * Default constructor.
	 *
	 * @author	Leon Rosengarten
	 **************************************************************************************************/

	FKinectBone();

	FKinectBone(const JointOrientation& jointOrientation, const Joint& joint);


	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		TEnumAsByte<EJoint::Type> JointTypeStart;   ///< The joint type start
	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		TEnumAsByte<EJoint::Type> JointTypeEnd; ///< The joint type end

	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		FQuat Orientation;  ///< The orientation
	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		FVector CameraSpacePoint;   ///< The camera space point
	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		TEnumAsByte<ETrackingState::Type> TrackingState;	///< State of the tracking

	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		FTransform JointTransform;  ///< The joint transform
};

USTRUCT(BlueprintType)

/**************************************************************************************************
 * A body.
 *
 * @author	Leon Rosengarten
 **************************************************************************************************/

struct KINECTV2_API FBody
{
	GENERATED_USTRUCT_BODY()

public:

	/**************************************************************************************************
	 * Default constructor.
	 *
	 * @author	Leon Rosengarten
	 **************************************************************************************************/

	FBody();

	/**************************************************************************************************
	 * Constructor.
	 *
	 * @author	Leon Rosengarten
	 * @param [in,out]	pBody	If non-null, the body.
	 **************************************************************************************************/

	FBody(IBody* pBody);

	/**************************************************************************************************
	 * Constructor.
	 *
	 * @author	Leon Rosengarten
	 * @param	body	The body.
	 **************************************************************************************************/

	FBody(const FBody& body);

	/**************************************************************************************************
	 * Assignment operator.
	 *
	 * @author	Leon Rosengarten
	 * @param	OtherBody	The other body.
	 *
	 * @return	A shallow copy of this object.
	 **************************************************************************************************/

	FBody& operator = (const FBody & OtherBody);

	UPROPERTY(VisibleAnywhere, EditFixedSize, Category = "Kinect")
		TArray<FKinectBone> KinectBones;	///< The kinect bones
	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		TEnumAsByte<ETrackingState::Type> BodyTrackingState;	///< State of the body tracking
	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		TEnumAsByte<EHandState::Type> LeftHandState;	///< State of the left hand
	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		TEnumAsByte<EHandState::Type> RightHandState;   ///< State of the right hand

	UPROPERTY(VisibleAnywhere, Category = "Kinect")
		FVector Lean;

	UPROPERTY()
		uint64 TrackingId;  ///< Identifier for the tracking

	UPROPERTY()
		bool bIsTracked;	///< true if this object is tracked
};


USTRUCT(BlueprintType)

/**************************************************************************************************
 * A body frame.
 *
 * @author	Leon Rosengarten
 **************************************************************************************************/

struct KINECTV2_API FBodyFrame{

	GENERATED_USTRUCT_BODY()

public:

	/**************************************************************************************************
	 * Default constructor.
	 *
	 * @author	Leon Rosengarten
	 **************************************************************************************************/

	FBodyFrame();

	/**************************************************************************************************
	 * Constructor.
	 *
	 * @author	Leon Rosengarten
	 * @param	bodyFrame	The body frame.
	 **************************************************************************************************/

	FBodyFrame(const FBodyFrame& bodyFrame);

	/**************************************************************************************************
	 * Constructor.
	 *
	 * @author	Leon Rosengarten
	 * @param [in,out]	ppBodies	If non-null, the bodies.
	 * @param	floorPlane			The floor plane.
	 **************************************************************************************************/

	FBodyFrame(IBody** ppBodies, const Vector4& floorPlane);

	/**************************************************************************************************
	 * Assignment operator.
	 *
	 * @author	Leon Rosengarten
	 * @param	OtherBodyFrame	The other body frame.
	 *
	 * @return	A shallow copy of this object.
	 **************************************************************************************************/

	FBodyFrame& operator = (const FBodyFrame& OtherBodyFrame);

	UPROPERTY(VisibleAnywhere, EditFixedSize, Category = "Kinect")
		TArray<FBody> Bodies;   ///< The bodies
	UPROPERTY()
		FPlane FloorPlane;  ///< The floor plane


};

DECLARE_MULTICAST_DELEGATE_OneParam(FBodyFrameEventSigneture, const FBodyFrame&);

DECLARE_DELEGATE_OneParam(FEnableBodyJoystick, const bool&);

DECLARE_DELEGATE_RetVal_ThreeParams(FVector2D, FMapBodyCoordToScreenCoord, const FVector&, int32, int32);

DECLARE_DELEGATE_OneParam(FOneEuroFilterSetEnableEvent, bool);

DECLARE_DELEGATE_OneParam(FOneEuroFilterSetFreqEvent, float);

DECLARE_DELEGATE_OneParam(FOneEuroFilterSetMinCutoffEvent, float);

DECLARE_DELEGATE_OneParam(FOneEuroFilterSetBetaEvent, float);

DECLARE_DELEGATE_OneParam(FOneEuroFilterSetDCutOffEvent, float);

DECLARE_DELEGATE_FourParams(FOneEuroFilterSetFilterParamsEvent, float, float, float, float);

DECLARE_DELEGATE_RetVal(class UKinectEventManager*, FGetKinectManegerEvent);

DECLARE_DELEGATE_RetVal(class FKinectV2InputDevice*, FGetKinectInputDevice);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewSkeletonDetectedEventTest, const struct FBody&, NewBody);

UCLASS()

/**********************************************************************************************//**
 * \class	UKinectFunctionLibrary
 *
 * \brief	A kinect function library.
 **************************************************************************************************/

class KINECTV2_API UKinectFunctionLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_UCLASS_BODY()

public:

	friend struct FBody;
	friend struct FKinectBone;
	friend struct FBodyFrame;
	friend class UVisualGestureImporterFactory;


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Kinect", meta = (NativeMakeFunc))

		/**************************************************************************************************
		 * \fn	static FQuat UKinectFunctionLibrary::MakeQuat(float x, float y, float z, float w);
		 *
		 * \brief	Makes a quaternion.
		 *
		 * \param	x	The x coordinate. \param	y	The y coordinate. \param	z	The z coordinate. \param	w	The
		 * scalar.
		 *
		 * \return	A FQuat.
		 *
		 * @author	Leon Rosengarten
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 * @param	z	The z coordinate.
		 * @param	w	The width.
		 *
		 * @return	A FQuat.
		 **************************************************************************************************/

		 static FQuat MakeQuat(float x, float y, float z, float w);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Kinect", meta = (NativeBreakFunc))

		/**************************************************************************************************
		 * \fn	static void UKinectFunctionLibrary::BreakQuat(const FQuat&amp; InQuat, float&amp; x,
		 * float&amp; y, float&amp; z, float&amp; w);
		 *
		 * \brief	Break quaternion.
		 *
		 * \param	InQuat   	The in quaternion. \param [in,out]	x	The float&amp; to process. \param [in,
		 * out]	y	The float&amp; to process. \param [in,out]	z	The float&amp; to process. \param [in,out]
		 * w	The float&amp; to process.
		 *
		 * @author	Leon Rosengarten
		 * @param	InQuat   	The in quaternion.
		 * @param [in,out]	x	The float&amp; to process.
		 * @param [in,out]	y	The float&amp; to process.
		 * @param [in,out]	z	The float&amp; to process.
		 * @param [in,out]	w	The float&amp; to process.
		 **************************************************************************************************/

		 static void BreakQuat(const FQuat& InQuat, float& x, float& y, float& z, float& w);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * Convert quaternion to rotator.
		 *
		 * @author	Leon Rosengarten
		 * @param	InQuat	The in quaternion.
		 *
		 * @return	The quaternion converted to rotator.
		 **************************************************************************************************/

		 static FRotator Conv_QuatToRotator(const FQuat& InQuat);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * \fn	static FQuat UKinectFunctionLibrary::Conv_Vector4ToQuat(const FVector4&amp; InVec);
		 *
		 * \brief	Convert vector 4 to quaternion.
		 *
		 * \param	InVec	The in vector.
		 *
		 * \return	The vector converted 4 to quaternion.
		 *
		 * @author	Leon Rosengarten
		 * @param	InVec	The in vector.
		 *
		 * @return	The vector converted 4 to quaternion.
		 **************************************************************************************************/

		 static FQuat Conv_Vector4ToQuat(const FVector4& InVec);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * \fn	static FRotator UKinectFunctionLibrary::Vec4QuatToRotator(const FVector4&amp; TheVec);
		 *
		 * \brief	Vector 4 quaternion to rotator.
		 *
		 * \param	TheVec	the vector.
		 *
		 * \return	A FRotator.
		 *
		 * @author	Leon Rosengarten
		 * @param	TheVec	the vector.
		 *
		 * @return	A FRotator.
		 **************************************************************************************************/

		 static FRotator Vec4QuatToRotator(const FVector4& TheVec);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * \fn	static FQuat UKinectFunctionLibrary::RotatorToQuat(const FRotator&amp; TheRotator);
		 *
		 * \brief	Rotator to quaternion.
		 *
		 * \param	TheRotator	the rotator.
		 *
		 * \return	A FQuat.
		 *
		 * @author	Leon Rosengarten
		 * @param	TheRotator	the rotator.
		 *
		 * @return	A FQuat.
		 **************************************************************************************************/

		 static FQuat	RotatorToQuat(const FRotator& TheRotator);

	UFUNCTION(BlueprintPure, Category = "Kinect", meta = (NativeBreakFunc))

		/**************************************************************************************************
		 * Break body frame.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	InBodyFrame   	The in body frame.
		 * @param [in,out]	Bodies	The bodies.
		 **************************************************************************************************/

		 static void BreakBodyFrame(const FBodyFrame& InBodyFrame, TArray<FBody> &Bodies);

	UFUNCTION(BlueprintPure, Category = "Kinect", meta = (NativeBreakFunc))

		/**************************************************************************************************
		 * Break vector 4.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	InVector	 	The in vector.
		 * @param [in,out]	X	The float&amp; to process.
		 * @param [in,out]	Y	The float&amp; to process.
		 * @param [in,out]	Z	The float&amp; to process.
		 * @param [in,out]	W	The float&amp; to process.
		 **************************************************************************************************/

		 static void BreakVector4(const FVector4& InVector, float& X, float& Y, float& Z, float& W);

	UFUNCTION(BlueprintPure, Category = "Kinect", meta = (NativeMakeFunc))

		/**************************************************************************************************
		 * Makes vector 4.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	X	The X coordinate.
		 * @param	Y	The Y coordinate.
		 * @param	Z	The Z coordinate.
		 * @param	W	The width.
		 *
		 * @return	A FVector4.
		 **************************************************************************************************/

		 static FVector4 MakeVector4(const float& X, const float& Y, const float& Z, const float& W);

	UFUNCTION(BlueprintPure, Category = "Kinect", meta = (NativeBreakFunc))

		/**************************************************************************************************
		 * Break body.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	InBody				  	The in body.
		 * @param [in,out]	BoneTransforms	The bone transforms.
		 * @param [in,out]	IsTracked	  	The is tracked.
		 **************************************************************************************************/

		 static void BreakBody(const FBody& InBody, TArray<FTransform> &BoneTransforms, bool &IsTracked);

	UFUNCTION(BlueprintPure, Category = "Kinect", meta = (NativeBreakFunc))

		/**************************************************************************************************
		 * Break kinect bone.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	InKinectBone				The in kinect bone.
		 * @param [in,out]	JointTypeStart  	The joint type start.
		 * @param [in,out]	JointTypeEnd		The joint type end.
		 * @param [in,out]	Orientation			The orientation.
		 * @param [in,out]	CameraSpacePoint	The camera space point.
		 * @param [in,out]	TrackingState   	State of the tracking.
		 **************************************************************************************************/

		 static void BreakKinectBone(const FKinectBone& InKinectBone, TEnumAsByte<EJoint::Type> &JointTypeStart,
		 TEnumAsByte<EJoint::Type>& JointTypeEnd,
		 FQuat& Orientation, FVector& CameraSpacePoint, TEnumAsByte<ETrackingState::Type>& TrackingState);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * \fn	static FQuat UKinectFunctionLibrary::MultiplyQuat(const FQuat&amp; A, const FQuat&amp;
		 * B);
		 *
		 * \brief	Multiply quaternion.
		 *
		 * \param	A	The const FQuat&amp; to process. \param	B	The const FQuat&amp; to process.
		 *
		 * \return	A FQuat.
		 *
		 * @author	Leon Rosengarten
		 * @param	A	The const FQuat&amp; to process.
		 * @param	B	The const FQuat&amp; to process.
		 *
		 * @return	A FQuat.
		 **************************************************************************************************/

		 static FQuat MultiplyQuat(const FQuat& A, const FQuat& B);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * \fn	static void UKinectFunctionLibrary::QuatToAxisOutAngle(const FQuat&amp; InQuat,
		 * FVector&amp; OutAxis, float &amp;OutAngle);
		 *
		 * \brief	Quaternion to axis out angle.
		 *
		 * \param	InQuat				The in quaternion. \param [in,out]	OutAxis 	The out axis. \param [in,out]
		 * OutAngle	The out angle.
		 *
		 * @author	Leon Rosengarten
		 * @param	InQuat				The in quaternion.
		 * @param [in,out]	OutAxis 	The out axis.
		 * @param [in,out]	OutAngle	The out angle.
		 **************************************************************************************************/

		 static void QuatToAxisOutAngle(const FQuat& InQuat, FVector& OutAxis, float &OutAngle);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * \fn	static float UKinectFunctionLibrary::DegreesToRadians(const float &amp;InDegrees);
		 *
		 * \brief	Degrees to radians.
		 *
		 * \param	InDegrees	The in in degrees.
		 *
		 * \return	A float.
		 *
		 * @author	Leon Rosengarten
		 * @param	InDegrees	The in in degrees.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		 static float DegreesToRadians(const float &InDegrees);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * \fn	static float UKinectFunctionLibrary::RadiansToDegrees(const float &amp;InRadians);
		 *
		 * \brief	Radians to degrees.
		 *
		 * \param	InRadians	The in in radians.
		 *
		 * \return	A float.
		 *
		 * @author	Leon Rosengarten
		 * @param	InRadians	The in in radians.
		 *
		 * @return	A float.
		 **************************************************************************************************/

		 static float RadiansToDegrees(const float &InRadians);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * Gets the parent of this item.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	InBone	The in bone.
		 *
		 * @return	The bone parent.
		 **************************************************************************************************/

		 static TEnumAsByte<EJoint::Type> GetBoneParent(const TEnumAsByte<EJoint::Type> &InBone);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * Inverse transform.
		 *
		 * @author	Leon Rosengarten
		 * @param	InTransform	The in transform.
		 *
		 * @return	A FTransform.
		 **************************************************************************************************/

		 static FTransform InverseTransform(const FTransform& InTransform);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * Multiply transform.
		 *
		 * @author	Leon Rosengarten
		 * @param	A	The const FTransform&amp; to process.
		 * @param	B	The const FTransform&amp; to process.
		 *
		 * @return	A FTransform.
		 **************************************************************************************************/

		 static FTransform MultiplyTransform(const FTransform& A, const FTransform& B);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * Inverse quaternion.
		 *
		 * @author	Leon Rosengarten
		 * @param	InQuat	The in quaternion.
		 *
		 * @return	A FQuat.
		 **************************************************************************************************/

		 static FQuat InverseQuat(const FQuat& InQuat);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * Enables the body joystick.
		 *
		 * @author	Leon Rosengarten
		 * @param	Enable	The enable.
		 **************************************************************************************************/

		 static void EnableBodyJoystick(const bool& Enable);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * Convert body point to screen point.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	BodyPoint  	The body point.
		 * @param	ScreenSizeX	The screen size x coordinate.
		 * @param	ScreenSizeY	The screen size y coordinate.
		 *
		 * @return	The body converted point to screen point.
		 **************************************************************************************************/

		 static FVector2D ConvertBodyPointToScreenPoint(const FVector& BodyPoint, int32 ScreenSizeX, int32 ScreenSizeY);


	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * Mirror kinect skeleton.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	BodyToMirror	The body to mirror.
		 *
		 * @return	A TArray&lt;FTransform&gt;
		 **************************************************************************************************/

		 static TArray<FTransform> MirrorKinectSkeleton(const FBody& BodyToMirror, float PosLocScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * One euro filter set enable.
		 *
		 * @author	Leon Rosengarten
		 * @param	Enable	true to enable, false to disable.
		 **************************************************************************************************/

		 static void OneEuroFilterSetEnable(bool Enable);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * One euro filter set frequency.
		 *
		 * @author	Leon Rosengarten
		 * @param	Freq	The frequency.
		 **************************************************************************************************/

		 static void OneEuroFilterSetFreq(float Freq);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * One euro filter set minimum cutoff.
		 *
		 * @author	Leon Rosengarten
		 * @param	MinCutoff	The minimum cutoff.
		 **************************************************************************************************/

		 static void OneEuroFilterSetMinCutoff(float MinCutoff);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * One euro filter set beta.
		 *
		 * @author	Leon Rosengarten
		 * @param	Beta	The beta.
		 **************************************************************************************************/

		 static void OneEuroFilterSetBeta(float Beta);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * One euro filter set d cut off.
		 *
		 * @author	Leon Rosengarten
		 * @param	DCutoff	The cutoff.
		 **************************************************************************************************/

		 static void OneEuroFilterSetDCutOff(float DCutoff);

	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * One euro filter set filter parameters.
		 *
		 * @author	Leon Rosengarten
		 * @param	freq	 	The frequency.
		 * @param	minCutoff	The minimum cutoff.
		 * @param	beta	 	The beta.
		 * @param	dCutoff  	The cutoff.
		 **************************************************************************************************/

		 static void OneEuroFilterSetFilterParams(float freq, float minCutoff, float beta, float dCutoff);
	UFUNCTION(BlueprintCallable, Category = "Kinect")

		/**************************************************************************************************
		 * Filters.
		 *
		 * @author	Leon Rosengarten
		 *
		 * @param	KinectBoneTransforms	The kinect bone transforms.
		 * @param	timeStamp				(Optional) the time stamp.
		 *
		 * @return	A TArray&lt;FTransform&gt;
		 **************************************************************************************************/

		 static TArray<FTransform> Filter(const TArray<FTransform>& KinectBoneTransforms, float timeStamp = -1.f);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * Gets kinect function library instance.
		 *
		 * @author	Leon Rosengarten
		 * @param [in,out]	IsValid	The is valid.
		 *
		 * @return	null if it fails, else the kinect function library instance.
		 **************************************************************************************************/

		 static UKinectFunctionLibrary* GetKinectFunctionLibraryInstance(bool& IsValid);

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * Tests get new skeleton detected event.
		 *
		 * @author	Leon Rosengarten
		 * @return	The new skeleton detected event test.
		 **************************************************************************************************/

		 static FNewSkeletonDetectedEventTest& GetNewSkeletonDetectdEventTest();

	UFUNCTION(BlueprintPure, Category = "Kinect")

		/**************************************************************************************************
		 * A kinect event manager*.
		 *
		 * @author	Leon Rosengarten
		 **************************************************************************************************/

		 static class UKinectEventManager* GetKinectEventManager();
	
	
	static FKinectV2InputDevice* GetKinectInputDevice();

private:

	

private:

	friend class FKinectV2InputDevice;

	static FNewSkeletonDetectedEventTest NewSkeletonDetectdEventTest;

	static FEnableBodyJoystick EnableBodyJoystickEvent; ///< The enable body joystick event

	static FMapBodyCoordToScreenCoord MapBodyCoordToScreenCoordEvent;   ///< The map body coordinate to screen coordinate event

	static FOneEuroFilterSetEnableEvent OneEuroFilterSetEnableEvent;	///< The one euro filter set enable event

	static FOneEuroFilterSetFreqEvent OneEuroFilterSetFreqEvent;	///< The one euro filter set frequency event

	static FOneEuroFilterSetMinCutoffEvent OneEuroFilterSetMinCutoffEvent;  ///< The one euro filter set minimum cutoff event

	static FOneEuroFilterSetBetaEvent OneEuroFilterSetBetaEvent;	///< The one euro filter set beta event

	static FOneEuroFilterSetDCutOffEvent OneEuroFilterSetDCutOffEvent;  ///< The one euro filter set d cut off event

	static FOneEuroFilterSetFilterParamsEvent OneEuroFilterSetFilterParamsEvent;	///< A variable-length parameters list containing one euro filter set filter parameters event

	static FGetKinectManegerEvent GetKinectManagerEvent;	///< The get kinect manager event

	static FGetKinectInputDevice GetKinectInputDeviceEvent;

	/**************************************************************************************************
	 * \property	static TMap&lt;TEnumAsByte&lt;EJoint::Type&gt;, TEnumAsByte&lt;EJoint::Type&gt;&gt;
	 * BoneMap
	 *
	 * \brief	Gets the bone map.
	 *
	 * \return	The bone map.
	 *
	 * @return	The bone map.
	 **************************************************************************************************/

	static TMap<TEnumAsByte<EJoint::Type>, TEnumAsByte<EJoint::Type>> BoneMap;


	/**************************************************************************************************
	 * Gets dir vector.
	 *
	 * @author	Leon Rosengarten
	 * @param	From	Source for the.
	 * @param	To  	to.
	 *
	 * @return	The dir vector.
	 **************************************************************************************************/

	static FVector GetDirVec(const FVector& From, const FVector& To);

	static TSharedPtr<class KinectSkeletonOneEuroFilter> KinectBoneFilter;

	//static FBodyFrameEvent BodyFrameEvent;

};