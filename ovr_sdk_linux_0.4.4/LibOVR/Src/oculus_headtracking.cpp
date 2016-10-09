#include "OVR_CAPI.h"
#include "Tracking/Tracking_SensorState.h"  
#include <iostream>
#include <cstdio>

int i = 100;

void Initialization() {
    ovr_Initialize();
    
    ovrHmd hmd = ovrHmd_Create(0);
    
    if (hmd) {
        std::cout << "hmd detected." << std::endl;
        // hmd is not null (which means that oculus is connected)

        // Get more details about the HMD.
        //ovrSizei resolution = hmd->Resolution;

        // Start the sensor which provides the Rift’s pose and motion.
        bool ret = ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation |
                                      ovrTrackingCap_MagYawCorrection |
                                      ovrTrackingCap_Position, 0);
        if (ret == false) std::cout << "tracking capabilities not supported" << std::endl;
                           
        // Query the HMD for the current tracking state.
        while (--i >= 0) {
            ovrTrackingState ts  = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());

            if (ts.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) {
                OVR::Posef pose = ts.HeadPose.ThePose;
                printf("Translation %lf, %lf, %lf, Rotation %lf, %lf, %lf, %lf\n", pose.Translation.x, pose.Translation.y, pose.Translation.z, pose.Rotation.w, pose.Rotation.x, pose.Rotation.y, pose.Rotation.z);
            }
        }
          //...
    }

    // Do something with the HMD.
    //....
    ovrHmd_Destroy(hmd);
    ovr_Shutdown();
}

int main (void) {
    Initialization();
}
