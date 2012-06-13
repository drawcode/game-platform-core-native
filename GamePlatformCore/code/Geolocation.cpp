#include "BBGeolocation.h"

namespace bb {

Geolocation::Geolocation(void)
{
}

Geolocation::~Geolocation(void)
{
#ifdef _IPHONE
    [locationController release];
#endif
}

void Geolocation::InitializeGeoLocationSubsystem()
{
#ifdef _IPHONE
    locationController = [[LocationController alloc] init];
    [locationController.locationManager startUpdatingLocation];
#endif
}


// PROPERTIES

// SETS
void Geolocation::SetGeoDescription(std::string description)
{
    mGeoDescription = description;
}

void Geolocation::SetGeoTimestamp(std::string timestamp)
{
    mGeoTimestamp = timestamp;
}

void Geolocation::SetGeoLongitude(float longitude)
{
    mGeoLongitude = longitude;
}

void Geolocation::SetGeoLatitude(float latitude)
{
    mGeoLatitude = latitude;
}

void Geolocation::SetGeoAltitude(float altitude)
{
    mGeoAltitude = altitude;
}

void Geolocation::SetGeoHorizontalAccuracy(float accuracy)
{
    mGeoHorizontalAccuracy = accuracy;
}

void Geolocation::SetGeoVerticalAccuracy(float accuracy)
{
    mGeoVerticalAccuracy = accuracy;
}

void Geolocation::SetGeoSpeed(float speed)
{
    mGeoSpeed = speed;
}

void Geolocation::SetGeoCourse(float course)
{
    mGeoCourse = course;
}


// GETS
std::string Geolocation::GetGeoDescription()
{
    return mGeoDescription;
}

std::string Geolocation::GetGeoTimestamp()
{
    return mGeoTimestamp;
}

float Geolocation::GetGeoLongitude()
{
    return mGeoLongitude;
}

float Geolocation::GetGeoLatitude()
{
    return mGeoLatitude;
}

float Geolocation::GetGeoAltitude()
{
    return mGeoAltitude;
}

float Geolocation::GetGeoHorizontalAccuracy()
{
    return mGeoHorizontalAccuracy;
}

float Geolocation::GetGeoVerticalAccuracy()
{
    return mGeoVerticalAccuracy;
}

float Geolocation::GetGeoSpeed()
{
    return mGeoSpeed;
}

float Geolocation::GetGeoCourse()
{
    return mGeoCourse;
}

}
