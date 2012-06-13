#ifndef _BB_GEOLOCATION_H
#define _BB_GEOLOCATION_H

#include "BBHeader.h"

#ifdef IPHONE
//#import <UIKit/UIKit.h>
//#import "LocationController.h"
#endif

using namespace std;

namespace bb {

class Geolocation
{
public:
    Geolocation(void);
    virtual ~Geolocation(void);

    //void InitializeGeoLocationSubsystem();

public:
#ifdef IPHONE
    //LocationController *locationController;
#endif
    
    string GetGeoDescription();
    string GetGeoTimestamp();
    float GetGeoLongitude();
    float GetGeoLatitude();
    float GetGeoAltitude();
    float GetGeoHorizontalAccuracy();
    float GetGeoVerticalAccuracy();
    float GetGeoSpeed();
    float GetGeoCourse();

    void SetGeoDescription(string description);
    void SetGeoTimestamp(string description);
    void SetGeoLongitude(float longitude);
    void SetGeoLatitude(float latitude);
    void SetGeoAltitude(float altitude);
    void SetGeoHorizontalAccuracy(float accuracy);
    void SetGeoVerticalAccuracy(float accuracy);
    void SetGeoSpeed(float speed);
    void SetGeoCourse(float course);

private:    
    std::string mGeoDescription;
    std::string mGeoTimestamp;
    float mGeoLongitude;
    float mGeoLatitude;
    float mGeoAltitude;
    float mGeoHorizontalAccuracy;
    float mGeoVerticalAccuracy;
    float mGeoSpeed;
    float mGeoCourse;

};

}

extern bb::Geolocation *gpBBGeolocation;

#endif
