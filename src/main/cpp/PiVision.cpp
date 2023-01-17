#include "PiVision.h"

PiVision::PiVision()
{
    std::cout << "PiVision created \n";
    // Creates UsbCamera and MjpegServer [1] and connects them
    frc::CameraServer::StartAutomaticCapture();

    // // Creates the CvSink and connects it to the UsbCamera
    // cs::CvSink cvSink = frc::CameraServer::GetVideo();

    // // Creates the CvSource and MjpegServer [2] and connects them
    // cs::CvSource outputStream = frc::CameraServer::PutVideo("Blur", 640, 480);
}

double clamp(double in, double minval, double maxval)
{
    if (in > maxval)
        return maxval;
    if (in < minval)
        return minval;
    return in;
}

void PiVision::Update()
{
    // Proportional Steering Constant:
    // If your robot doesn't turn fast enough toward the target, make this number bigger
    // If your robot oscillates (swings back and forth past the target) make this smaller
    const double STEER_K = 1.00;

    // Proportional Drive constant: bigger = faster drive
    const double DRIVE_K = 0.08;

    // Area of the target when your robot has reached the goal
    const double DESIRED_TARGET_AREA = 2500.0;
    const double MAX_DRIVE = 0.6;
    const double MAX_STEER = 0.95f;

    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("PiVision");
    double tx = table->GetNumber("Apriltag/cX", 0.0);
    double ty = table->GetNumber("Apriltag/cY", 0.0);
    double ta = table->GetNumber("Apriltag/Area", 0.0);
    double tv = table->GetNumber("Apriltag/ValidResult", 0.0);

    // std::cout<<ta<<"\n";

    if (tv < 1.0)
    {
        HasTarget = false;
        // DriveCmd = 0.0;
        // TurnCmd = 0.0;
    }
    else
    {
        HasTarget = true;

        // Proportional steering
        TurnCmd = tx * STEER_K;
        TurnCmd = clamp(TurnCmd, -MAX_STEER, MAX_STEER);
        std::cout<<TurnCmd<<"\n";

        // drive forward until the target area reaches our desired area
        DriveCmd = (DESIRED_TARGET_AREA - ta) * DRIVE_K;
        DriveCmd = clamp(DriveCmd, -MAX_DRIVE, MAX_DRIVE);
    }
}
